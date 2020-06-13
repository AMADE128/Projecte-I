#include "Monkey.h"

#include <stdio.h>
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

Monkey::Monkey(int x, int y) : Enemy(x, y)
{

	//Idle animation
	idle.PushBack({ 32,32,80,80 });

	//life of the Enemy

	//Left Walk Animation
	l_walk.PushBack({ 128, 32, 80, 80 });
	l_walk.PushBack({ 240, 32, 80, 80 });
	l_walk.PushBack({ 336, 32, 80, 80 });
	l_walk.loop = true;
	l_walk.speed = 0.07f;

	//Right Walk
	r_walk.PushBack({ 880, 32, 80, 80 });
	r_walk.PushBack({ 784, 32, 80, 80 });
	r_walk.PushBack({ 672, 32, 80, 80 });
	r_walk.loop = true;
	r_walk.speed = 0.07f;

	//Left Stun
	l_stun.PushBack({ 448, 32, 80, 80 });
	l_stun.PushBack({ 32, 144, 80, 80 });
	l_stun.loop = true;
	l_stun.speed = 0.05f;

	//Right Snowball
	r_stun.PushBack({ 576, 32, 80, 80 });
	r_stun.PushBack({ 976, 144, 80, 80 });
	r_stun.loop = true;
	r_stun.speed = 0.05f;


	path.PushBack({ 1, 0 }, 1000, &r_walk);
	path.PushBack({ 1, 0 }, 2000, &l_walk);
	path.PushBack({ 0, 0 }, 594058, &r_stun);
	path.PushBack({ 0, 0 }, 594058, &l_stun);

	collider = App->collisions->AddCollider({ (position.x) + 14, position.y, 32 * 4 - 15, 32 * 4 - 15 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Monkey::Update()
{

	path.Update();

	if (currentAnim == &r_walk)
	{
		position.x += 2;
	}

	if (currentAnim == &l_walk)
	{
		//position = spawnPos - path.GetRelativePosition();
		position.x -= 2;
	}

	if (life >= 7)
	{
		currentAnim = path.GetCurrentAnimation();
	}
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position

	Enemy::Update();
}

void Monkey::Fall(Collider* collider) {

	//position.x = 0;
	if (currentAnim == &r_walk)
	{
		currentAnim = &l_walk;
		path.currentStep = 1;
		path.currentStepFrame = 0;
	}

	else if (currentAnim == &l_walk)
	{
		//path.relativePosition = { 0,0 };
		currentAnim = &r_walk;
		path.currentStep = 0;
		path.currentStepFrame = 0;
	}

}

void Monkey::StopMovement(Collider* collider) {

	//position.x = 0;
	if (currentAnim == &r_walk)
	{
		currentAnim = &l_walk;
		path.currentStep = 1;
		path.currentStepFrame = 0;
	}

	else if (currentAnim == &l_walk)
	{
		//path.relativePosition = { 0,0 };
		currentAnim = &r_walk;
		path.currentStep = 0;
		path.currentStepFrame = 0;
	}

}

bool Monkey::CleanUp()
{
	App->collisions->RemoveCollider(collider);

	return true;
}

void Monkey::Freeze(Collider* collider) {

	if (life >= 0)
	{
		life--;
	}

	if (currentAnim == &r_walk && life > 0)
	{
		currentAnim = &r_stun;
		path.currentStep = 2;
		path.currentStepFrame = 0;
	}

	else if (currentAnim == &l_walk && life > 0)
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
		this->collider->type = this->collider->FREEZE_BALL;
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
		App->player->score += 10;
		App->particles->AddParticle(App->particles->snowball[0], position.x, position.y, Collider::NONE);
		break;
	case 6:
		App->player->score += 10;
		App->particles->AddParticle(App->particles->snowball[0], position.x, position.y, Collider::NONE);
		this->collider->type = this->collider->NONE;
		break;
	case 7:
		break;

	}

}