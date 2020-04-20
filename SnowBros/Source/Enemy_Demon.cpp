#include "Enemy_Demon.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"

Enemy_Demon::Enemy_Demon(int x, int y) : Enemy(x, y)
{


	//Idle animation
	idle.PushBack({ 3,2,29,30 });

	//life of the Enemy

	//Left Walk Animation
	l_walk.PushBack({ 32, 0, 32, 32 });
	l_walk.PushBack({ 64, 0, 32, 32 });
	l_walk.PushBack({ 96, 0, 32, 32 });
	l_walk.loop = true;
	l_walk.speed = 0.07f;

	//Right Walk
	r_walk.PushBack({ 256, 0, 32, 32 });
	r_walk.PushBack({ 224, 0, 32, 32 });
	r_walk.PushBack({ 192, 0, 32, 32 });
	r_walk.loop = true;
	r_walk.speed = 0.07f;

	//Left Stun
	l_stun.PushBack({ 0, 32, 32, 32 });
	l_stun.PushBack({ 32, 32, 32, 32 });
	l_stun.loop = true;
	l_stun.speed = 0.05f;

	//Right Snowball
	r_stun.PushBack({ 256, 32, 32, 32 });
	r_stun.PushBack({ 288, 32, 32, 32 });
	r_stun.loop = true;
	r_stun.speed = 0.05f;

	// TODO 3: Have the Brown Cookies describe a path in the screen

	path.PushBack({ 1, 0 }, 1000, &r_walk);
	path.PushBack({ 1, 0 }, 2000, &l_walk);
	path.PushBack({ 0, 0 }, 594058, &r_stun);
	path.PushBack({ 0, 0 }, 594058, &l_stun);

	collider = App->collisions->AddCollider({position.x, position.y, 32 * 4 - 15, 32 * 4 - 15}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Demon::Update()
{

	path.Update();

	if (currentAnim == &r_walk)
	{
		position.x++;
	}

	if (currentAnim == &l_walk)
	{
		//position = spawnPos - path.GetRelativePosition();
		position.x--;
	}

	if (life >= 7)
	{
		currentAnim = path.GetCurrentAnimation();
	}
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_Demon::Fall(Collider* collider) {

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

void Enemy_Demon::StopMovement(Collider* collider) {

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

void Enemy_Demon::Freeze(Collider* collider) {
	life--;

	if (currentAnim == &r_walk && life < 7)
	{
		currentAnim = &r_stun;
		path.currentStep = 2;
		path.currentStepFrame = 0;
	}

	else if (currentAnim == &l_walk && life < 7)
	{
		//path.relativePosition = { 0,0 };
		currentAnim = &l_stun;
		path.currentStep = 3;
		path.currentStepFrame = 0;
	}

	switch (life)
	{
	case 1:
		App->particles->DeleteParticles(App->particles->snowball[3]);
		App->particles->AddParticle(App->particles->snowball[4], position.x, position.y, Collider::NONE);
		break;
	case 2:
		App->particles->DeleteParticles(App->particles->snowball[2]);
		App->particles->AddParticle(App->particles->snowball[3], position.x, position.y, Collider::NONE);
		break;
	case 3:
		App->particles->DeleteParticles(App->particles->snowball[1]);
		App->particles->AddParticle(App->particles->snowball[2], position.x, position.y, Collider::NONE);
		break;
	case 4:
		App->particles->DeleteParticles(App->particles->snowball[0]);
		App->particles->AddParticle(App->particles->snowball[1], position.x, position.y, Collider::NONE);
		break;
	case 5:
	case 6:
		App->particles->AddParticle(App->particles->snowball[0], position.x, position.y, Collider::NONE);
		break;
	case 7:
		break;

	}

}