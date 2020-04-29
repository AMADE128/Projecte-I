#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "Animation.h"
#include "ModuleFonts.h"
#include "ModuleEnemies.h"
#include "SceneLevel1.h"

#include <stdio.h>

#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL.h"

#define NICK_SPRITE_SIZE 32


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	//Right
	r_idleAnim.PushBack({ 16, 16, 32, 32 });
	//Left
	l_idleAnim.PushBack({ 1177, 16, 32, 32 });

	// right jump
	lastRightJumpSprite = { 217, 305, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE };

	rightjumpAnim.PushBack({ 72, 368, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	rightjumpAnim.PushBack({ 100, 369, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	rightjumpAnim.PushBack({ 131, 375, NICK_SPRITE_SIZE - 3, NICK_SPRITE_SIZE });
	rightjumpAnim.PushBack({ 157, 376, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	rightjumpAnim.PushBack({ 185, 371, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	rightjumpAnim.PushBack({ 213, 374, NICK_SPRITE_SIZE - 3, NICK_SPRITE_SIZE });
	rightjumpAnim.PushBack({ 243, 375, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	rightjumpAnim.PushBack(lastRightJumpSprite);
	rightjumpAnim.loop = false;
	rightjumpAnim.speed = 0.1f;

	// left jump
	lastLeftJumpSprite = { 979, 305, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE - 3 };

	leftjumpAnim.PushBack({ 1180, 305, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE - 3 });
	leftjumpAnim.PushBack({ 1150, 307, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE - 4 });
	leftjumpAnim.PushBack({ 1122, 311, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE - 4 });
	leftjumpAnim.PushBack({ 1094, 312, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE - 4 });
	leftjumpAnim.PushBack({ 1066, 307, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE - 4 });
	leftjumpAnim.PushBack({ 1038, 310, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE - 4 });
	leftjumpAnim.PushBack({ 1007, 311, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE - 4 });
	leftjumpAnim.PushBack(lastLeftJumpSprite);
	leftjumpAnim.loop = false;
	leftjumpAnim.speed = 0.1f;

	// Move right

	sideRightAnim.PushBack({ 13, 75, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE });
	sideRightAnim.PushBack({ 37, 76, NICK_SPRITE_SIZE - 3, NICK_SPRITE_SIZE });
	sideRightAnim.PushBack({ 62, 75, NICK_SPRITE_SIZE - 5, NICK_SPRITE_SIZE });
	sideRightAnim.PushBack({ 37, 76, NICK_SPRITE_SIZE - 3, NICK_SPRITE_SIZE });
	sideRightAnim.loop = true;
	sideRightAnim.speed = 0.07f;

	// Move left

	sideLeftAnim.PushBack({ 1182, 76, NICK_SPRITE_SIZE, NICK_SPRITE_SIZE + 3 });
	sideLeftAnim.PushBack({ 1158, 77, NICK_SPRITE_SIZE - 8, NICK_SPRITE_SIZE + 3 });
	sideLeftAnim.PushBack({ 1131, 76, NICK_SPRITE_SIZE - 8, NICK_SPRITE_SIZE + 3 });
	sideLeftAnim.PushBack({ 1158, 77, NICK_SPRITE_SIZE - 8, NICK_SPRITE_SIZE + 3 });
	sideLeftAnim.loop = true;
	sideLeftAnim.speed = 0.07f;
	
	// Move down
	fallRightAnim.PushBack( lastRightJumpSprite );
	fallRightAnim.loop = false;
	fallRightAnim.speed = 0.1f;

	fallLeftAnim.PushBack(lastLeftJumpSprite);
	fallLeftAnim.loop = false;
	fallLeftAnim.speed = 0.1f;

	//Win animation
	winAnim.PushBack({ 374, 366, 32, 32 });
	winAnim.PushBack({ 404, 366, 32, 32 });
	winAnim.loop = true;
	winAnim.speed = 0.1f;

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{

	LOG("Loading player textures");

	bool ret = true;

	spritesheet = App->textures->Load("Assets/Sprites/Player/Nick_right_left.png");
	currentAnimation = &r_idleAnim;

	shotFx = App->audio->LoadFx("Assets/Audio/SFX/Player/#028.wav");
	looseFx = App->audio->LoadFx("Assets/Audio/Music/Menus/9.#046 Game Over.ogg");
	deathFx = App->audio->LoadFx("Assets/Audio/SFX/Others/#008.wav");

	position.x = 528;
	position.y = 955 - (32 * 4.2);

	destroyed = false;

	char life_score_Table[] = { "0123456789" };
	lifeFont = App->fonts->Load("Assets/Sprites/Menu & UI/numbers.png", life_score_Table, 1);
	scoreFont = App->fonts->Load("Assets/Sprites/Menu & UI/points.png", life_score_Table, 1);

	collider = App->collisions->AddCollider({ position.x, position.y, 32 * 3, 28 * 4}, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{

	//SOBRA 4: NUESTRO JUEGO NO TIENE CAMERA SCROLL EN EL EJE X

	// Moving the player with the camera scroll
	//App->player->position.x += 1;

	if (App->input->keys[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
	{
		if (godmode == false)
		{
			godmode = true;
			collider->type = Collider::NONE;
		}
		else if (godmode == true)
		{
			godmode = false;
			collider->type = Collider::PLAYER;
		}
	}

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] != KEY_STATE::KEY_REPEAT && App->enemies->win == false)
	{
		// Enable to escape collision
		if (rightCollision == true)
		{
			speed_x = 2;
		}

		if (rightCollision == false && leftCollision == false && speed_x == 0)
		{
			speed_x = 2;
		}

		if (fall == true)
		{
			speed_y = SPEED_Y;
		}

		// Move player
		position.x -= speed_x;

		//change sprite while jumping
		if (currentAnimation == &rightjumpAnim && currentAnimation->GetCurrentFrame().x == lastRightJumpSprite.x)
		{
			leftjumpAnim.currentFrame = 18;
			currentAnimation = &leftjumpAnim;
		}

		if (currentAnimation != &leftjumpAnim && currentAnimation != &sideLeftAnim && currentAnimation != &rightjumpAnim)
		{
			sideLeftAnim.Reset();
			currentAnimation = &sideLeftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] != KEY_STATE::KEY_REPEAT && App->enemies->win == false)
	{
		if (leftCollision == true)
		{
			speed_x = 2;
		}

		if (rightCollision == false && leftCollision == false && speed_x == 0)
		{
			speed_x = 2;
		}

		if (fall == true)
		{
			speed_y = SPEED_Y;
		}


		position.x += speed_x;

		//change sprite while jumping
		if (currentAnimation == &leftjumpAnim && currentAnimation->GetCurrentFrame().x == lastLeftJumpSprite.x)
		{
			rightjumpAnim.currentFrame = 10;
			currentAnimation = &rightjumpAnim;
		}

		if (currentAnimation != &rightjumpAnim && currentAnimation != &sideRightAnim && currentAnimation != &leftjumpAnim)
		{
			sideRightAnim.Reset();
			currentAnimation = &sideRightAnim;
		}
	}

	//SOBRA 3: EL PERSONAJE NO PUEDE MOVERSE HACIA ABAJO

	if (godmode == true)
	{
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
		{
			position.y -= speed_y;
		}
		if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			position.y += speed_y;
		}
	}

	//right jump
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && currentAnimation != &leftjumpAnim && fall == false && godmode == false && App->enemies->win == false)
	{
		if (rightCollision == true)
		{
			speed_x = 2;
		}

		if (leftCollision == false)
		{
			rightCollision = false;
		}

		if (groundCollision == true)
		{
			speed_y = SPEED_Y;
			groundCollision = false;
		}

		position.y -= speed_y;
		if (currentAnimation != &rightjumpAnim && (currentAnimation == &r_idleAnim || currentAnimation == &sideRightAnim))
		{
			rightjumpAnim.Reset();
			currentAnimation = &rightjumpAnim;
		}
	}

	//left jump
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && currentAnimation != &rightjumpAnim && fall == false && godmode == false && App->enemies->win == false)
	{
		if (leftCollision == true)
		{
			speed_x = 2;
		}

		if (rightCollision == false)
		{
			leftCollision = false;
		}

		if (groundCollision == true)
		{
			speed_y = SPEED_Y;
			groundCollision = false;
		}

		position.y -= speed_y;
		if (currentAnimation != &leftjumpAnim && (currentAnimation == &l_idleAnim || currentAnimation == &sideLeftAnim))
		{
			leftjumpAnim.Reset();
			currentAnimation = &leftjumpAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && App->enemies->win == false)
	{
		if (currentAnimation == &sideRightAnim || currentAnimation == &r_idleAnim)
		{
			App->particles->AddParticle(App->particles->shotright, position.x + 75, position.y + 20, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(shotFx);
		}
		else if (currentAnimation == &sideLeftAnim || currentAnimation == &l_idleAnim)
		{
			App->particles->AddParticle(App->particles->shotleft, position.x - 20, position.y + 20, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(shotFx);
		}
	}

	//We make the player go up or down

	if (currentAnimation == &leftjumpAnim && (currentAnimation->GetCurrentFrame().x != lastLeftJumpSprite.x))
	{
		position.y -= (speed_y + 1);
	}

	if (currentAnimation == &leftjumpAnim && (currentAnimation->GetCurrentFrame().x == lastLeftJumpSprite.x) && groundCollision == false)
	{
		position.y += speed_y;
	}

	if (currentAnimation == &rightjumpAnim && (currentAnimation->GetCurrentFrame().x != lastRightJumpSprite.x))
	{
		position.y -= (speed_y + 1);
	}

	if (currentAnimation == &rightjumpAnim && (currentAnimation->GetCurrentFrame().x == lastRightJumpSprite.x) && groundCollision == false)
	{
		position.y += speed_y;
	}

	//GRAVEDAD 1

	//Gravity

	if (fall == true && App->enemies->win == false)
	{
		position.y += speed_y;

		if (currentAnimation == &r_idleAnim || currentAnimation == &sideRightAnim) {
			currentAnimation = &fallRightAnim;
		}

		if (currentAnimation == &l_idleAnim || currentAnimation == &sideLeftAnim) {
			currentAnimation = &fallLeftAnim;
		}
	}

	// If no up / left / right movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE && App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE && App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE && ((currentAnimation != &leftjumpAnim && currentAnimation != &rightjumpAnim)) || ((currentAnimation == &leftjumpAnim || currentAnimation == &rightjumpAnim)))
	{
		//groundCollision = false;

		speed_y = SPEED_Y;

		if (currentAnimation == &sideRightAnim || (currentAnimation == &rightjumpAnim && currentAnimation->GetCurrentFrame().x == lastRightJumpSprite.x && groundCollision == true) || (currentAnimation == &fallRightAnim && fall == false))
		{
			currentAnimation = &r_idleAnim;
		}
		if (currentAnimation == &sideLeftAnim || (currentAnimation == &leftjumpAnim && currentAnimation->GetCurrentFrame().x == lastLeftJumpSprite.x && groundCollision == true) || (currentAnimation == &fallLeftAnim && fall == false))
		{
			currentAnimation = &l_idleAnim;
		}
	}

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	if (destroyed)
	{
		pHealth--;
		if (pHealth == 0) {
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 200);
			//App->audio->PlayFx(looseFx);
			pHealth = 4;
			score = 0;

		}
		else {
			App->audio->PlayFx(deathFx);
			speed_x = 0;
			speed_y = 0,
			destroyed = false;
			position.x = 528;
			position.y = 955 - (32 * 4.2);
			App->particles->AddParticle(App->particles->snowDeath, position.x - 55, position.y - 60, Collider::NONE);
			collider->SetPos(position.x, position.y);
		}
	}

	if (App->enemies->win == true) 
	{
		currentAnimation = &winAnim;
		collider->type = Collider::NONE;
		position.y -= 4;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(spritesheet, position.x, position.y, &rect);
	}

	sprintf_s(lifeText, 10, "%d", pHealth);
	sprintf_s(scoreText, 10, "%d", score);

	App->fonts->BlitText(80, 40, lifeFont, lifeText);
	App->fonts->BlitText(1200, 53, scoreFont, scoreText);

	App->render->Blit(App->particles->texture, -10, -20, &App->particles->healthFace.anim.GetCurrentFrame());

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		/*App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);*/

		App->audio->PlayFx(explosionFx);

		destroyed = true;

		App->particles->AddParticle(App->particles->death, position.x, position.y, Collider::NONE);
	}
}

void ModulePlayer::StopMovement(Collider* c1, Collider* c2)
{

	if (c1 == collider && destroyed == false)
	{

		if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && speed_x != 0)
		{
			speed_x = 0;
			leftCollision = false;
			rightCollision = true;

		}
		
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && speed_x != 0)
		{
			speed_x = 0;
			rightCollision = false;
			leftCollision = true;

		}

	}

}

void ModulePlayer::StopMovementY(Collider* c1, Collider* c2)
{
	//GRAVEDAD 2

	if ((c1->rect.y + c1->rect.w) < c2->rect.y && groundCollision == false)
		fall = true;

	if (currentAnimation != &rightjumpAnim && currentAnimation != &leftjumpAnim && ((c1->rect.y + c1->rect.h - 5) <= c2->rect.y))
	{
		groundCollision = true;
		speed_y = 0;
		fall = false;
	}

	if (currentAnimation == &rightjumpAnim && currentAnimation->GetCurrentFrame().x == lastRightJumpSprite.x && ((c1->rect.y + c1->rect.h - 5) <= c2->rect.y))
	{
		groundCollision = true;
		speed_y = 0;
		fall = false;
	}

	else if (currentAnimation == &leftjumpAnim && currentAnimation->GetCurrentFrame().x == lastLeftJumpSprite.x && ((c1->rect.y + c1->rect.h - 5) <= c2->rect.y))
	{
		groundCollision = true;
		speed_y = 0;
		fall = false;
	}
}

void ModulePlayer::Fall(Collider* c1, Collider* c2)
{
	//GRAVEDAD 3
	if (currentAnimation != &rightjumpAnim && currentAnimation != &leftjumpAnim && c1->rect.x > c2->rect.x && ((c1->rect.x + c1->rect.w) < (c2->rect.x + c2->rect.w)))
	{
		fall = true;
		groundCollision = false;
	}

	if ((c1->rect.y + c1->rect.w) < c2->rect.y && groundCollision == false)
	{
		fall = true;
		//groundCollision = false;
	}
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading particles");

	// Delete collider and texture
	SDL_DestroyTexture(spritesheet);
	

	return true;
}