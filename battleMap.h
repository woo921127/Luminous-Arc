#pragma once
#include "gameNode.h"
#include "isoMetricScene.h"

class Alph;
class Lucia;
class Enemy;
class battleMap : public gameNode
{
private:
	vector<vector<iSoTile*>>	_vvMap;//¸Ê

	vector<vector<Tile*>>	_isoMap;//¸Ê

	unsigned int TILEX;
	unsigned int TILEY;

	int left, top;
	int centerX, centerY;
	DWORD* _attribute;

	Alph* _alph;
	Lucia* _lucia;
	Enemy* _enemy;
	//playerManager* _player;

	RECT rc;

	image* _image;

	char saveNum[100];

	float CameraX;
	float CameraY;

public:
	battleMap();
	~battleMap();

	HRESULT init();
	void release();
	void update();
	void render(float cameraX, float cameraY);

	void load();
	void classLoad();
	void Ztile(float cameraX, float cameraY);

	void classZtile(float cameraX, float cameraY);

	TERRAIN_ARRAY_NUM1 terrainSelect(int frameX, int frameY);

	OBJECT objSelect(int frameX, int frameY);

	unsigned int getTileX() { return TILEX; }
	unsigned int getTileY() { return TILEY; }

	void setTileX(int x) { TILEX = x; }
	void setTileY(int y) { TILEY = y; }

	unsigned int getCenterX() { return centerX; }
	unsigned int getCenterY() { return centerY; }

	iSoTile* getTile(int x, int y) { return _vvMap[y][x]; }


	Tile* getclassTile(int x, int y) { return _isoMap[y][x]; }

	DWORD getAttr(int x, int y) { return _attribute[x + y * TILEX]; }

	void setAlphManagerAddressLink(Alph* play) { _alph = play; }
	void setLuciaManagerAddressLink(Lucia* play) { _lucia = play; }
	void setEnemyManagerAddressLink(Enemy* enemy) { _enemy = enemy; }
};

