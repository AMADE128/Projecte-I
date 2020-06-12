#include "Frog.h"

#include <stdio.h>
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL.h"

Frog::Frog(int x, int y) : Enemy(x, y)
{

	//Left Idle animation
	l_idle.PushBack({ 0,0,32,32 });
	l_idle.PushBack({ 0,0,32,32 });
	l_idle.PushBack({ 0,0,32,32 });
	l_idle.PushBack({ 0,0,32,32 });
	l_idle.PushBack({ 0,0,32,32 });
	l_idle.PushBack({ 0, 32, 32, 32 });
	l_idle.speed = 0.01f;
	l_idle.loop = true;

	//Right Idle animation
	r_idle.PushBack({ 224,0,32,32 });
	r_idle.PushBack({ 224,0,32,32 });
	r_idle.PushBack({ 224,0,32,32 });
	r_idle.PushBack({ 224,0,32,32 });
	r_idle.PushBack({ 224,0,32,32 });
	r_idle.PushBack({ 224, 32, 32, 32 });
	r_idle.speed = 0.01f;
	r_idle.loop = true;

	//Left Stun
	l_stun.PushBack({ 0, 96, 32, 32 });
	l_stun.PushBack({ 32, 96, 32, 32 });
	l_stun.loop = true;
	l_stun.speed = 0.05f;

	//Right Stun
	r_stun.PushBack({ 224, 64, 32, 32 });
	r_stun.PushBack({ 192, 64, 32, 32 });
	r_stun.loop = true;
	r_stun.speed = 0.05f;

	if (position.x < SCREEN_WIDTH / 2)
	{
		collider = App->collisions->AddCollider({ (position.x) + 14, position.y, 32 * 4 - 15, 32 * 4 - 10 }, Collider::Type::ENEMY, (Module*)App->enemies);
	}
	else if (position.x > SCREEN_WIDTH / 2)
	{
		collider = App->collisions->AddCollider({ (position.x) + 14, position.y, 32 * 4, 32 * 4 - 10 }, Collider::Type::ENEMY, (Module*)App->enemies);
	}

}

void Frog::Update()
{
	if (App->player->position.x > position.x && life >= 7)
	{
		currentAnim = &r_idle;
	}
	else if (App->player->position.x < position.x && life >= 7)
	{
		currentAnim = &l_idle;
	}

	if (currentAnim == &l_idle && currentAnim->GetCurrentFrame().y == l_idle.frames[0].y)
	{
		shot = 0;
	}

	if (currentAnim == &r_idle && currentAnim->GetCurrentFrame().y == r_idle.frames[0].y)
	{
		shot = 0;
	}

	if (currentAnim == &r_idle && r_idle.GetCurrentFrame().y == 32 && life >= 7 && shot == 0)
	{
		App->particles->AddParticle(App->particles->r_fire_ball, position.x, position.y, Collider::Type::ENEMY_SHOT);
		shot += 1;
	}

	if (currentAnim == &l_idle && l_idle.GetCurrentFrame().y == 32 && life >= 7 && shot == 0)
	{
		App->particles->AddParticle(App->particles->l_fire_ball, position.x, position.y, Collider::Type::ENEMY_SHOT);
		shot += 1;
	}

	//path.Update();

	//if (currentAnim == &r_walk)
	//{
	//	position.x += 2;
	//}

	//if (currentAnim == &l_walk)
	//{
	//	//position = spawnPos - path.GetRelativePosition();
	//	position.x -= 2;
	//}

	//if (life >= 7)
	//{
	//	currentAnim = path.GetCurrentAnimation();
	//}
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position

	Enemy::Update();
}

void Frog::Fall(Collider* collider) {

	////position.x = 0;
	//if (currentAnim == &r_walk)
	//{
	//	currentAnim = &l_walk;
	//	path.currentStep = 1;
	//	path.currentStepFrame = 0;
	//}

	//else if (currentAnim == &l_walk)
	//{
	//	//path.relativePosition = { 0,0 };
	//	currentAnim = &r_walk;
	//	path.currentStep = 0;
	//	path.currentStepFrame = 0;
	//}

}

void Frog::StopMovement(Collider* collider) {

	////position.x = 0;
	//if (currentAnim == &r_walk)
	//{
	//	currentAnim = &l_walk;
	//	path.currentStep = 1;
	//	path.currentStepFrame = 0;
	//}

	//else if (currentAnim == &l_walk)
	//{
	//	//path.relativePosition = { 0,0 };
	//	currentAnim = &r_walk;
	//	path.currentStep = 0;
	//	path.currentStepFrame = 0;
	//}

}

bool Frog::CleanUp()
{
	App->collisions->RemoveCollider(collider);

	return true;
}

void Frog::Freeze(Collider* collider) {

	if (life >= 0)
	{
		life--;
	}

	if (life > 0)
	{
		currentAnim = &r_stun;
		path.currentStep = 2;
		path.currentStepFrame = 0;
	}

	else if (life > 0)
	{
		currentAnim = &l_stun;
		path.currentStep = 3;
		path.currentStepFrame = 0;
	}

	switch (life)
	{
	case 1:
		App->player->score += 500;
		App->particles->snowball[3].lifetime = 0;
		App->particles->AddParticle(App->particles->snowball[4], position.x, position.y, Collider::NONE);
		break;
	case 2:
		App->player->score += 10;
		App->particles->snowball[2].lifetime = 0;
		App->particles->AddParticle(App->particles->snowball[3], position.x, position.y, Collider::NONE);
		break;
	case 3:
		App->player->score += 10;
		App->particles->snowball[1].lifetime = 0;
		App->particles->AddParticle(App->particles->snowball[2], position.x, position.y, Collider::NONE);
		break;
	case 4:
		App->player->score += 10;
		App->particles->snowball[0].lifetime = 0;
		App->particles->AddParticle(App->particles->snowball[1], position.x, position.y, Collider::NONE);
		break;
	case 5:
	case 6:
		App->player->score += 10;
		App->particles->AddParticle(App->particles->snowball[0], position.x, position.y, Collider::NONE);
		this->collider->type = this->collider->NONE;
		break;
	case 7:
		break;

	}

}