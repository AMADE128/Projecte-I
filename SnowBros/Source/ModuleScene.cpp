#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

ModuleScene::ModuleScene()
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/background.png");
	App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);

	//Bottomside collider
	App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);

	//First two columns colliders
	App->collisions->AddCollider({ 1375, 0, 111, 96 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 600, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 625, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 640, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 665, 80);

	// TODO 1: Add a new wave of red birds

	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 800, 135);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 820, 135);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 850, 135);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 865, 135);

	// TODO 2: Add a new wave of brown cookies

	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 1000, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 1025, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 1050, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 1075, 100);

	// TODO 4: Create a new enemy type: The Mech


	return ret;
}

update_status ModuleScene::Update()
{
	App->render->camera.x += 3;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}