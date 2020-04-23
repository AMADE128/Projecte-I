#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Enemy_Demon.h"
#include "ModuleEnemies.h"
#include "Enemy.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/Player/Nick_right_left.png");

	//Health face
	healthFace.anim.PushBack({ 112, 16, 32, 32 });
	healthFace.anim.speed = 0;

	//Right Shot
	shotright.anim.PushBack({ 16, 141, 7, 11 });
	shotright.anim.PushBack({ 31, 141, 7, 11 });
	shotright.speed.x = 5;
	shotright.lifetime = 180;
	shotright.anim.speed = 0.2f;

	//Left Shot
	shotleft.anim.PushBack({ 1190, 140, 13, 13 });
	shotleft.anim.PushBack({ 1175, 140, 13, 13 });
	shotleft.speed.x = -5;
	shotleft.lifetime = 180;
	shotleft.anim.speed = 0.2f;

	//left snowball
	snowball[0].anim.PushBack({ 12, 702, 28, 32 });
	snowball[1].anim.PushBack({ 41, 702, 28, 32 });
	snowball[2].anim.PushBack({ 74, 702, 28, 32 });
	snowball[3].anim.PushBack({ 107, 703, 28, 32 });
	snowball[4].anim.PushBack({ 140, 702, 28, 32 });

	//Death
	death.anim.PushBack({ 15,527,32,32 });
	for (int i = 0; i < 4; i++)
	{
		death.anim.PushBack({ 52,527,32,32 });
		death.anim.PushBack({ 90,527,32,32 });
	}
	death.anim.PushBack({ 127,527,32,32 });
	death.anim.PushBack({ 164,527,32,32 });
	death.anim.PushBack({ 203,527,32,32 });
	death.anim.PushBack({ 243,527,32,32 });
	death.anim.PushBack({ 283,527,32,32 });
	death.lifetime = 200;
	death.anim.speed = 0.07f;

	//Snow Death animation
	snowDeath.anim.PushBack({ 7, 608, 50, 48 });
	snowDeath.anim.PushBack({ 53, 608, 50, 48 });
	snowDeath.anim.PushBack({ 93, 608, 50, 48 });
	snowDeath.anim.PushBack({ 140, 608, 50, 48 });
	snowDeath.anim.PushBack({ 196, 608, 50, 48 });
	snowDeath.anim.PushBack({ 256, 608, 50, 48 });
	snowDeath.anim.PushBack({ 318, 608, 50, 48 });
	snowDeath.anim.PushBack({ 380, 608, 50, 48 });
	snowDeath.anim.PushBack({ 470, 608, 50, 48 });
	snowDeath.anim.PushBack({ 510, 608, 50, 48 });
	snowDeath.anim.PushBack({ 553, 608, 50, 48 });
	snowDeath.lifetime = 100;
	snowDeath.anim.speed = 0.09f;

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

update_status ModuleParticles::Update()
{
	death.anim.Reset();
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			if (colliderType == Collider::Type::PLAYER_SHOT)
			{
				p->collider = App->collisions->AddCollider({ p->anim.GetCurrentFrame().x, p->anim.GetCurrentFrame().y, 10, 50 }, colliderType, this);
			}

			//Adding the particle's collider
			else if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}