#include "SceneWon.h"

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

SceneWon::SceneWon(bool startEnabled) : Module(startEnabled)
{

}

SceneWon::~SceneWon()
{

}

// Load assets
bool SceneWon::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTextureWon = App->textures->Load("Assets/Sprites/Menu & UI/won_screen.png");

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

update_status SceneWon::Update()
{
	GamePad& pad = App->input->pads[0];
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneWon::PostUpdate()
{
	// Draw everything ---
	App->render->Blit(bgTextureWon, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}


bool SceneWon::CleanUp()
{

	/*App->collisions->Disable();
	App->particles->Disable();
	App->player->Disable();
	App->enemies->Disable();*/

	App->textures->Unload(bgTextureWon);

	return true;
}