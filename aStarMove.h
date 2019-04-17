#pragma once
#include "gameNode.h"
#include "battleMap.h"
#include <list>
#include "Alph.h"
#include "Lucia.h"


struct aStarMoving {

	POINT index;

	int zLevel;

	int f;
	int g;
	int h;

	bool isStart;
	bool isEnd;
	bool isblock;
	aStarMoving* aStar;
};

class aStarMove : public gameNode
{
private:


	battleMap* _battle;

	Alph* _alph;

	vector<vector<Tile*>>  _isoMap;



	list<aStarMoving*>					_OpenTile;
	list<aStarMoving*>::iterator		_iOpenTile;

	list<aStarMoving*>					_CloseTile;
	list<aStarMoving*>::iterator		_iCloseTile;

	vector<POINT>						_LoadTile;
	vector<POINT>::iterator			_iLoadTile;


	vector<vector<aStarMoving*>>	_vvAStar;


	//저장 인덱스

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
	aStarMove();
	~aStarMove();


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

	

	void setAlph(Alph* alph) { _alph = alph; }

	aStarMoving* getaStarTile(int x, int y) { return _vvAStar[y][x]; }

	POINT* getTileNum() { return _tileNum; }


	vector<POINT>* getLoad() { return &_LoadTile; }
};

