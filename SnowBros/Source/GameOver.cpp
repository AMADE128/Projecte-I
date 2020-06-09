#include "GameOver.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemies.h"
#include "Globals.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL.h"

GameOver::GameOver(bool startEnabled) : Module(startEnabled)
{

}

GameOver::~GameOver()
{

}

// Load assets
bool GameOver::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	GameOverTexture = App->textures->Load("Assets/Sprites/Menu & UI/LetterANDOthers.png");
	NinjaTexture = App->textures->Load("Assets/Sprites/Enemies/brujo barbiazul.png");
	RanaTexture = App->textures->Load("Assets/Sprites/Enemies/Rana.png");
	MonoTexture = App->textures->Load("Assets/Sprites/Enemies/mono.png");
	DemonioTexture = App->textures->Load("Assets/Sprites/Enemies/Demonio.png");
	
	
	App->enemies->Disable();
	App->player->Disable();
	App->particles->Disable();
	App->collisions->Disable();

	return ret;
}

update_status GameOver::Update()
{
	//SDL_GetTicks

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status GameOver::PostUpdate()
{
	// Draw everything ---
	App->render->Blit(GameOverTexture, 20, 20, &GameOverRect); //1539 147 570 90

	return update_status::UPDATE_CONTINUE;
}


bool GameOver::CleanUp()
{

	App->collisions->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->enemies->Disable();

	SDL_DestroyTexture(GameOverTexture);
	SDL_DestroyTexture(NinjaTexture);
	SDL_DestroyTexture(RanaTexture);
	SDL_DestroyTexture(MonoTexture);
	SDL_DestroyTexture(DemonioTexture);


	return true;
}