#pragma once
#include "singletonBase.h"
#include <vector>

struct aStarTile
{
	int F;
	int G;
	int H;

	POINT idx;

	bool isWall;

	aStarTile* mom;
};
class aStar : public singletonBase<aStar>
{
private:
	vector<vector<aStarTile*>> _vvMap;

	vector<aStarTile*>	_OpenTile;
	vector<aStarTile*>	_CloseTile;

	POINT loadIdx;

	vector<POINT>	_isWall;
	vector<POINT>	_load;

	float volume;

	float effectVolume;

public:
	aStar();
	~aStar();

	HRESULT init();
	void release();
	void update();
	void render();

	void closeTile(POINT idx);
	void openTile(POINT idx);
	vector<POINT> getLoad(POINT start, POINT end, POINT tileNum);

	aStarTile* getstyle(int y, int x) { return _vvMap[y][x]; }


	float getVolume() { return volume; }
	void setVolume(float v) { volume = v; }


	float getEftVolume() { return effectVolume; }
	void setEftVolume(float v) { effectVolume = v; }

};

