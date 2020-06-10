#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"


//constructor: spawns the enemy at given coords
Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
}

//destrcutor: if it's not nullptr, delete it
Enemy::~Enemy()
{
	if (collider != nullptr) collider->pendingToDelete = true;
}

//get the enemies collider
const Collider* Enemy::GetCollider() const
{
	return collider;
}


void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
	//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	//App->audio->PlayFx(destroyedFx);
}

void Enemy::Fall(Collider* collider) {

}

void Enemy::StopMovement(Collider* collider) {

}

void Enemy::Freeze(Collider* collider) {

}