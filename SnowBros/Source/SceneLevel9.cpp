#include "SceneLevel9.h"

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


SceneLevel9::SceneLevel9(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel9::~SceneLevel9()
{

}

// Load assets
bool SceneLevel9::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture9 = App->textures->Load("Assets/Sprites/Maps/lvl9.png");
	App->audio->PlayMusic("Assets/Audio/Music/Stages/1.#035 Yukidama-Ondo (Stage 1, 3).ogg", 1.0f);

	//Bottomside collider
	App->collisions->AddCollider({ 40, 933, 1390, 60 }, Collider::Type::GROUND);

	//Platform colliders
	App->collisions->AddCollider({ 160, 780, 460, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 160+460+190, 780, 460, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 40, 625, 230, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 270+180, 625, 540, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1170, 625, 230, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 160, 471, 460, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 160+460+190, 471, 460, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 40, 319, 140, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 540, 319, 360, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 360, 160, 720, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 1260, 319, 140, 2 }, Collider::Type::GROUND);

	//Fall colliders
	App->collisions->AddCollider({ 160+460, 777, 190, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 40+230, 622, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 270+180+540, 622, 180, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 160+460, 460, 190, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 185, 316, 175, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 258, 140, 100, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1080, 140, 100, 2 }, Collider::Type::AIR);
	App->collisions->AddCollider({ 1080, 316, 180, 2 }, Collider::Type::AIR);

	//Last platform walls
	App->collisions->AddCollider({ 530, 165, 2, 73*2 }, Collider::Type::WALLPUSHR);
	App->collisions->AddCollider({ 540+370, 165, 2, 73*2 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 361, 165, 2, 50 * 3 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 1080, 165, 2, 50 * 3 }, Collider::Type::WALLPUSHR);
	App->collisions->AddCollider({ 180, 325, 2, 73 * 2 }, Collider::Type::WALLPUSHR);
	App->collisions->AddCollider({ 1260, 325, 2, 73 * 2 }, Collider::Type::WALLPUSHL);
	App->collisions->AddCollider({ 160, 630, 2, 73 * 2 }, Collider::Type::WALLPUSHR);
	App->collisions->AddCollider({ 160 + 460 + 190+460, 630, 2, 73 * 2 }, Collider::Type::WALLPUSHL);

	//First two columns colliders
	App->collisions->AddCollider({ 0, 0, 40, 1390 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1400, 0, 40, 1390 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 700, 510-155*2);
	App->enemies->AddEnemy(ENEMY_TYPE::FROG, 45, 510);
	App->enemies->AddEnemy(ENEMY_TYPE::FROG, 1260, 510);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 400, 510+160);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 1050, 510 + 160);
	App->enemies->AddEnemy(ENEMY_TYPE::DEMON, 45, 500 + 160*2);

	App->enemies->win = false;

	App->enemies->Enable();
	App->player->Enable();
	App->particles->Enable();
	App->collisions->Enable();

	return ret;
}

update_status SceneLevel9::Update()
{
	//App->render->camera.x += 3; SOBRA 2: LO GUARDAMOS PARA CUANDO CAMBIE DE NIVEL Y SUBA HACIA ARRIBA

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel9::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture9, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel9::CleanUp()
{
	App->collisions->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->enemies->Disable();


	App->textures->Unload(bgTexture9);

	return true;
}