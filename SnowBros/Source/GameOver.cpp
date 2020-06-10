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
	Ninja.PushBack({ 207, 9, 66, 72 });
	Ninja.PushBack({ 15, 204, 63, 75 });
	Ninja.loop = true;
	Ninja.speed = 0.07f;

	Rana.PushBack({ 5, 3, 25, 26 });
	Rana.PushBack({ 34, 227, 28, 26  });
	Rana.loop = true;
	Rana.speed = 0.07f;
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
	Ninja.Update();
	Rana.Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status GameOver::PostUpdate()
{
	// Draw everything ---
	App->render->Blit(GameOverTexture, 450, 350, &GameOverRect);

	SDL_Rect rect = (&Ninja)->GetCurrentFrame();
	App->render->Blit(NinjaTexture, 800, 500, &rect);

	rect = (&Rana)->GetCurrentFrame();
	App->render->Blit(RanaTexture, 700, 500, &rect);

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