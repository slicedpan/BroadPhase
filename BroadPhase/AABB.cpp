#include "AABB.h"


AABB::AABB(void)
{
}


AABB::~AABB(void)
{
}

AABB AABB::Transform(Mat4& transform)
{
	Vec3 transformedPoint[8];
	Vec3* originalPoints = GeneratePoints();
	Vec3 newMax(FLT_MIN, FLT_MIN, FLT_MIN);
	Vec3 newMin(FLT_MAX, FLT_MAX, FLT_MAX);
	for (int i = 0; i < 8; ++i)
	{
		transformedPoint[i] = proj(Vec4(originalPoints[i], 1) * transform);
		for (int j = 0; j < 3; ++j)
		{
			if (transformedPoint[i][j] > newMax[j])
				newMax[j] = transformedPoint[i][j];
			else if (transformedPoint[i][j] < newMin[j])
				newMin[j] = transformedPoint[i][j];
		}
	}
	free(originalPoints);
	return AABB(newMin, newMax);
}

Vec3* AABB::GeneratePoints()
{
	Vec3* pV = (Vec3*)malloc(sizeof(Vec3) * 8);
	Vec3 offset = (max - min) / 2.0;
	
	pV[0] = centre + offset;
	pV[1] = centre + Vec3(offset[0], offset[1], -offset[2]);
	pV[2] = centre + Vec3(-offset[0], offset[1], -offset[2]);
	pV[3] = centre + Vec3(-offset[0], offset[1], offset[2]);
	pV[4] = centre + Vec3(offset[0], -offset[1], offset[2]);
	pV[5] = centre + Vec3(offset[0], -offset[1], -offset[2]);
	pV[6] = centre + Vec3(-offset[0], -offset[1], -offset[2]);
	pV[7] = centre + Vec3(-offset[0], -offset[1], offset[2]);

	return pV;
}
