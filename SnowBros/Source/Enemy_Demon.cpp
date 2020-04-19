#include "Enemy_Demon.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Demon::Enemy_Demon(int x, int y) : Enemy(x, y)
{
	//Idle animation
	idle.PushBack({ 3,2,29,30 });

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
	//r_walk.loop = true;
	r_walk.speed = 0.07f;

	// TODO 3: Have the Brown Cookies describe a path in the screen

	path.PushBack({ 1, 0 }, 1000, &r_walk);

	collider = App->collisions->AddCollider({position.x, position.y, 32 * 4 - 15, 32 * 4 - 15}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Demon::Update()
{

	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_Demon::Fall(Collider* c1, Collider* c2) {

	position.x = 0;
	if (currentAnim == &r_walk)
	{
		r_walk.pingpong = true;
	}
	if (currentAnim == &l_walk)
	{
		l_walk.pingpong = true;
	}

}