#include "SceneLevel5.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


SceneLevel5::SceneLevel5(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel5::~SceneLevel5()
{

}

// Load assets
bool SceneLevel5::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Maps/lv5.png");
	App->audio->PlayMusic("Assets/Audio/Music/Stages/1.#035 Yukidama-Ondo (Stage 1, 3).ogg", 1.0f);

	//Bottomside collider
	App->collisions->AddCollider({ 40, 933, 1390, 60 }, Collider::Type::GROUND);

	//Platform colliders
	App->collisions->AddCollider({ 180, 780, 450, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 800, 780, 450, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 40, 625, 320, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1080, 625, 320, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 180, 471, 450, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 800, 471, 450, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 40, 319, 320, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1080, 319, 320, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 540, 319, 360, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 180, 160, 1080, 2 }, Collider::Type::GROUND);

	//Fall colliders
	App->collisions->AddCollider({ 40, 777, 140, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1250, 777, 140, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 360, 622, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 900, 622, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 40, 460, 140, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1250, 460, 140, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 360, 316, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 900, 316, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1260, 150, 140, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 40, 150, 140, 2 }, Collider::Type::AIR);

	//Last platform walls
	App->collisions->AddCollider({ 630, 165, 2, 150 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 810, 165, 2, 150 }, Collider::Type::WALLPUSHR);
	App->collisions->AddCollider({ 630, 680, 2, 100 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 810, 680, 2, 100 }, Collider::Type::WALLPUSHR);
	App->collisions->AddCollider({ 540, 325, 2, 380 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 900, 325, 2, 380 }, Collider::Type::WALLPUSHR);

	//First two columns colliders
	App->collisions->AddCollider({ 0, 0, 40, 1390 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1400, 0, 40, 1390 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 45, 510);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 1200, 510);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 400, 670);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 910, 670);
	

	App->enemies->win = false;

	App->enemies->Enable();
	App->player->Enable();
	App->particles->Enable();
	App->collisions->Enable();

	return ret;
}

update_status SceneLevel5::Update()
{
	//App->render->camera.x += 3; SOBRA 2: LO GUARDAMOS PARA CUANDO CAMBIE DE NIVEL Y SUBA HACIA ARRIBA

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel5::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel5::CleanUp()
{
	App->collisions->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->enemies->Disable();

	
	App->textures->Unload(bgTexture);

	return true;
}