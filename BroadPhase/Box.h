#pragma once
#include "icollidable.h"
#include <glut.h>
#include <svl\SVLgl.h>

class Box : public ICollidable
{
public:
	Box(Vec3 centre, Vec3 extents);
	~Box(void);
	bool PointIntersects(Vec3& point);
	bool PointWithinDistance(Vec3& point, float dist);
	Contact* GetContact(Vec3& point);
	void Draw();
	Vec3 Colour;
	Vec3 GetPoint(int index);
	Vec3 GetTransformedPoint(int index);
	void ApplyAngularMomentum(Vec3 axis, float amount);
	void Update(float msSinceLast);
private:
	inline void DrawQuad(int i0, int i1, int i2, int i3)
	{
		glBegin(GL_QUADS);
		glVertex(points[i0]);
		glNormal(points[i0]);
		glVertex(points[i1]);
		glNormal(points[i1]);
		glVertex(points[i2]);
		glNormal(points[i2]);
		glVertex(points[i3]);
		glNormal(points[i3]);
		glEnd();
	}
	Vec3 centre;
	Vec3 extents;
	Vec3 max;
	Vec3 min;
	Vec3 points[8];
	Mat4 transform;
	Vec4 angularMomentum;
	Vec4 orientation;
	Vec3 velocity;
};



