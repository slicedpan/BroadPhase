#pragma once

class AABB;
class Vec4;
class RigidBody;

class IDebugDrawer
{
public:
	virtual void DrawAABB(AABB& aabb, Vec4& colour) = 0;
	virtual void DrawRigidBodyMotion(RigidBody& body) = 0;
};


