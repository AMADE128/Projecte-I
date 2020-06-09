#include "Module.h"

Module::Module(bool startEnabled) : isEnabled(startEnabled)
{

}

bool Module::Init()
{
	return true;
}

bool Module::Start()
{
	return true;
}

update_status Module::PreUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

update_status Module::Update()
{
	return update_status::UPDATE_CONTINUE;
}

update_status Module::PostUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

bool Module::CleanUp()
{
	return true;
}

void Module::OnCollision(Collider* c1, Collider* c2)
{

}

void Module::StopMovement(Collider* c1, Collider* c2){

}

void Module::StopMovementY(Collider* c1, Collider* c2) {

}

void Module::Fall(Collider* c1, Collider* c2) {

}

void Module::Freeze(Collider* c1, Collider* c2) {

}

void Module::PushR(Collider* c1, Collider* c2) {

}

void Module::PushL(Collider* c1, Collider* c2) {

}

void Module::Enable()
{
	if (!isEnabled)
	{
		isEnabled = true;
		Start();
	}
}

void Module::Disable()
{
	if (isEnabled)
	{
		isEnabled = false;
		CleanUp();
	}
}