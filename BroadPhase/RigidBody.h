#pragma once

#include <svl\SVL.h>
#include "AABB.h"

class RigidBody
{
public:
	RigidBody(void);
	~RigidBody(void);
	void ApplyImpulse(Vec3 impulse);
	void ApplyForce(Vec3 force);
	void SetMass(float mass);
	void SetPosition(Vec3 position);
	Vec3& GetVelocity();
	Vec3& GetPosition();
	Vec3& GetAcceleration();
	Vec3& GetLastPosition();
	Vec4& GetAngularVelocity();
	Vec4& GetOrientation();
	void SetOrientation(Vec4& orientation);
	void ApplyAngularImpulse(Vec4& angularVelocity);
	void ClearAcceleration();
	void CalculateTransform();
	void CalculateBB();
	Vec4& GetDebugColour();
	void SetDebugColour(Vec4& colour);
	Mat4& GetTransform();
	AABB& GetAABB();
protected:
	AABB baseBB;
private:
	Vec3 position;
	Vec3 lastPosition;
	Vec3 acceleration;
	Vec3 velocity;
	Vec4 orientation;
	Vec4 angularVelocity;
	Mat4 transform;	
	AABB currentBB;
	float mass;
	Vec4 debugColour;
};

inline void RigidBody::SetPosition(Vec3 position)
{	
	Vec3 vel = GetVelocity();
	this->position = position;
	lastPosition = this->position - vel;
}

inline void RigidBody::ClearAcceleration()
{
	acceleration.MakeZero();
}

inline Vec3& RigidBody::GetVelocity() 
{
	velocity = position - lastPosition;
	return velocity;
}

inline Vec3& RigidBody::GetPosition() {return position;}
inline Vec3& RigidBody::GetAcceleration() {return acceleration;}
inline Vec3& RigidBody::GetLastPosition() {return lastPosition;}
inline void RigidBody::SetMass(float mass) {this->mass = mass;}

inline Vec4& RigidBody::GetOrientation() {return orientation;}
inline Vec4& RigidBody::GetAngularVelocity() {return angularVelocity;}

inline void RigidBody::SetDebugColour(Vec4& colour) {debugColour = colour;}
inline Vec4& RigidBody::GetDebugColour() {return debugColour;}

inline void RigidBody::ApplyForce(Vec3 force)
{
	acceleration += force / mass;
}

inline void RigidBody::ApplyImpulse(Vec3 impulse)
{
	lastPosition -= impulse;
}

inline void RigidBody::ApplyAngularImpulse(Vec4& angularImpulse)
{
	angularVelocity = qMultiply(angularVelocity, angularImpulse);
}

inline void RigidBody::SetOrientation(Vec4& orientation)
{
	this->orientation = orientation;
}


