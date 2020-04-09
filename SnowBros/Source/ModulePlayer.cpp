#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "Animation.h"

#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL.h"

#define NICK_SPRITE_SIZE 32


ModulePlayer::ModulePlayer()
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 16, 16, 32, 32 });

	// right jump
	rightjumpAnim.PushBack({ 72, 368, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	rightjumpAnim.PushBack({ 100, 369, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	rightjumpAnim.PushBack({ 131, 375, NICK_SPRITE_SIZE - 3, NICK_SPRITE_SIZE });
	rightjumpAnim.PushBack({ 157, 376, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	rightjumpAnim.PushBack({ 185, 371, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	rightjumpAnim.PushBack({ 213, 374, NICK_SPRITE_SIZE - 3, NICK_SPRITE_SIZE });
	rightjumpAnim.PushBack({ 243, 375, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	rightjumpAnim.PushBack({ 72, 368, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	rightjumpAnim.loop = false;
	rightjumpAnim.speed = 0.1f;

	// left jump
	leftjumpAnim.PushBack({ 572, 305, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE -3});
	leftjumpAnim.PushBack({ 542, 307, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE -4});
	leftjumpAnim.PushBack({ 514, 311, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE -4});
	leftjumpAnim.PushBack({ 486, 312, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE -4});
	leftjumpAnim.PushBack({ 458, 307, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE -4});
	leftjumpAnim.PushBack({ 430, 310, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE -4});
	leftjumpAnim.PushBack({ 399, 311, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE -4});
	leftjumpAnim.PushBack({ 572, 305, NICK_SPRITE_SIZE - 4, NICK_SPRITE_SIZE -3});
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

	sideLeftAnim.PushBack({ 574, 76, NICK_SPRITE_SIZE, NICK_SPRITE_SIZE +3});
	sideLeftAnim.PushBack({ 550, 77, NICK_SPRITE_SIZE - 8, NICK_SPRITE_SIZE +3});
	sideLeftAnim.PushBack({ 523, 76, NICK_SPRITE_SIZE - 8, NICK_SPRITE_SIZE +3});
	sideLeftAnim.PushBack({ 550, 77, NICK_SPRITE_SIZE - 8, NICK_SPRITE_SIZE +3});
	sideLeftAnim.loop = true;
	sideLeftAnim.speed = 0.07f;
	/*
	// Move down
	jumpAnim.PushBack({ 72, 368, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	fallAnim.loop = true;
	fallAnim.speed = 0.1f;*/
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{

	LOG("Loading player textures");

	bool ret = true;

	texture_right = App->textures->Load("Assets/Sprites/Player/Nick_Tom_right.png");
	texture_left = App->textures->Load("Assets/Sprites/Player/Nick_Tom_left.png");
	currentAnimation = &idleAnim;

	shotFx = App->audio->LoadFx("Assets/Audio/SFX/Player/#028.wav");
	//explosionFx = App->audio->LoadFx("Assets/explosion.wav");

	position.x = 528;
	position.y = 955 - (32 * 4.2);

	collider = App->collisions->AddCollider({ position.x, position.y, 32 * 3, 28 * 4 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{

	//SOBRA 4: NUESTRO JUEGO NO TIENE CAMERA SCROLL EN EL EJE X

	// Moving the player with the camera scroll
	//App->player->position.x += 1;


	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] != KEY_STATE::KEY_REPEAT)
	{
		// Enable to escape collision
		if (rightCollision == true)
		{
			speed = 2;
		}

		if (rightCollision == false && leftCollision == false && speed == 0)
		{
			speed = 2;
		}

		// Move player
		position.x -= speed;

		// Set left textures spritesheet to true
		Tleft = true;
		Tright = false;

		if (currentAnimation != &leftjumpAnim && currentAnimation != &sideLeftAnim)
		{
			sideLeftAnim.Reset();
			currentAnimation = &sideLeftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] != KEY_STATE::KEY_REPEAT)
	{
		if (leftCollision == true)
		{
			speed = 2;
		}

		if (rightCollision == false && leftCollision == false && speed == 0)
		{
			speed = 2;
		}

		position.x += speed;

		Tright = true;
		Tleft = false;

		if (currentAnimation != &rightjumpAnim && currentAnimation != &sideRightAnim)
		{
			sideRightAnim.Reset();
			currentAnimation = &sideRightAnim;
		}
	}

	//SOBRA 3: EL PERSONAJE NO PUEDE MOVERSE HACIA ABAJO

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
	}

	//right jump
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && (Tright == true || (rightCollision == true && currentAnimation != &leftjumpAnim)))
	{
		if (rightCollision == true)
		{
			speed = 2;
			Tright = true;
		}

		if (leftCollision == false)
		{
			rightCollision = false;
		}

		Tleft = false;
		speed = 2;

		position.y -= speed;
		if (currentAnimation != &rightjumpAnim)
		{
			rightjumpAnim.Reset();
			currentAnimation = &rightjumpAnim;
		}
	}

	//left jump
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && (Tleft == true || (leftCollision == true && currentAnimation != &rightjumpAnim)))
	{
		if (leftCollision == true)
		{
			speed = 2;
			Tleft = true;
		}

		if (rightCollision == false)
		{
			leftCollision = false;
		}

		Tright = false;
		speed = 2;

		position.y -= speed;
		if (currentAnimation != &leftjumpAnim)
		{
			leftjumpAnim.Reset();
			currentAnimation = &leftjumpAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->shot, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
  		App->audio->PlayFx(shotFx);
	}

	// If no up / left / right movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE && App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE && App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
	{
		currentAnimation = &idleAnim;
		Tright = true;
	}

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	if (destroyed)
	{
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed && Tright == true)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture_right, position.x, position.y, &rect);
	}

	else if (!destroyed && Tleft == true)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture_left, position.x, position.y, &rect);
	}

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
	}
}

void ModulePlayer::StopMovement(Collider* c1, Collider* c2)
{

	if (c1 == collider && destroyed == false)
	{

		if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && speed != 0 && Tleft == false)
		{
			speed = 0;
			leftCollision = false;
			rightCollision = true;
			
		}

		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && speed != 0 && Tright == false)
		{
			speed = 0;
			rightCollision = false;
			leftCollision = true;
			
		}
		
	}

}