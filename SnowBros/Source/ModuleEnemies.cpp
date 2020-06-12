#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include <stdio.h>

#include "Enemy.h"
#include "Enemy_Demon.h"
#include "Frog.h"

#include "SDL/include/SDL.h"

#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	demon = App->textures->Load("Assets/Sprites/Enemies/Demonio.png");
	frog = App->textures->Load("Assets/Sprites/Enemies/Rana.png");

	char life_score_Table[] = { "0123456789" };
	enemydiesFont = App->fonts->Load("Assets/Sprites/Menu & UI/numbers.png", life_score_Table, 1);

	//enemyDestroyedFx = App->audio->LoadFx("Assets/");

	return true;
}

update_status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();
	char life_score_Table[] = { "0123456789" };

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->life > 2)
			enemies[i]->Update();
		int time = SDL_GetTicks();
		if (enemies[i] != nullptr && time - enemies[i]->current_time >= 10000)
		{
			App->fonts->UnLoad(enemydiesFont);
			//enemydiesFont = App->fonts->Load("Assets/Sprites/Menu & UI/numbers.png", life_score_Table, 1);
		}
	}

	HandleEnemiesDespawn();

	WinCondition();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->life > 2)
		{
			enemies[i]->Draw();
		}

		if (enemies[i] != nullptr && enemies[i]->life <= 2)
		{
			sprintf_s(enemydiesText, 10, "%d", scoreD);
			App->fonts->BlitText(enemies[i]->position.x, enemies[i]->position.y - 50, enemydiesFont, enemydiesText);
			enemies[i]->current_time = SDL_GetTicks();
		}
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	App->textures->Unload(demon);
	App->textures->Unload(frog);

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == ENEMY_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	//// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->life < 2)
			{
				delete enemies[i];
				enemies[i] = nullptr;
			}
	    }
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
			case ENEMY_TYPE::DEMON:
				enemies[i] = new Enemy_Demon(info.x, info.y);
				enemies[i]->texture = demon;
				break;
			case ENEMY_TYPE::FROG:
				enemies[i] = new Frog(info.x, info.y);
				enemies[i]->texture = frog;
				break;
			}
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision

			delete enemies[i];
			enemies[i] = nullptr;
			break;
		}
	}
}

void ModuleEnemies::Fall(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->Fall(c2); //Notify the enemy of a collision
			break;
		}
	}
}

void ModuleEnemies::StopMovement(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->StopMovement(c2); //Notify the enemy of a collision
			break;
		}
	}
}

void ModuleEnemies::Freeze(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->Freeze(c2); //Notify the enemy of a collision
			break;
		}
	}
}

void ModuleEnemies::WinCondition() {
	int wincondition = 0;
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (enemies[i] != nullptr)
		{
			wincondition++;
		}
	}
	if (wincondition == 0)
	{
		if (App->modules[5]->IsEnabled() == true)
		{
			win = true;
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_2, 90);
		}
		else if (App->modules[6]->IsEnabled() == true) {
			win = true;
			App->fade->FadeToBlack((Module*)App->sceneLevel_2, (Module*)App->sceneLevel_3, 90);
		}
		else if (App->modules[7]->IsEnabled() == true) {
			win = true;
			App->fade->FadeToBlack((Module*)App->sceneLevel_3, (Module*)App->sceneLevel_4, 90);
		}
		else if (App->modules[8]->IsEnabled() == true) {
			win = true;
			App->fade->FadeToBlack((Module*)App->sceneLevel_4, (Module*)App->sceneLevel_5, 90);
		}
		else if (App->modules[9]->IsEnabled() == true) {
			win = true;
			App->fade->FadeToBlack((Module*)App->sceneLevel_5, (Module*)App->sceneLevel_6, 90);
		}
		else if (App->modules[10]->IsEnabled() == true) {
			win = true;
			App->fade->FadeToBlack((Module*)App->sceneLevel_6, (Module*)App->sceneLevel_7, 90);
		}
	}
}

