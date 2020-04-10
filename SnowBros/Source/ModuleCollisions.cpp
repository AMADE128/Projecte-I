#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = NOTHING;
	matrix[Collider::Type::WALL][Collider::Type::GROUND] = NOTHING;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = NOTHING;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = NOTHING;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = NOTHING;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = NOTHING;

	matrix[Collider::Type::GROUND][Collider::Type::WALL] = NOTHING;
	matrix[Collider::Type::GROUND][Collider::Type::GROUND] = NOTHING;
	matrix[Collider::Type::GROUND][Collider::Type::PLAYER] = NOTHING;
	matrix[Collider::Type::GROUND][Collider::Type::ENEMY] = NOTHING;
	matrix[Collider::Type::GROUND][Collider::Type::PLAYER_SHOT] = NOTHING;
	matrix[Collider::Type::GROUND][Collider::Type::ENEMY_SHOT] = NOTHING;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = STOP;
	matrix[Collider::Type::PLAYER][Collider::Type::GROUND] = STOP_Y;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = NOTHING;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = DIE;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = NOTHING;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = DIE;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = STOP;
	matrix[Collider::Type::ENEMY][Collider::Type::GROUND] = STOP_Y;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = NOTHING;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = NOTHING;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = DIE;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = NOTHING;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = DIE;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::GROUND] = DIE;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = NOTHING;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = NOTHING;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = NOTHING;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = NOTHING;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = DIE;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::GROUND] = DIE;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = NOTHING;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = NOTHING;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = NOTHING;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = NOTHING;
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


			}
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