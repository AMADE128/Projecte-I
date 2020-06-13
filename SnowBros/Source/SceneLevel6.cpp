#include "SceneLevel6.h"

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


SceneLevel6::SceneLevel6(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel6::~SceneLevel6()
{

}

// Load assets
bool SceneLevel6::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture6 = App->textures->Load("Assets/Sprites/Maps/lv6.png");
	App->audio->PlayMusic("Assets/Audio/Music/Stages/1.#035 Yukidama-Ondo (Stage 1, 3).ogg", 1.0f);

	//Bottomside collider
	App->collisions->AddCollider({ 40, 933, 1390, 60 }, Collider::Type::GROUND);

	//Platform colliders
	App->collisions->AddCollider({ 40, 780, 140, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 360, 780, 720, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1260, 780, 140, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 40, 625, 140, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1260, 625, 140, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 40, 471, 140, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1260, 471, 140, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 360, 471, 270, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 810, 471, 270, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 40, 319, 320, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1080, 319, 320, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 272, 161, 898, 2 }, Collider::Type::GROUND);

	//Fall colliders
	App->collisions->AddCollider({ 180, 777, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1080, 777, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 180, 622, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1080, 622, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 180, 460, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 630, 460, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1080, 460, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 40+320, 316, 1080-360, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 40, 155, 220, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1172, 155, 220, 2 }, Collider::Type::AIR);

	//Last platform walls
	App->collisions->AddCollider({ 361, 472, 2, 160 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 810, 472, 2, 160 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 361+270, 472, 2, 160 }, Collider::Type::WALLPUSHR);
	App->collisions->AddCollider({ 810+270, 472, 2, 160 }, Collider::Type::WALLPUSHR);
	

	//First two columns colliders
	App->collisions->AddCollider({ 0, 0, 40, 1390 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1400, 0, 40, 1390 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 700, 670);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 45, 670-160);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 1280, 670-160);
	App->enemies->AddEnemy(ENEMY_TYPE::FROG, 880, 670-160*2);
	App->enemies->AddEnemy(ENEMY_TYPE::FROG, 450, 670-160*2);
	App->enemies->AddEnemy(ENEMY_TYPE::FROG, 650, 670 - 156 * 4);

	App->enemies->win = false;

	App->enemies->Enable();
	App->player->Enable();
	App->particles->Enable();
	App->collisions->Enable();

	return ret;
}

update_status SceneLevel6::Update()
{
	//App->render->camera.x += 3; SOBRA 2: LO GUARDAMOS PARA CUANDO CAMBIE DE NIVEL Y SUBA HACIA ARRIBA

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel6::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture6, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel6::CleanUp()
{
	App->collisions->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->enemies->Disable();


	App->textures->Unload(bgTexture6);

	return true;
}