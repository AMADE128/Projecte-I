#include "SceneCredits.h"
#include "SceneIntro.h"
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

SceneCredits::SceneCredits(bool startEnabled) : Module(startEnabled)
{

}

SceneCredits::~SceneCredits()
{

}

// Load assets
bool SceneCredits::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTextureCredits = App->textures->Load("Assets/Sprites/Menu & UI/AprendingTeam.png");

	if (App->enemies->IsEnabled() == true)
	{
		App->enemies->Disable();
	}
	if (App->player->IsEnabled() == true)
	{
		App->player->Disable();
	}
	if (App->particles->IsEnabled() == true)
	{
		App->particles->Disable();
	}
	if (App->collisions->IsEnabled() == true)
	{
		App->collisions->Disable();
	}

	App->player->score = 0;

	return ret;
}

update_status SceneCredits::Update()
{
	GamePad& pad = App->input->pads[0];
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneCredits::PostUpdate()
{
	// Draw everything ---
	App->render->Blit(bgTextureCredits, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}


bool SceneCredits::CleanUp()
{

	/*App->collisions->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->enemies->Disable();*/

	App->textures->Unload(bgTextureCredits);

	return true;
}