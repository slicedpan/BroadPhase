#pragma once

class AABB;
class Vec4;

class IDebugDrawer
{
public:
	virtual void DrawAABB(AABB& aabb, Vec4& colour) = 0;
};


