#include "BroadPhase.h"
#include "RigidBody.h"
#include "AABB.h"
#include <algorithm>

bool EntrySortFunc(BroadPhaseEntry& entry1, BroadPhaseEntry& entry2)
{
	return entry1.value < entry2.value;
}

BroadPhase::BroadPhase(void) : needsResync(false)
{
	first = 0;
	second = 1;
	third = 2;
	overlapMask = (bool*)malloc(sizeof(bool) * 2500);
	maxPairs = 2500;
}


BroadPhase::~BroadPhase(void)
{
}

void BroadPhase::ReallocateMask()
{
	//realloc overlapMask
}

void BroadPhase::GenerateCollisions()
{	
	memset(overlapMask, 0, sizeof(bool) * bodies.size() * bodies.size());
	pairs.clear();
	if (bodies.size() * bodies.size() > maxPairs)
		ReallocateMask();

	if (bodies.size() != entries[0].size() || bodies.size() != entries[1].size() || bodies.size() != entries[2].size())
		GenerateEntries();
	else
		UpdateEntries();
	SortEntries();
	
	for (int i = 0; i < entries[first].size(); ++i)
	{
		if (entries[first][i].start)
		{
			indexActive.push_back(entries[first][i].index);
			for (int j = 0; j < indexActive.size() - 1; ++j)
			{
				SetMask(entries[first][i].index, indexActive[j], true);								
			}
		}
		else
		{
			for (int j = 0; j < indexActive.size(); ++j)
			{
				if (indexActive[j] == entries[first][i].index)
					indexActive.erase(indexActive.begin() + j);
			}
		}
	}

	indexActive.clear();

	for (int i = 0; i < entries[second].size(); ++i)
	{
		if (entries[second][i].start)
		{
			indexActive.push_back(entries[second][i].index);
			for (int j = 0; j < indexActive.size() - 1; ++j)
			{
				if (!CheckMask(entries[second][i].index, indexActive[j]))
				{
					continue;
				}
			}
		}
		else
		{
			for (int j = 0; j < indexActive.size(); ++j)
			{
				if (indexActive[j] == entries[first][i].index)
					indexActive.erase(indexActive.begin() + j);
			}
		}
	}

	for (int i = 0; i < entries[third].size(); ++i)
	{
		if (entries[third][i].start)
		{
			indexActive.push_back(entries[third][i].index);
			for (int j = 0; j < indexActive.size() - 1; ++j)
			{
				if (CheckMask(entries[third][i].index, indexActive[j]))
				{
					BroadPhasePair pair;
					pair.p1 = bodies[entries[third][i].index];
					pair.p2 = bodies[indexActive[j]];
					pair.p1->SetDebugColour(Vec4(1, 0, 0, 1));
					pair.p2->SetDebugColour(Vec4(1, 0, 0, 1));
					pairs.push_back(pair);
				}
			}
		}
		else
		{
			for (int j = 0; j < indexActive.size(); ++j)
			{
				if (indexActive[j] == entries[first][i].index)
					indexActive.erase(indexActive.begin() + j);
			}
		}
	}
}

void BroadPhase::AddBody(RigidBody* body)
{
	bodies.push_back(body);
}

void BroadPhase::GenerateEntries()
{
	for (int i = 0; i < 3; ++i)
	{
		entries[i].clear();		
	}
	for (int i = 0; i < bodies.size(); ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			BroadPhaseEntry startEntry, endEntry;
			startEntry.index = i;
			endEntry.index = i;
			startEntry.start = true;
			endEntry.start = false;
			startEntry.value = bodies[i]->GetAABB().GetMin()[j];
			endEntry.value = bodies[i]->GetAABB().GetMax()[j];
			startEntry.body = bodies[i];
			endEntry.body = bodies[i];
			entries[j].push_back(startEntry);
			entries[j].push_back(endEntry);
		}
	}	
}

void BroadPhase::SortEntries()
{
	for (int j = 0; j < 3; ++j)
	{
		std::sort(entries[j].begin(), entries[j].end(), EntrySortFunc);
	}
}

void BroadPhase::UpdateEntries()
{
	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < entries[j].size(); ++i)
		{
			if (entries[j][i].start)
				entries[j][i].value = entries[j][i].body->GetAABB().GetMax()[j];
			else
				entries[j][i].value = entries[j][i].body->GetAABB().GetMin()[j];
		}
	}
}
