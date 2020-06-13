#include "SceneLevel3.h"

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


SceneLevel3::SceneLevel3(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel3::~SceneLevel3()
{

}

// Load assets
bool SceneLevel3::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture3 = App->textures->Load("Assets/Sprites/Maps/lvl3.png");
	App->audio->PlayMusic("Assets/Audio/Music/Stages/1.#035 Yukidama-Ondo (Stage 1, 3).ogg", 1.0f);

	//Bottomside collider
	App->collisions->AddCollider({ 40, 933, 1390, 60 }, Collider::Type::GROUND);

	//Platform colliders
	App->collisions->AddCollider({ 40, 780, 220, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 450, 780, 530, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1170, 780, 310, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 625, 625, 180, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 40, 625, 50, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1350, 625, 50, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 40, 471, 50, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 270, 471, 170, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 630, 471, 170, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 990, 471, 170, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1350, 471, 50, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 40, 319, 120, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 360, 319, 700, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1258, 319, 130, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 272, 161, 898, 2 }, Collider::Type::GROUND);

	//Fall colliders
	App->collisions->AddCollider({ 261, 777, 183, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 983, 777, 191, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 110, 622, 494, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 806, 622, 544, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 110, 460, 143, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 440, 460, 183, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 800, 460, 183, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1160, 460, 183, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 160, 316, 194, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1060, 316, 194, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 40, 155, 220, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1172, 155, 220, 2 }, Collider::Type::AIR);

	//First two columns colliders
	App->collisions->AddCollider({ 0, 0, 40, 1390 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1400, 0, 40, 1390 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 40, 670);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 1216, 670);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 300, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 1032, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::FROG, 1250, 205);
	App->enemies->AddEnemy(ENEMY_TYPE::FROG, 40, 205);

	App->enemies->win = false;

	App->enemies->Enable();
	App->player->Enable();
	App->particles->Enable();
	App->collisions->Enable();

	return ret;
}

update_status SceneLevel3::Update()
{
	//App->render->camera.x += 3; SOBRA 2: LO GUARDAMOS PARA CUANDO CAMBIE DE NIVEL Y SUBA HACIA ARRIBA

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel3::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture3, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel3::CleanUp()
{
	App->collisions->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->enemies->Disable();

	App->textures->Unload(bgTexture3);

	return true;
}