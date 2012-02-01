#include "PhysicsSystem.h"
#include "ICollidable.h"
#include "Contact.h"

PhysicsSystem * PhysicsSystem::currentInstance;


PhysicsSystem::PhysicsSystem(void)
{
}

PhysicsSystem::~PhysicsSystem(void)
{
}



void PhysicsSystem::AddCollidable(ICollidable* obj)
{
	collidables.push_back(obj);
}

ICollidable* PhysicsSystem::CollideWith(Vec3 point)
{
	for (int i = 0; i < collidables.size(); ++i)
	{
		if (collidables[i]->PointIntersects(point))
			return collidables[i];
	}
	return 0;
}
