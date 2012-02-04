#include "PhysicsSystem.h"
#include "ICollidable.h"
#include "Contact.h"
#include "RigidBody.h"
#include "IDebugDrawer.h"

PhysicsSystem * PhysicsSystem::currentInstance;


PhysicsSystem::PhysicsSystem(void) : debugDrawer(0)
{
}

PhysicsSystem::~PhysicsSystem(void)
{
}

void PhysicsSystem::DrawDebug()
{
	if (!debugDrawer)
		return;
	for (int i = 0; i < rigidBodies.size(); ++i)
	{
		debugDrawer->DrawAABB(rigidBodies[i]->GetAABB(), rigidBodies[i]->GetDebugColour());
	}
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

void PhysicsSystem::Integrate(float timeStep)
{
	float timeSquared = timeStep * timeStep;
	for (int i = 0; i < rigidBodies.size(); ++i)
	{
		rigidBodies[i]->SetPosition(2 * rigidBodies[i]->GetPosition() - rigidBodies[i]->GetLastPosition() + rigidBodies[i]->GetAcceleration() * timeSquared);
		rigidBodies[i]->SetOrientation(qMultiply(rigidBodies[i]->GetOrientation(), rigidBodies[i]->GetAngularVelocity()));
		rigidBodies[i]->CalculateTransform();
		rigidBodies[i]->CalculateBB();
	}	
}

void PhysicsSystem::AddRigidBody(RigidBody* bodyToAdd)
{
	rigidBodies.push_back(bodyToAdd);
	broadPhase.bodies.push_back(bodyToAdd);
}

void PhysicsSystem::SetDebugDrawer(IDebugDrawer* debugDrawer)
{
	this->debugDrawer = debugDrawer;
}

