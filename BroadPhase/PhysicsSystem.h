#pragma once

class ICollidable;
struct Contact;

#include <vector>
#include <svl\SVL.h>

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
	ICollidable* CollideWith(Vec3 point);
private:
	static PhysicsSystem * currentInstance;
	std::vector<ICollidable*> collidables;
	PhysicsSystem(void);
};

