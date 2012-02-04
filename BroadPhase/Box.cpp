#include "Box.h"
#include "Contact.h"
#include "Quaternion.h"

Box::Box(Vec3 centre, Vec3 extents)
{
	SetPosition(centre);
	this->extents = extents;
	this->max = centre + (extents / 2.0f);
	this->min = centre - (extents / 2.0f);
	this->Colour = Vec3(0.9, 0.1, 0.0);
	ApplyAngularImpulse(Vec4(0.99995f, 0.0f, 0.01f, 0.0f));
	SetOrientation(Vec4(1.0f, 0.0f, 0.0f, 0.0f));
	ApplyImpulse(Vec3(0.03f, 0.0f, 0.0f));
	points[0] = extents / 2.0f;
	points[1] = Vec3(-extents[0] / 2.0f, extents[1] / 2.0f, extents[2] / 2.0f);
	points[2] = Vec3(-extents[0] / 2.0f, -extents[1] / 2.0f, extents[2] / 2.0f);
	points[3] = Vec3(extents[0] / 2.0f, -extents[1] / 2.0f, extents[2] / 2.0f);
	points[4] = Vec3(extents[0] / 2.0f, extents[1] / 2.0f, -extents[2] / 2.0f);
	points[5] = Vec3(-extents[0] / 2.0f, extents[1] / 2.0f, -extents[2] / 2.0f);
	points[6] = - points[0];
	points[7] = Vec3(extents[0] / 2.0f, -extents[1] / 2.0f, -extents[2] / 2.0f);
	baseBB.SetMax(max);
	baseBB.SetMin(min);

}

Box::~Box(void)
{
}

bool Box::PointIntersects(Vec3& point)
{
	if (point[0] > min[0] && point[0] < max[0])
	{
		if (point[1] > min[1] && point[1] < max[1])
		{
			if (point[2] > min[2] && point[2] < max[2])
			{
				return true;
			}
		}
	}
	return false;
}

bool Box::PointWithinDistance(Vec3& point, float dist)
{
	return true; //fix maybe
}

/*

void Box::Draw()
{
	glPushMatrix();		
	glMultMatrixf(transform.Ref());	
	glScalef(extents[0], extents[1], extents[2]);
	glColor(Colour);
	glutSolidCube(1.0);
	glPopMatrix();
}

*/



void Box::Draw()
{
	glPushMatrix();
	glMultMatrixf(GetTransform().Ref());
	glColor(Colour);
	DrawQuad(0, 1, 2, 3);
	DrawQuad(4, 5, 6, 7);
	DrawQuad(0, 1, 5, 4);
	DrawQuad(1, 2, 6, 5);
	DrawQuad(2, 3, 7, 6);
	DrawQuad(3, 0, 4, 7);
	glPopMatrix();
}



void Box::ApplyAngularMomentum(Vec3 axis, float amount)
{
	float s = sin(amount);
	axis.Normalise();
	Vec4 quat = Vec4(cos(amount), s * axis[0], s * axis[1], s * axis[2]);
	ApplyAngularImpulse(quat);
}

Vec3 Box::GetPoint(int index)
{
	return points[index];
}

Vec3 Box::GetTransformedPoint(int index)
{
	return proj(Vec4(points[index], 1.0f) * GetTransform());
}

void Box::Update(float msSinceLast)
{

}



