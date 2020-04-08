#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"

#define NICK_SPRITE_SIZE 32


ModulePlayer::ModulePlayer()
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 16, 16, 32, 32 });

	// move upwards
	jumpAnim.PushBack({ 72, 368, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	jumpAnim.PushBack({ 100, 369, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	jumpAnim.PushBack({ 131, 375, NICK_SPRITE_SIZE - 3, NICK_SPRITE_SIZE });
	jumpAnim.PushBack({ 157, 376, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	jumpAnim.PushBack({ 185, 371, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	jumpAnim.PushBack({ 213, 374, NICK_SPRITE_SIZE - 3, NICK_SPRITE_SIZE });
	jumpAnim.PushBack({ 243, 375, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	jumpAnim.PushBack({ 72, 368, NICK_SPRITE_SIZE - 2, NICK_SPRITE_SIZE });
	jumpAnim.loop = false;
	jumpAnim.speed = 0.1f;

	// Move down
	fallAnim.PushBack({ 33, 1, 32, 14 });
	fallAnim.PushBack({ 0, 1, 32, 14 });
	fallAnim.loop = false;
	fallAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/Player/Nick_Tom.png");
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

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
	}

	//SOBRA 3: EL PERSONAJE NO PUEDE MOVERSE HACIA ABAJO

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
		if (currentAnimation != &fallAnim)
		{
			fallAnim.Reset();
			currentAnimation = &fallAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
		if (currentAnimation != &jumpAnim)
		{
			jumpAnim.Reset();
			currentAnimation = &jumpAnim;
		}
		//jumpAnimState = true;
	}

	/*if (jumpAnimState = true )
	{
		position.y -= speed;
	}*/

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(shotFx);
	}

	// If no up movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE && jumpAnimState == false)
		currentAnimation = &idleAnim;

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
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);

		destroyed = true;
	}
}