#include "Enemy_Demon.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Demon::Enemy_Demon(int x, int y) : Enemy(x, y)
{
	//Idle animation
	idle.PushBack({ 3,2,29,30 });

	//Walk Animation


	// TODO 3: Have the Brown Cookies describe a path in the screen

	path.PushBack({ 0.3f, 0.0f }, 150, &idle);
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
