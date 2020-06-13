#include "SceneLevel4.h"

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


SceneLevel4::SceneLevel4(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel4::~SceneLevel4()
{

}

// Load assets
bool SceneLevel4::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture4 = App->textures->Load("Assets/Sprites/Maps/lvl4.png");
	App->audio->PlayMusic("Assets/Audio/Music/Stages/1.#035 Yukidama-Ondo (Stage 1, 3).ogg", 1.0f);

	//Bottomside collider
	App->collisions->AddCollider({ 40, 933, 1390, 60 }, Collider::Type::GROUND);

	//Platform colliders
	App->collisions->AddCollider({ 160, 780, 470, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 815, 780, 450, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 40, 625, 590, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 815, 625, 590, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 220, 471, 140, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 640, 471, 550, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 185, 319, 800, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 450, 160, 800, 2 }, Collider::Type::GROUND);

	//Fall colliders
	App->collisions->AddCollider({ 630, 777, 185, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 630, 622, 185, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 360, 460, 280, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 40, 460, 170, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1220, 460, 280, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 985, 316, 200, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 40, 155, 400, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1250, 155, 200, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 40, 315, 145, 2 }, Collider::Type::AIR);

	//Last platform walls
	App->collisions->AddCollider({ 160, 630, 2, 150 }, Collider::Type::WALLPUSHR);
	App->collisions->AddCollider({ 1260, 630, 2, 150 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 220, 325, 2, 150 }, Collider::Type::WALLPUSHR);
	App->collisions->AddCollider({ 170, 325, 2, 90 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 1210, 165, 2, 300 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 1260, 165, 2, 240 }, Collider::Type::WALLPUSHR);

	//First two columns colliders
	App->collisions->AddCollider({ 0, 0, 40, 1390 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1400, 0, 40, 1390 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::FROG, 170, 665);
	App->enemies->AddEnemy(ENEMY_TYPE::FROG, 1140, 665);
	App->enemies->AddEnemy(ENEMY_TYPE::MONKEY, 900, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::MONKEY, 650, 205);
	App->enemies->AddEnemy(ENEMY_TYPE::MONKEY, 750, 45);

	App->enemies->win = false;

	App->enemies->Enable();
	App->player->Enable();
	App->particles->Enable();
	App->collisions->Enable();

	return ret;
}

update_status SceneLevel4::Update()
{
	//App->render->camera.x += 3; SOBRA 2: LO GUARDAMOS PARA CUANDO CAMBIE DE NIVEL Y SUBA HACIA ARRIBA

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel4::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture4, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel4::CleanUp()
{
	App->collisions->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->enemies->Disable();

	App->textures->Unload(bgTexture4);

	return true;
}