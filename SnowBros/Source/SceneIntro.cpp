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

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Menu & UI/logoblack.png");

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
	App->player->pHealth = 3;

	return ret;
}

update_status SceneIntro::Update()
{
	GamePad& pad = App->input->pads[0];
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneIntro::PostUpdate()
{
	// Draw everything ---
 	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}


bool SceneIntro::CleanUp()
{

	/*App->collisions->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->enemies->Disable();*/

	App->textures->Unload(bgTexture);

	return true;
}