#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class GameOver : public Module
{
public:
	//Constructor
	GameOver(bool startEnabled);

	//Destructor
	~GameOver();

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
	SDL_Texture* GameOverTexture = nullptr;
	SDL_Texture* NinjaTexture = nullptr;
	SDL_Texture* RanaTexture = nullptr;
	SDL_Texture* MonoTexture = nullptr;
	SDL_Texture* DemonioTexture = nullptr;

	SDL_Rect GameOverRect = { 1440, 48, 378, 48 };

	Animation* currentAnimationNinja = nullptr;
	Animation* currentAnimationRana = nullptr;
	Animation* currentAnimationMono = nullptr;
	Animation* currentAnimationDemonio = nullptr;
	Animation Ninja;
	Animation Rana;
	Animation Mono;
	Animation Demonio;
};

#endif
