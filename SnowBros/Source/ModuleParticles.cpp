#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Enemy_Demon.h"


#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
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

	//Right snowball
	r_snowball.anim.PushBack({ 16, 716, 20, 18 });
	r_snowball.anim.PushBack({ 42, 710, 25, 24 });
	r_snowball.anim.PushBack({ 74, 707, 27, 28 });
	r_snowball.anim.PushBack({ 107, 704, 28, 31 });
	r_snowball.anim.PushBack({ 141, 703, 28, 33 });

	//Left snowball
	l_snowball.anim.PushBack({ 1179, 716, 20, 18 });
	l_snowball.anim.PushBack({ 1148, 710, 25, 24 });
	l_snowball.anim.PushBack({ 1115, 707, 27, 28 });
	l_snowball.anim.PushBack({ 1081, 704, 28, 31 });
	l_snowball.anim.PushBack({ 1048, 703, 28, 33 });

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

	switch (Enemy_Demon::life)
	{
	case 7:
		if()
	case 6:
	case 5:
	case 4:
	case 3:
	case 2:
	case 1:
	case 0:
		break;
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