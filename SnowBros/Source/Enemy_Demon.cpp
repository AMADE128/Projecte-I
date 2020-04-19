#include "Enemy_Demon.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Demon::Enemy_Demon(int x, int y) : Enemy(x, y)
{
	//Idle animation
	idle.PushBack({ 3,2,29,30 });

	//Walk Animation
	l_walk.PushBack({ 32, 0, 32, 32 });
	l_walk.PushBack({ 64, 0, 32, 32 });
	l_walk.PushBack({ 96, 0, 32, 32 });
	l_walk.loop = true;
	l_walk.speed = 0.07f;

	// TODO 3: Have the Brown Cookies describe a path in the screen

	path.PushBack({ 1, 0 }, 5, &l_walk);
	//path.PushBack({ -0.4f, 0.3f }, 150, &idle);

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

//void Enemy_Demon::Fall(Collider* c1, Collider* c2)
//{
//	////GRAVEDAD 3
//	//if (currentAnimation != &rightjumpAnim && currentAnimation != &leftjumpAnim && c1->rect.x > c2->rect.x && ((c1->rect.x + c1->rect.w) < (c2->rect.x + c2->rect.w)))
//	//{
//	//	fall = true;
//	//	groundCollision = false;
//	//}
//}
