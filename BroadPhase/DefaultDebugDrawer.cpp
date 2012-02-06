#include "DefaultDebugDrawer.h"
#include "AABB.h"
#include "RigidBody.h"
#include <svl\SVL.h>
#include <glut.h>
#include <svl\SVLgl.h>

DefaultDebugDrawer::DefaultDebugDrawer(void)
{
}


DefaultDebugDrawer::~DefaultDebugDrawer(void)
{
}

void DefaultDebugDrawer::DrawAABB(AABB& aabb, Vec4& colour)
{
	Vec3* points = aabb.GeneratePoints();
 	glColor(colour);

	glBegin(GL_LINE_STRIP);
	glVertex(points[0]);
	glVertex(points[1]);
	glVertex(points[2]);
	glVertex(points[3]);
	glVertex(points[0]);
	glVertex(points[4]);
	glVertex(points[5]);
	glVertex(points[6]);
	glVertex(points[7]);
	glVertex(points[4]);
	glEnd();

	glBegin(GL_LINES);
	glVertex(points[1]);
	glVertex(points[5]);
	glVertex(points[2]);
	glVertex(points[6]);
	glVertex(points[3]);
	glVertex(points[7]);
	glEnd();

	free(points);
}

void DefaultDebugDrawer::DrawRigidBodyMotion(RigidBody& body)
{
	glColor3f(1, 0, 0);
	Vec3 vel = body.GetVelocity() * 60.0; //approx how far it travels in one sec	
	glBegin(GL_LINES);
	glVertex(body.GetPosition() - vel);
	glVertex(body.GetPosition());
	glEnd();
}

