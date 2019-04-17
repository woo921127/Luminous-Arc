#pragma once
#include "gameNode.h"
#include "battleMap.h"
#include <list>
#include "Enemy.h"
struct EnemyMoving {

	POINT index;

	int zLevel;

	int f;
	int g;
	int h;

	bool isStart;
	bool isEnd;
	bool isblock;
	EnemyMoving* EnemyStar;
};


class EnemyAstar : public gameNode
{
private:

	battleMap* _battle;

	Enemy* _enemy;;

	vector<vector<Tile*>>  _isoMap;


	list<EnemyMoving*>					_OpenTile;
	list<EnemyMoving*>::iterator		_iOpenTile;

	list<EnemyMoving*>					_CloseTile;
	list<EnemyMoving*>::iterator		_iCloseTile;

	vector<POINT>						_LoadTile;
	vector<POINT>::iterator			_iLoadTile;


	vector<vector<EnemyMoving*>>	_EnemyAStar;

	int _currentX;
	int _currentY;

	RECT rc;

	bool _isStart;

	POINT _startIdx;

	//끝위치
	POINT _endIdx;

	//반환점
	POINT _giveIdx;

	//설정된 타일 최대갯수
	POINT* _tileNum;
	POINT p[4];
	//비교용 정수
	int _compareInt;

	//4방향검사
	bool _locCheck[4];

	//돌아온횟수
	int _endG;
	bool _isStopEndG;

	int playX;
	int playY;

	int left, top;

	int centerX, centerY;


public:
	EnemyAstar();
	~EnemyAstar();

	HRESULT init();
	void release();
	void update();
	void render(float cameraX, float cameraY);

	void drawRhombus(int left, int top, float cameraX, float cameraY);
	void setAstar();

	void setvvMap(vector<vector<Tile*>> vvMap) { _isoMap = vvMap; }
	void setTileNum(POINT* tileNum) { _tileNum = tileNum; }
	POINT getPlayerIdx() { return _endIdx; }
	void setPlayerIdx(POINT playerIdx) { _endIdx = playerIdx; }
	void setMonsterIdx(POINT monsterIdx) { _startIdx = monsterIdx; }



	void setEnemy(Enemy* alph) { _enemy = alph; }

	EnemyMoving* getaStarTile(int x, int y) { return _EnemyAStar[y][x]; }

	POINT* getTileNum() { return _tileNum; }


	vector<POINT>* getLoad() { return &_LoadTile; }
};

