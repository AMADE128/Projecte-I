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
#include "ModuleFonts.h"

#include <stdio.h>

#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL.h"

GameOver::GameOver(bool startEnabled) : Module(startEnabled)
{
	Ninja.PushBack({ 207, 9, 66, 72 });
	Ninja.PushBack({ 15, 204, 63, 75 });
	Ninja.loop = true;
	Ninja.speed = 0.05f;

	Rana.PushBack({ 5, 2, 25, 27 });
	Rana.PushBack({ 34, 226, 28, 27  });
	Rana.loop = true;
	Rana.speed = 0.05f;

	Mono.PushBack({ 993, 39, 66, 61 });
	Mono.PushBack({ 887, 351, 66, 61 });
	Mono.loop = true;
	Mono.speed = 0.05f;

	Demonio.PushBack({ 290, 2, 27, 27 });
	Demonio.PushBack({ 194, 66, 27, 27 });
	Demonio.loop = true;
	Demonio.speed = 0.05f;
}

GameOver::~GameOver()
{

}

// Load assets
bool GameOver::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	startTime = SDL_GetTicks();

	GameOverTexture = App->textures->Load("Assets/Sprites/Menu & UI/LetterANDOthers.png");
	NinjaTexture = App->textures->Load("Assets/Sprites/Enemies/brujo barbiazul.png");
	RanaTexture = App->textures->Load("Assets/Sprites/Enemies/Rana.png");
	MonoTexture = App->textures->Load("Assets/Sprites/Enemies/mono.png");
	DemonioTexture = App->textures->Load("Assets/Sprites/Enemies/Demonio.png");

	char life_score_Table[] = { "0123456789" };
	ScoreFont = App->fonts->Load("Assets/Sprites/Menu & UI/numbers.png",life_score_Table, 1);
	
	
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
	Mono.Update();
	Demonio.Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status GameOver::PostUpdate()
{
	// Draw everything ---
	App->render->Blit(GameOverTexture, 450, 350, &GameOverRect);

	SDL_Rect rect = (&Ninja)->GetCurrentFrame();
	App->render->Blit(NinjaTexture, 915, 500, &rect);

	rect = (&Rana)->GetCurrentFrame();
	App->render->Blit(RanaTexture, 765, 501, &rect);

	rect = (&Mono)->GetCurrentFrame();
	App->render->Blit(MonoTexture, 615, 500, &rect);

	rect = (&Demonio)->GetCurrentFrame();
	App->render->Blit(DemonioTexture, 465, 500, &rect);

	sprintf_s(App->player->scoreText, 10, "%d", App->player->score);
	App->fonts->BlitText(1200, 53, ScoreFont, App->player->scoreText);

	actualTime = SDL_GetTicks();

	if (actualTime - startTime >= 3000)
	{
		App->fade->FadeToBlack((Module*)App->gameOver, (Module*)App->sceneIntro, 120);
	}

	return update_status::UPDATE_CONTINUE;
}


bool GameOver::CleanUp()
{

	App->collisions->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->enemies->Disable();

	App->textures->Unload(GameOverTexture);
	App->textures->Unload(NinjaTexture);
	App->textures->Unload(RanaTexture);
	App->textures->Unload(MonoTexture);
	App->textures->Unload(DemonioTexture);


	return true;
}