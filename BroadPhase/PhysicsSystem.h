#pragma once

class ICollidable;
class RigidBody;
struct Contact;
class IDebugDrawer;

#include <vector>
#include <svl\SVL.h>
#include "BroadPhase.h"

class PhysicsSystem
{
public:
	~PhysicsSystem(void);
	inline static PhysicsSystem* GetCurrentInstance()
	{
		if (currentInstance == 0)
			currentInstance = new PhysicsSystem();
		return currentInstance;
	}
	void AddCollidable(ICollidable* obj);
	void AddRigidBody(RigidBody* bodyToAdd);
	void Integrate(float timeStep);
	ICollidable* CollideWith(Vec3 point);
	void DrawDebug();
	void SetDebugDrawer(IDebugDrawer* debugDrawer);
private:
	static PhysicsSystem * currentInstance;
	IDebugDrawer*  debugDrawer;
	std::vector<ICollidable*> collidables;
	std::vector<RigidBody*> rigidBodies;
	PhysicsSystem(void);
	BroadPhase broadPhase;
};

