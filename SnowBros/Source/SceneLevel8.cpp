#include "SceneLevel8.h"

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


SceneLevel8::SceneLevel8(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel8::~SceneLevel8()
{

}

// Load assets
bool SceneLevel8::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture8 = App->textures->Load("Assets/Sprites/Maps/lv8.png");
	App->audio->PlayMusic("Assets/Audio/Music/Stages/1.#035 Yukidama-Ondo (Stage 1, 3).ogg", 1.0f);

	//Bottomside collider
	App->collisions->AddCollider({ 40, 933, 1390, 60 }, Collider::Type::GROUND);

	//Platform colliders
	App->collisions->AddCollider({ 40, 780, 140, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 180 * 2, 780, 720, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1260, 780, 140, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 180, 625, 390, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 870, 625, 390, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 40, 471, 580, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 815, 471, 580, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 270, 319, 180, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 270 + 180, 241, 540, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 270 + 180 + 540, 319, 180, 2 }, Collider::Type::GROUND);

	//Fall colliders
	App->collisions->AddCollider({ 180, 777, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 180 * 2 + 720, 777, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 40, 622, 140, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1260, 622, 140, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 620, 460, 190, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 40, 316, 230, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 270, 200, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 270 + 180 + 540, 200, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 270 + 180 + 540 + 180, 316, 230, 2 }, Collider::Type::AIR);

	//Last platform walls
	App->collisions->AddCollider({ 270 + 180, 245, 2, 76 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 270 + 180 + 540, 245, 2, 76 }, Collider::Type::WALLPUSHR);
	App->collisions->AddCollider({ 180 + 390, 475, 2, 140 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 40 + 580, 475, 2, 170 }, Collider::Type::WALLPUSHR);
	App->collisions->AddCollider({ 815, 475, 2, 170 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 870, 475, 2, 140 }, Collider::Type::WALLPUSHR);

	//First two columns colliders
	App->collisions->AddCollider({ 0, 0, 40, 1390 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1400, 0, 40, 1390 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 740, 120);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 320, 205);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 1050, 205);
	App->enemies->AddEnemy(ENEMY_TYPE::FROG, 170, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::FROG, 1170, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 45, 510 + 160);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 740, 510 + 160);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 1280, 510 + 160);

	App->enemies->win = false;

	App->enemies->Enable();
	App->player->Enable();
	App->particles->Enable();
	App->collisions->Enable();

	return ret;
}

update_status SceneLevel8::Update()
{
	//App->render->camera.x += 3; SOBRA 2: LO GUARDAMOS PARA CUANDO CAMBIE DE NIVEL Y SUBA HACIA ARRIBA

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel8::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture8, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel8::CleanUp()
{
	App->textures->Unload(bgTexture8);
	App->collisions->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->enemies->Disable();

	

	return true;
}