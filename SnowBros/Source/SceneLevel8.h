#ifndef __SCENE_LEVEL8_H__
#define __SCENE_LEVEL8_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel8 : public Module
{
public:
	//Constructor
	SceneLevel8(bool startEnabled);

	//Destructor
	~SceneLevel8();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	bool CleanUp();

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture8 = nullptr;

	// The sprite rectangle for the ground
	SDL_Texture* starsTexture = nullptr;
};

#endif

