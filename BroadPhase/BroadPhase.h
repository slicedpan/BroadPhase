#pragma once

#include <vector>

class RigidBody;

class BroadPhase
{
public:
	BroadPhase(void);
	~BroadPhase(void);
	std::vector<RigidBody*> bodies;
	
};

