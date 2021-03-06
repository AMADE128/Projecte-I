#include "Application.h"

#include "Module.h"
#include "SceneCredits.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "SceneIntro.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "SceneLevel3.h"
#include "SceneLevel4.h"
#include "SceneLevel5.h"
#include "SceneLevel6.h"
#include "SceneLevel7.h"
#include "SceneLevel8.h"
#include "SceneLevel9.h"
#include "SceneLevel10.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"
#include "GameOver.h"
#include "SceneWon.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen
	modules[0] = window = new ModuleWindow(true);
	modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);
	modules[3] = audio = new ModuleAudio(true);

	modules[4] = sceneIntro = new SceneIntro(false);
	modules[5] = sceneLevel_1 = new SceneLevel1(false);	
	modules[6] = sceneLevel_2 = new SceneLevel2(false);	
	modules[7] = sceneLevel_3 = new SceneLevel3(false);	
	modules[8] = sceneLevel_4 = new SceneLevel4(false);	
	modules[9] = sceneLevel_5 = new SceneLevel5(false);	
	modules[10] = sceneLevel_6 = new SceneLevel6(false);	
	modules[11] = sceneLevel_7 = new SceneLevel7(false);	
	modules[12] = sceneLevel_8 = new SceneLevel8(false);	
	modules[13] = sceneLevel_9 = new SceneLevel9(false);
	modules[14] = sceneLevel_10 = new SceneLevel10(false);		//Gameplay scene starts disabled
	modules[15] = sceneCredits = new SceneCredits(true);
	modules[16] = sceneWon = new SceneWon(false);
	modules[18] = player = new ModulePlayer(false);	//Player starts disabled
	modules[19] = particles = new ModuleParticles(false);
	modules[17] = enemies = new ModuleEnemies(false);	//Enemies start disabled
	modules[22] = gameOver = new GameOver(false);

	modules[20] = collisions = new ModuleCollisions(false);
	modules[21] = fade = new ModuleFadeToBlack(true);

	modules[24] = fonts = new ModuleFonts(true);
	modules[23] = render = new ModuleRender(true);
	
	
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : update_status::UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
