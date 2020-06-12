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

	bgTexture = App->textures->Load("Assets/Sprites/Maps/lv8.png");
	App->audio->PlayMusic("Assets/Audio/Music/Stages/1.#035 Yukidama-Ondo (Stage 1, 3).ogg", 1.0f);

	//Bottomside collider
	App->collisions->AddCollider({ 40, 933, 1390, 60 }, Collider::Type::GROUND);

	//Platform colliders
	App->collisions->AddCollider({ 40, 780, 300, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 535, 780, 352, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1090, 780, 310, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 275, 625, 880, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 40, 471, 570, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 815, 471, 583, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 185, 319, 175, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 362, 241, 698, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1061, 319, 175, 2 }, Collider::Type::GROUND);

	//Fall colliders
	App->collisions->AddCollider({ 341, 777, 193, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 888, 777, 201, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 40, 622, 234, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1156, 622, 244, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 611, 460, 203, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 40, 316, 144, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 258, 200, 100, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1061, 200, 100, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1237, 316, 163, 2 }, Collider::Type::AIR);

	//Last platform walls
	App->collisions->AddCollider({ 361, 245, 2, 76 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 1060, 245, 2, 76 }, Collider::Type::WALLPUSHR);

	//First two columns colliders
	App->collisions->AddCollider({ 0, 0, 40, 1390 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1400, 0, 40, 1390 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 400, 120);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 916, 120);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 250, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 1132, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 372, 510);

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
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel8::CleanUp()
{
	App->collisions->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->enemies->Disable();
	Mix_FreeMusic(App->audio->music);

	SDL_DestroyTexture(bgTexture);

	return true;
}