#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "Enemy_Demon.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = NOTHING;
	matrix[Collider::Type::WALL][Collider::Type::GROUND] = NOTHING;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = NOTHING;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = NOTHING;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = NOTHING;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = NOTHING;
	matrix[Collider::Type::WALL][Collider::Type::AIR] = NOTHING;
	matrix[Collider::Type::WALL][Collider::Type::NONE] = NOTHING;
	matrix[Collider::Type::WALL][Collider::Type::WALLPUSHR] = NOTHING;
	matrix[Collider::Type::WALL][Collider::Type::WALLPUSHL] = NOTHING;
	matrix[Collider::Type::WALL][Collider::Type::GODMODE] = NOTHING;
	matrix[Collider::Type::WALL][Collider::Type::FREEZE_BALL] = NOTHING;

	matrix[Collider::Type::GROUND][Collider::Type::WALL] = NOTHING;
	matrix[Collider::Type::GROUND][Collider::Type::GROUND] = NOTHING;
	matrix[Collider::Type::GROUND][Collider::Type::PLAYER] = NOTHING;
	matrix[Collider::Type::GROUND][Collider::Type::ENEMY] = NOTHING;
	matrix[Collider::Type::GROUND][Collider::Type::PLAYER_SHOT] = NOTHING;
	matrix[Collider::Type::GROUND][Collider::Type::ENEMY_SHOT] = NOTHING;
	matrix[Collider::Type::GROUND][Collider::Type::AIR] = NOTHING;
	matrix[Collider::Type::GROUND][Collider::Type::NONE] = NOTHING;
	matrix[Collider::Type::GROUND][Collider::Type::WALLPUSHR] = NOTHING;
	matrix[Collider::Type::GROUND][Collider::Type::WALLPUSHL] = NOTHING;
	matrix[Collider::Type::GROUND][Collider::Type::GODMODE] = NOTHING;
	matrix[Collider::Type::GROUND][Collider::Type::FREEZE_BALL] = NOTHING;

	matrix[Collider::Type::AIR][Collider::Type::WALL] = NOTHING;
	matrix[Collider::Type::AIR][Collider::Type::GROUND] = NOTHING;
	matrix[Collider::Type::AIR][Collider::Type::PLAYER] = FALL;
	matrix[Collider::Type::AIR][Collider::Type::ENEMY] = FALL;
	matrix[Collider::Type::AIR][Collider::Type::PLAYER_SHOT] = NOTHING;
	matrix[Collider::Type::AIR][Collider::Type::ENEMY_SHOT] = NOTHING;
	matrix[Collider::Type::AIR][Collider::Type::AIR] = NOTHING;
	matrix[Collider::Type::AIR][Collider::Type::NONE] = NOTHING;
	matrix[Collider::Type::AIR][Collider::Type::WALLPUSHR] = NOTHING;
	matrix[Collider::Type::AIR][Collider::Type::WALLPUSHL] = NOTHING;
	matrix[Collider::Type::AIR][Collider::Type::GODMODE] = NOTHING;
	matrix[Collider::Type::AIR][Collider::Type::FREEZE_BALL] = FALL;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = STOP;
	matrix[Collider::Type::PLAYER][Collider::Type::GROUND] = STOP_Y;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = NOTHING;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = DIE;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = NOTHING;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = DIE;
	matrix[Collider::Type::PLAYER][Collider::Type::AIR] = FALL;
	matrix[Collider::Type::PLAYER][Collider::Type::NONE] = NOTHING;
	matrix[Collider::Type::PLAYER][Collider::Type::WALLPUSHR] = PUSHR;
	matrix[Collider::Type::PLAYER][Collider::Type::WALLPUSHL] = PUSHL;
	matrix[Collider::Type::PLAYER][Collider::Type::GODMODE] = NOTHING;
	matrix[Collider::Type::PLAYER][Collider::Type::FREEZE_BALL] = PUSH;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = STOP;
	matrix[Collider::Type::ENEMY][Collider::Type::GROUND] = STOP_Y;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = NOTHING;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = NOTHING;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] =  FREEZE;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = NOTHING;
	matrix[Collider::Type::ENEMY][Collider::Type::AIR] = FALL;
	matrix[Collider::Type::ENEMY][Collider::Type::NONE] = NOTHING;
	matrix[Collider::Type::ENEMY][Collider::Type::WALLPUSHR] = STOP;
	matrix[Collider::Type::ENEMY][Collider::Type::WALLPUSHL] = STOP;
	matrix[Collider::Type::ENEMY][Collider::Type::GODMODE] = NOTHING;
	matrix[Collider::Type::ENEMY][Collider::Type::FREEZE_BALL] = DIE;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = DIE;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::GROUND] = DIE;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = NOTHING;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = DIE, NOTHING;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = NOTHING;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = NOTHING;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::AIR] = NOTHING;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::NONE] = DIE;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALLPUSHR] = DIE;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALLPUSHL] = DIE;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::GODMODE] = NOTHING;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::FREEZE_BALL] = DIE;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = DIE;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::GROUND] = DIE;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = DIE;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = NOTHING;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = NOTHING;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = DIE;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::AIR] = NOTHING;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::NONE] = NOTHING;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALLPUSHR] = DIE;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALLPUSHL] = DIE;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::GODMODE] = NOTHING;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::FREEZE_BALL] = DIE;

	matrix[Collider::Type::NONE][Collider::Type::WALL] = NOTHING;
	matrix[Collider::Type::NONE][Collider::Type::GROUND] = NOTHING;
	matrix[Collider::Type::NONE][Collider::Type::PLAYER] = NOTHING;
	matrix[Collider::Type::NONE][Collider::Type::ENEMY] = NOTHING;
	matrix[Collider::Type::NONE][Collider::Type::PLAYER_SHOT] = FREEZE;
	matrix[Collider::Type::NONE][Collider::Type::ENEMY_SHOT] = NOTHING;
	matrix[Collider::Type::NONE][Collider::Type::AIR] = NOTHING;
	matrix[Collider::Type::NONE][Collider::Type::NONE] = NOTHING;
	matrix[Collider::Type::NONE][Collider::Type::WALLPUSHR] = NOTHING;
	matrix[Collider::Type::NONE][Collider::Type::WALLPUSHL] = NOTHING;
	matrix[Collider::Type::NONE][Collider::Type::GODMODE] = NOTHING;
	matrix[Collider::Type::NONE][Collider::Type::FREEZE_BALL] = NOTHING;

	matrix[Collider::Type::WALLPUSHR][Collider::Type::WALL] = NOTHING;
	matrix[Collider::Type::WALLPUSHR][Collider::Type::GROUND] = NOTHING;
	matrix[Collider::Type::WALLPUSHR][Collider::Type::PLAYER] = NOTHING;
	matrix[Collider::Type::WALLPUSHR][Collider::Type::ENEMY] = NOTHING;
	matrix[Collider::Type::WALLPUSHR][Collider::Type::PLAYER_SHOT] = NOTHING;
	matrix[Collider::Type::WALLPUSHR][Collider::Type::ENEMY_SHOT] = NOTHING;
	matrix[Collider::Type::WALLPUSHR][Collider::Type::AIR] = NOTHING;
	matrix[Collider::Type::WALLPUSHR][Collider::Type::NONE] = NOTHING;
	matrix[Collider::Type::WALLPUSHR][Collider::Type::WALLPUSHR] = NOTHING;
	matrix[Collider::Type::WALLPUSHR][Collider::Type::WALLPUSHL] = NOTHING;
	matrix[Collider::Type::WALLPUSHR][Collider::Type::GODMODE] = NOTHING;
	matrix[Collider::Type::WALLPUSHR][Collider::Type::FREEZE_BALL] = NOTHING;

	matrix[Collider::Type::WALLPUSHL][Collider::Type::WALL] = NOTHING;
	matrix[Collider::Type::WALLPUSHL][Collider::Type::GROUND] = NOTHING;
	matrix[Collider::Type::WALLPUSHL][Collider::Type::PLAYER] = NOTHING;
	matrix[Collider::Type::WALLPUSHL][Collider::Type::ENEMY] = NOTHING;
	matrix[Collider::Type::WALLPUSHL][Collider::Type::PLAYER_SHOT] = NOTHING;
	matrix[Collider::Type::WALLPUSHL][Collider::Type::ENEMY_SHOT] = NOTHING;
	matrix[Collider::Type::WALLPUSHL][Collider::Type::AIR] = NOTHING;
	matrix[Collider::Type::WALLPUSHL][Collider::Type::NONE] = NOTHING;
	matrix[Collider::Type::WALLPUSHL][Collider::Type::WALLPUSHR] = NOTHING;
	matrix[Collider::Type::WALLPUSHL][Collider::Type::WALLPUSHL] = NOTHING;
	matrix[Collider::Type::WALLPUSHL][Collider::Type::GODMODE] = NOTHING;
	matrix[Collider::Type::WALLPUSHL][Collider::Type::FREEZE_BALL] = NOTHING;

	matrix[Collider::Type::GODMODE][Collider::Type::WALL] = NOTHING;
	matrix[Collider::Type::GODMODE][Collider::Type::GROUND] = NOTHING;
	matrix[Collider::Type::GODMODE][Collider::Type::PLAYER] = NOTHING;
	matrix[Collider::Type::GODMODE][Collider::Type::ENEMY] = NOTHING;
	matrix[Collider::Type::GODMODE][Collider::Type::PLAYER_SHOT] = NOTHING;
	matrix[Collider::Type::GODMODE][Collider::Type::ENEMY_SHOT] = NOTHING;
	matrix[Collider::Type::GODMODE][Collider::Type::AIR] = NOTHING;
	matrix[Collider::Type::GODMODE][Collider::Type::NONE] = NOTHING;
	matrix[Collider::Type::GODMODE][Collider::Type::WALLPUSHR] = NOTHING;
	matrix[Collider::Type::GODMODE][Collider::Type::WALLPUSHL] = NOTHING;
	matrix[Collider::Type::GODMODE][Collider::Type::GODMODE] = NOTHING;
	matrix[Collider::Type::GODMODE][Collider::Type::FREEZE_BALL] = NOTHING;

	matrix[Collider::Type::FREEZE_BALL][Collider::Type::WALL] = STOP;
	matrix[Collider::Type::FREEZE_BALL][Collider::Type::GROUND] = STOP_Y;
	matrix[Collider::Type::FREEZE_BALL][Collider::Type::PLAYER] = PUSH;
	matrix[Collider::Type::FREEZE_BALL][Collider::Type::ENEMY] = NOTHING;
	matrix[Collider::Type::FREEZE_BALL][Collider::Type::PLAYER_SHOT] = FREEZE;
	matrix[Collider::Type::FREEZE_BALL][Collider::Type::ENEMY_SHOT] = NOTHING;
	matrix[Collider::Type::FREEZE_BALL][Collider::Type::AIR] = FALL;
	matrix[Collider::Type::FREEZE_BALL][Collider::Type::NONE] = NOTHING;
	matrix[Collider::Type::FREEZE_BALL][Collider::Type::WALLPUSHR] = STOP;
	matrix[Collider::Type::FREEZE_BALL][Collider::Type::WALLPUSHL] = STOP;
	matrix[Collider::Type::FREEZE_BALL][Collider::Type::GODMODE] = NOTHING;

}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

