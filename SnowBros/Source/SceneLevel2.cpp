#include "SceneLevel2.h"

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


SceneLevel2::SceneLevel2(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel2::~SceneLevel2()
{

}

// Load assets
bool SceneLevel2::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture2 = App->textures->Load("Assets/Sprites/Maps/lvl2.png");
	App->audio->PlayMusic("Assets/Audio/Music/Stages/1.#035 Yukidama-Ondo (Stage 1, 3).ogg", 1.0f);

	//Bottomside collider
	App->collisions->AddCollider({ 40, 933, 1390, 60 }, Collider::Type::GROUND);

	//Platform colliders
	App->collisions->AddCollider({ 360, 780, 820, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 180, 625, 180, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 550, 625, 530, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 360, 470, 540, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1080, 470, 180, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 185, 318, 175, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 550, 318, 530, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 280, 160, 620, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1080, 160, 180, 2 }, Collider::Type::GROUND);

	//Fall colliders
	App->collisions->AddCollider({ 1170, 777, 300, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 40, 622, 135, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 360, 622, 190, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 900, 467, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1260, 467, 190, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 40, 316, 144, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 360, 316, 190, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 40, 157, 240, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 900, 157, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1260, 157, 190, 2 }, Collider::Type::AIR);

	//Last platform walls
	App->collisions->AddCollider({ 359, 635, 2, 155 }, Collider::Type::WALLPUSHR);
	App->collisions->AddCollider({ 359, 325, 2, 155 }, Collider::Type::WALLPUSHR);
	App->collisions->AddCollider({ 1080, 475, 2, 155 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 1080, 175, 2, 155 }, Collider::Type::WALLPUSHL);

	//First two columns colliders
	App->collisions->AddCollider({ 0, 0, 40, 1390 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1400, 0, 40, 1390 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::MONKEY, 370, 665);
	App->enemies->AddEnemy(ENEMY_TYPE::MONKEY, 900, 510);
	App->enemies->AddEnemy(ENEMY_TYPE::FROG, 650, 205);
	App->enemies->AddEnemy(ENEMY_TYPE::MONKEY, 750, 45);
	App->enemies->AddEnemy(ENEMY_TYPE::MONKEY, 290, 45);

	App->enemies->win = false;

	App->enemies->Enable();
	App->player->Enable();
	App->particles->Enable();
	App->collisions->Enable();

	return ret;
}

update_status SceneLevel2::Update()
{
	//App->render->camera.x += 3; SOBRA 2: LO GUARDAMOS PARA CUANDO CAMBIE DE NIVEL Y SUBA HACIA ARRIBA

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel2::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture2, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel2::CleanUp()
{
	App->collisions->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->enemies->Disable();

	//Mix_FreeMusic(App->audio->music);
	App->textures->Unload(bgTexture2);

	return true;
}