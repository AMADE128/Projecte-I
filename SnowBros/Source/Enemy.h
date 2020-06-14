#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy(int x, int y);

	// Destructor
	virtual ~Enemy();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	// Triggers an animation and a sound fx
	virtual void OnCollision(Collider* collider);

	virtual void Fall(Collider* collider);

	virtual void StopMovement(Collider* collider);

	virtual void Freeze(Collider* collider);

	virtual void BallPush(Collider* collider);

	virtual void StopMovementY(Collider* collider);

	int tiempo = 3000;
	int descongelar = 0;

public:
	// The current position in the world
	iPoint position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A ptr to the current animation
	Animation* currentAnim = nullptr;
	Animation* currentSnowAnim = nullptr;

	Animation SnowballAnim;
	Animation SnowballPushed;

	int life = 7;

	int current_time = 0;

	// The enemy's collider
	Collider* collider = nullptr;
protected:


	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;

};

#endif // __ENEMY_H__
