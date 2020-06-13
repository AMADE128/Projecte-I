#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

class Module;

struct Collider
{
	enum Type
	{
		NONE,
		GROUND,
		AIR,
		WALL,
		WALLPUSHR,
		WALLPUSHL,  //Wall that lets the player pass from one side
		PLAYER,
		ENEMY,
		PLAYER_SHOT,
		ENEMY_SHOT,
		GODMODE,
		FREEZE_BALL,
		

		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listener = nullptr;
};


#endif // !__COLLIDER_H_

