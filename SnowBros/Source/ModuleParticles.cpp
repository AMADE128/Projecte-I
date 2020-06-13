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
	player_shot = App->textures->Load("Assets/Sprites/Player/Nick_right_left.png");
	frog_particle = App->textures->Load("Assets/Sprites/Enemies/fire_ball.png");

	//Health face
	healthFace.anim.PushBack({ 112, 16, 32, 32 });
	healthFace.anim.speed = 0;

	//Right Shot
	shotright.anim.PushBack({ 16, 141, 7, 11 });
	shotright.anim.PushBack({ 31, 141, 7, 11 });
	shotright.speed.x = 10;
	shotright.lifetime = 180;
	shotright.anim.speed = 0.2f;

	//Left Shot
	shotleft.anim.PushBack({ 1190, 140, 13, 13 });
	shotleft.anim.PushBack({ 1175, 140, 13, 13 });
	shotleft.speed.x = -10;
	shotleft.lifetime = 180;
	shotleft.anim.speed = 0.2f;

	//left snowball
	snowball[0].anim.PushBack({ 12, 702, 28, 32 });
	snowball[1].anim.PushBack({ 41, 702, 28, 32 });
	snowball[2].anim.PushBack({ 74, 702, 28, 32 });
	snowball[3].anim.PushBack({ 107, 703, 28, 32 });
	snowball[4].anim.PushBack({ 140, 702, 28, 32 });

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

 	if (FirstPushBack == false)
	{
	path.PushBack({ 1, 0 }, 5, &shotright.anim);
	path.PushBack({ 1, 0.25 }, 3, &shotright.anim);
	path.PushBack({ 1, 0.5 }, 3, &shotright.anim);
	path.PushBack({ 1, 1 }, 2, &shotright.anim);
	path.PushBack({ 1, 1.5 }, 2, &shotright.anim);
	path.PushBack({ 1, 2 }, 2, &shotright.anim);
	path.PushBack({ 0.75, 4 }, 2, &shotright.anim);
	path.PushBack({ 0.75, 8 }, 2, &shotright.anim);
	path.PushBack({ 0.75, 12 }, 2, &shotright.anim);

	path.PushBack({ -1, 0 }, 5, &shotleft.anim);
	path.PushBack({ -1, 0.25 }, 3, &shotleft.anim);
	path.PushBack({ -1, 0.5 }, 3, &shotleft.anim);
	path.PushBack({ -1, 1 }, 2, &shotleft.anim);
	path.PushBack({ -1, 1.5 }, 2, &shotleft.anim);
	path.PushBack({ -1, 2 }, 2, &shotleft.anim);
	path.PushBack({ -0.75, 4 }, 2, &shotleft.anim);
	path.PushBack({ -0.75, 8 }, 2, &shotleft.anim);
	path.PushBack({ -0.75, 12 }, 2, &shotleft.anim);

	FirstPushBack = true;
	}

	//right & left fire ball
	l_fire_ball.anim.PushBack({ 96, 384, 96, 90 });
	l_fire_ball.anim.PushBack({ 96, 285, 96, 90 });
	l_fire_ball.anim.PushBack({ 96, 189, 96, 90 });
	l_fire_ball.anim.PushBack({ 96, 285, 96, 90 });
	l_fire_ball.anim.PushBack({ 96, 0, 96, 90 });
	l_fire_ball.speed.x = -3;
	l_fire_ball.lifetime = 220;
	l_fire_ball.anim.speed = 0.15f;
	l_fire_ball.anim.loop = false;

	r_fire_ball.anim.PushBack({ 197, 378, 96, 90 });
	r_fire_ball.anim.PushBack({ 197, 279, 96, 90 });
	r_fire_ball.anim.PushBack({ 197, 183, 96, 90 });
	r_fire_ball.anim.PushBack({ 198, 89, 96, 90 });
	r_fire_ball.anim.PushBack({ 200, 0, 96, 90 });
	r_fire_ball.speed.x = 3;
	r_fire_ball.lifetime = 220;
	r_fire_ball.anim.speed = 0.15f;
	r_fire_ball.anim.loop = false;

	//right & left fire ball explosions
	l_fire_death.anim.PushBack({ 0, 384, 96, 90 });
	l_fire_death.anim.PushBack({ 0, 294, 96, 90 });
	l_fire_death.anim.PushBack({ 0, 194, 96, 90 });
	l_fire_death.anim.PushBack({ 0, 96, 96, 90 });
	
	l_fire_death.speed.x = 0;
	l_fire_death.speed.y = 0;
	l_fire_death.anim.speed = 0.2f;
	l_fire_death.anim.loop = false;
	l_fire_death.lifetime = 35;

	r_fire_death.anim.PushBack({ 294, 384, 96, 90 });
	r_fire_death.anim.PushBack({ 294, 294, 96, 90 });
	r_fire_death.anim.PushBack({ 294, 194, 96, 90 });
	r_fire_death.anim.PushBack({ 294, 96, 96, 90 });
	
	r_fire_death.speed.x = 0;
	r_fire_death.speed.y = 0;
	r_fire_death.anim.speed = 0.2f;
	r_fire_death.anim.loop = false;
	r_fire_death.lifetime = 35;

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

	App->textures->Unload(player_shot);
	App->textures->Unload(frog_particle);

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			if (particles[i]->anim.frames[0].x == l_fire_ball.anim.frames[0].x)
			{
				AddParticle(l_fire_death, particles[i]->position.x, particles[i]->position.y, Collider::Type::GODMODE);
			}

			if (particles[i]->anim.frames[0].x == r_fire_ball.anim.frames[0].x)
			{
				AddParticle(r_fire_death, particles[i]->position.x, particles[i]->position.y, Collider::Type::GODMODE);
			}

			delete particles[i];
			particles[i] = nullptr;
			path.Reset();
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

		if (particle != nullptr && particle->isAlive && particle->anim.frames[0].x != shotright.anim.frames[0].x && particle->anim.frames[0].x != shotleft.anim.frames[0].x && particle->anim.frames[0].x != l_fire_ball.anim.frames[0].x && particle->anim.frames[0].x != r_fire_ball.anim.frames[0].x && particle->anim.frames[0].x != l_fire_death.anim.frames[0].x && particle->anim.frames[0].x != r_fire_death.anim.frames[0].x)
		{
			App->render->Blit(player_shot, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}

		if (particle != nullptr && particle->isAlive && particle->anim.frames[0].x == shotright.anim.frames[0].x && particle->anim.frames[0].x != l_fire_ball.anim.frames[0].x && particle->anim.frames[0].x != r_fire_ball.anim.frames[0].x && particle->anim.frames[0].x != l_fire_death.anim.frames[0].x && particle->anim.frames[0].x != r_fire_death.anim.frames[0].x)
		{
			path.Update();

			if (path.currentStep > 8)
			{
				path.currentStep = 8;
			}
			
			particle->position.x += path.steps[path.currentStep].speed.x;
			particle->position.y += path.steps[path.currentStep].speed.y;
			App->render->Blit(player_shot, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}

		if (particle != nullptr && particle->isAlive && particle->anim.frames[0].x == shotleft.anim.frames[0].x && particle->anim.frames[0].x != l_fire_ball.anim.frames[0].x && particle->anim.frames[0].x != r_fire_ball.anim.frames[0].x && particle->anim.frames[0].x != l_fire_death.anim.frames[0].x && particle->anim.frames[0].x != r_fire_death.anim.frames[0].x)
		{
			path.Update();

			if (path.currentStep < 9)
			{
				path.currentStep = 9;
			}

			if (path.currentStep > 16)
			{
				path.currentStep = 16;
			}

			particle->position.x += path.steps[path.currentStep].speed.x;
			particle->position.y += path.steps[path.currentStep].speed.y;
			App->render->Blit(player_shot, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}

		if (particle != nullptr && particle->isAlive && particle->anim.frames[0].y == l_fire_ball.anim.frames[0].y)
		{
			particle->position.x += particle->speed.x;
			App->render->Blit(frog_particle, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}

		if (particle != nullptr && particle->isAlive && particle->anim.frames[0].y == r_fire_ball.anim.frames[0].y)
		{
			particle->position.x += particle->speed.x;
			App->render->Blit(frog_particle, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}

		if (particle != nullptr && particle->isAlive && particle == &r_fire_death)
		{
			App->render->Blit(frog_particle, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}

		if (particle != nullptr && particle->isAlive && particle == &l_fire_death)
		{
			App->render->Blit(frog_particle, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
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