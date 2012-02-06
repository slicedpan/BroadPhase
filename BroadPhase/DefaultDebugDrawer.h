#pragma once

#include "IDebugDrawer.h"

class DefaultDebugDrawer : public IDebugDrawer
{
public:
	DefaultDebugDrawer(void);
	~DefaultDebugDrawer(void);
	void DrawAABB(AABB& aabb, Vec4& colour);
	void DrawRigidBodyMotion(RigidBody& body);
};

