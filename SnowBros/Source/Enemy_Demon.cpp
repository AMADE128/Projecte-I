#include "Enemy_Demon.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Demon::Enemy_Demon(int x, int y) : Enemy(x, y)
{
	idle.PushBack({ 0,0,32,32 });
	currentAnim = &idle;


	// TODO 3: Have the Brown Cookies describe a path in the screen

	/*path.PushBack({ -0.4f, -0.3f }, 150, &fly);
	path.PushBack({ -0.4f, 0.3f }, 150, &fly);*/
	position.x = x / 2;
	position.y = y / 2;

	collider = App->collisions->AddCollider({position.x, position.y, 32 * 3, 32 * 3}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Demon::Update()
{

	/*path.Update();
	position = spawnPos + path.GetRelativePosition();*/

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
