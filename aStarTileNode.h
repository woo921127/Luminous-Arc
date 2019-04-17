#pragma once
#include "stdafx.h"
#include <vector>


typedef struct astarTile
{
public:
	enum ASTAR_NODE_TYPE
	{
		EMPTY = 0,
		BLOCK,
		START,
		DEST
	};

	POINT idx;
	POINT parentIndex = { -1,-1 };
	int zLevel = 0;

	float f = 0.0f;
	float g = 0.0f;
	float h = 0.0f;

	ASTAR_NODE_TYPE nodeType = EMPTY;

	void setAstarTile(POINT idx, int zLvl, ASTAR_NODE_TYPE type) {
		this->idx = idx;
		this->zLevel = zLvl;
		this->nodeType = type;

	}
	void setAstarTile(int idxX, int idxY, int parentX, int parentY,
		int zlvl, float f, float g, float h) {

	}

}ASTARTILE;

typedef vector<ASTARTILE*> vLineAstar;
typedef vector<vLineAstar> vvMapAstar;

