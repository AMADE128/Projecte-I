#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Enemy_Demon.h"
#include "ModuleEnemies.h"
#include "Enemy.h"
#include "ModuleInput.h"

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

void ModuleParticles::DeleteParticles(int num) {
	
	
	/*delete particles;*/

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

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}