#pragma once

#include <vector>
#define FIRSTOVERLAP 1
#define SECONDOVERLAP 2
#define THIRDOVERLAP 4

class RigidBody;

struct BroadPhaseEntry
{
	int index;
	bool start;
	float value;
	RigidBody* body;
};

struct BroadPhasePair
{
	RigidBody* p1;
	RigidBody* p2;
};

class BroadPhase
{
public:
	BroadPhase(void);
	~BroadPhase(void);
	std::vector<RigidBody*> bodies;	
	void GenerateCollisions();
	void AddBody(RigidBody* body);
private:
	std::vector<BroadPhaseEntry> entries[3];
	std::vector<BroadPhasePair> pairs;	
	void GenerateEntries();
	void SortEntries();
	void UpdateEntries();
	bool needsResync;
	int first;
	int second;
	int third;
	std::vector<bool> colliding;
	std::vector<int> indexActive;
	bool* overlapMask;
	void ReallocateMask();
	int maxPairs;
	inline void SetMask(int index1, int index2, bool value)
	{		
		if (index1 > index2)
		{
			int i;
			i = index2;
			index2 = index1;
			index1 = i;
		}
		*(overlapMask + index1 + (index2 * bodies.size())) = value;
	}
	inline bool CheckMask(int index1, int index2)
	{
		if (index1 > index2)
		{
			int i;
			i = index2;
			index2 = index1;
			index1 = i;
		}
		return *(overlapMask + index1 + (index2 * bodies.size()));
	}

};



