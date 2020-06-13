#include "SceneLevel7.h"

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


SceneLevel7::SceneLevel7(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel7::~SceneLevel7()
{

}

// Load assets
bool SceneLevel7::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture7 = App->textures->Load("Assets/Sprites/Maps/lvl7.png");
	App->audio->PlayMusic("Assets/Audio/Music/Stages/1.#035 Yukidama-Ondo (Stage 1, 3).ogg", 1.0f);

	//Bottomside collider
	App->collisions->AddCollider({ 40, 933, 1390, 60 }, Collider::Type::GROUND);

	//Platform colliders
	App->collisions->AddCollider({ 240, 780, 380, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 825, 780, 352, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 40, 700, 220, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 815+352, 700, 220, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 475+40, 625, 280, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 335, 625-80, 180, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1150, 625 - 80, 240, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 190, 625 - 160, 150, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 730, 625 - 160, 420, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 280, 625 - 315, 340, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1090, 625 - 315, 320, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 630, 625 - 385, 270, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 40, 625 - 465, 390, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 900, 625 - 465, 340, 2 }, Collider::Type::GROUND);

	//Fall colliders
	App->collisions->AddCollider({ 240 + 380, 777, 825-(240+380), 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 270, 667, 170, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1060, 667, 100, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 800, 617, 170, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 550, 617 - 160, 170, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 350, 617 - 210, 100, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 90, 617 - 170, 100, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1170, 617 - 190, 170, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 970, 617 - 320, 120, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 150, 617 - 320, 120, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 500, 617 - 440, 120, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 440, 617 - 490, 120, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 780, 617 - 490, 120, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1230, 617 - 490, 120, 2 }, Collider::Type::AIR);

	//Last platform walls
	App->collisions->AddCollider({ 1170, 705, 2, 76 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 900, 166, 2, 76 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 630, 242, 2, 76 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 250, 701, 2, 76 }, Collider::Type::WALLPUSHR);
	App->collisions->AddCollider({ 510, 550, 2, 76 }, Collider::Type::WALLPUSHR);
	App->collisions->AddCollider({ 340, 470, 2, 76 }, Collider::Type::WALLPUSHR);
	App->collisions->AddCollider({ 1140, 470, 2, 76 }, Collider::Type::WALLPUSHR);

	//First two columns colliders
	App->collisions->AddCollider({ 0, 0, 40, 1390 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1400, 0, 40, 1390 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 400, 670);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 200, 370);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 200, 50);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 900, 670);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 1200, 590);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 950, 50);

	App->enemies->win = false;

	App->enemies->Enable();
	App->player->Enable();
	App->particles->Enable();
	App->collisions->Enable();

	return ret;
}

update_status SceneLevel7::Update()
{
	//App->render->camera.x += 3; SOBRA 2: LO GUARDAMOS PARA CUANDO CAMBIE DE NIVEL Y SUBA HACIA ARRIBA

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel7::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture7, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel7::CleanUp()
{
	App->collisions->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->enemies->Disable();


	App->textures->Unload(bgTexture7);

	return true;
}