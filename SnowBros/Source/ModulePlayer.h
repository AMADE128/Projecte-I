#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

#define SPEED_Y 2

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	bool CleanUp() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	void StopMovement(Collider* c1, Collider* c2) override;

	void StopMovementY(Collider* c1, Collider* c2) override;

	void Fall(Collider* c1, Collider* c2) override;

	void PushR(Collider* c1, Collider* c2) override;

	void PushL(Collider* c1, Collider* c2) override;

	void BallPush(Collider* c1, Collider* c2) override;

	//Player Health

	int pHealth = 3;

	bool fontstop = false;

	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed_x = 2;
	float speed_y = SPEED_Y;

	bool rightCollision;
	bool leftCollision;

	bool fall;

	bool wallCollision = false;

	// The player spritesheets loaded into an SDL_Texture
	SDL_Texture* spritesheet = nullptr;
	SDL_Texture* score_bg = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation r_idleAnim;
	Animation l_idleAnim;
	Animation rightjumpAnim;
	Animation leftjumpAnim;
	Animation fallRightAnim;
	Animation fallLeftAnim;
	Animation sideRightAnim;
	Animation sideLeftAnim;
	Animation winAnim;
	Animation r_shootAnim;
	Animation l_shootAnim;
	Animation r_jumpShoot;
	Animation l_jumpShoot;
	Animation deathAnim;

	//Chech ground collision
	bool groundCollision;

	//Last jumping Sprites
	SDL_Rect lastLeftJumpSprite;
	SDL_Rect lastRightJumpSprite;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// A flag to detect when the player is pushing a snowball
	bool pushing = false;

	// A countdown to when the player gets destroyed. After a while, the game exits
	uint destroyedCountdown = 200;

	uint score = 000;
	int scoreFont = -1;
	int lifeFont = -1;
	char lifeText[10] = { "\0" };
	char scoreText[10] = { "\0" };

	bool godmode = false;
	bool death = false;
	int deathtime = 120;

	// Sound effects indices
	uint shotFx = 0;
	uint looseFx = 0;
	uint deathFx = 0;
	uint explosionFx = 0;

	bool debugGamepadInfo = false;

};

#endif //!__MODULE_PLAYER_H__