update_status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->Intersects(c2->rect))
			{
				if (matrix[c1->type][c2->type] == DIE && c1->listener)
					c1->listener->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] == DIE && c2->listener)
					c2->listener->OnCollision(c2, c1);

				if (matrix[c1->type][c2->type] == STOP && c1->listener)
					c1->listener->StopMovement(c1, c2);

				if (matrix[c2->type][c1->type] == STOP && c2->listener)
					c2->listener->StopMovement(c2, c1);

				if (matrix[c1->type][c2->type] == STOP_Y && c1->listener)
					c1->listener->StopMovementY(c1, c2);

				if (matrix[c2->type][c1->type] == STOP_Y && c2->listener)
					c2->listener->StopMovementY(c2, c1);

				if (matrix[c1->type][c2->type] == FALL && c1->listener)
					c1->listener->Fall(c1, c2);

				if (matrix[c2->type][c1->type] == FALL && c2->listener)
					c2->listener->Fall(c2, c1);

				if(matrix[c1->type][c2->type] == FREEZE && c1->listener)
					c1->listener->Freeze(c1, c2);

				if (matrix[c2->type][c1->type] == FREEZE && c2->listener)
					c2->listener->Freeze(c2, c1);

				if (matrix[c1->type][c2->type] == PUSHR && c1->listener)
					c1->listener->PushR(c1, c2);

				if (matrix[c2->type][c1->type] == PUSHR && c2->listener)
					c2->listener->PushR(c2, c1);

				if (matrix[c1->type][c2->type] == PUSHL && c1->listener)
					c1->listener->PushL(c1, c2);

				if (matrix[c2->type][c1->type] == PUSHL && c2->listener)
					c2->listener->PushL(c2, c1);

				if (matrix[c1->type][c2->type] == PUSH && c1->listener)
					c1->listener->BallPush(c1, c2);

				if (matrix[c2->type][c1->type] == PUSH && c2->listener)
					c2->listener->BallPush(c2, c1);
			}

			//SOBRA 7: INTENTO DE QUE CAIGA EL JUGADOR SI NO EST� EN UNA PLATAFORMA

			/*else if (c2->Intersects(c1->rect) == false)
			{
			if ((c1->type == Collider::GROUND && c2->type == Collider::PLAYER))
				{
					if ((App->player->currentAnimation == &App->player->sideLeftAnim || App->player->currentAnimation == &App->player->sideRightAnim || App->player->currentAnimation == &App->player->r_idleAnim || App->player->currentAnimation == &App->player->l_idleAnim) && ((c2->rect.x >= (c1->rect.x + c1->rect.w)) || ((c2->rect.x + c2->rect.w) <= c1->rect.x)) && ((c2->rect.y + c2->rect.h) <= c1->rect.y) && (c2->rect.y > (c1->rect.y + 32)))
					{
						App->player->position.y += App->player->speed_y;
					}
				}
			}*/
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return update_status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case Collider::Type::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case Collider::Type::WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::GROUND: // purple
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		case Collider::Type::AIR: // black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		case Collider::Type::PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case Collider::Type::ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case Collider::Type::WALLPUSHL: //light blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 150, alpha);
			break;
		case Collider::Type::WALLPUSHR: //light blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 150, alpha);
			break;
		case Collider::Type::GODMODE: //light blue
			App->render->DrawQuad(colliders[i]->rect, 212, 172, 45, alpha);
			break;
		case Collider::Type::FREEZE_BALL: //light blue
			App->render->DrawQuad(colliders[i]->rect, 150, 172, 45, alpha);
			break;

		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}
