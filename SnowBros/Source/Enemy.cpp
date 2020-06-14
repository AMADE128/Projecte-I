#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL.h"

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
	SnowballAnim.PushBack({ 0,0,0,0 });
	SnowballAnim.PushBack({ 12, 702, 28, 32 });
	SnowballAnim.PushBack({ 41, 702, 28, 32 });
	SnowballAnim.PushBack({ 74, 702, 28, 32 });
	SnowballAnim.PushBack({ 107, 703, 28, 32 });
	SnowballAnim.PushBack({ 140, 702, 28, 32 });
	
	SnowballPushed.PushBack({ 140, 702, 28, 32 });
	SnowballPushed.PushBack({ 231, 702, 28, 32 });
	SnowballPushed.PushBack({ 264, 702, 28, 32 });
	SnowballPushed.PushBack({ 298, 702, 28, 32 });
	SnowballPushed.loop = true;
}

Enemy::~Enemy()
{
	if (collider != nullptr) collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (life < 7 && App->player->pushing == false)
	{
		int currentTime = SDL_GetTicks();

		if (descongelar == 0)
			descongelar = SDL_GetTicks();

		else if (currentTime - descongelar >= tiempo)
		{
			if (life == 1)
			{
				App->player->score -= 500;
			}
			else
			{
				App->player->score -= 10;
			}
			life++;
			descongelar = 0;
		}
	}

	if (life == 1 && App->player->pushing == true)
	{
		if(App->player->currentAnimation == &App->player->sideRightAnim)
			position.x += App->player->speed_x * 1.5;

		if (App->player->currentAnimation == &App->player->sideLeftAnim)
			position.x -= App->player->speed_x * 1.5;
	}
	
		switch (life)
		{
		case 7:
			SnowballAnim.SetCurrentFrame(0);
			break;
		case 6:
		case 5:
			SnowballAnim.SetCurrentFrame(1);
			break;
		case 4:
			SnowballAnim.SetCurrentFrame(2);
			break;
		case 3:
			SnowballAnim.SetCurrentFrame(3);
			break;
		case 2:
			SnowballAnim.SetCurrentFrame(4);
			break;
		case 1:
		case 0:
			SnowballAnim.SetCurrentFrame(5);
			break;
		default:
			break;
		}

		currentSnowAnim = &SnowballAnim;
	

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Enemy::Draw()
{
	if (life > 2)
	{
		if (currentAnim != nullptr)
			App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
	}

	if (&SnowballAnim != nullptr)
		App->render->Blit(App->player->spritesheet, position.x, position.y, &(currentSnowAnim->GetCurrentFrame()));

}

void Enemy::OnCollision(Collider* collider)
{

}

void Enemy::Fall(Collider* collider) {

}

void Enemy::StopMovement(Collider* collider) {

}

void Enemy::StopMovementY(Collider* collider) {

}

void Enemy::Freeze(Collider* collider) {

}

void Enemy::BallPush(Collider* collider) {

}