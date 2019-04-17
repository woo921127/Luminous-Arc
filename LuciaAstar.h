#pragma once
#include "gameNode.h"
#include "battleMap.h"
#include <list>
#include "Lucia.h"


struct LuciaMoving {

	POINT index;

	int zLevel;

	int f;
	int g;
	int h;

	bool isStart;
	bool isEnd;
	bool isblock;
	LuciaMoving* LuciaStar;
};

class LuciaAstar : public gameNode
{
private:


	battleMap* _battle;

	Lucia* _lucia;

	vector<vector<Tile*>>  _isoMap;


	list<LuciaMoving*>					_OpenTile;
	list<LuciaMoving*>::iterator		_iOpenTile;

	list<LuciaMoving*>					_CloseTile;
	list<LuciaMoving*>::iterator		_iCloseTile;

	vector<POINT>						_LoadTile;
	vector<POINT>::iterator			_iLoadTile;


	vector<vector<LuciaMoving*>>	_LuciaAStar;

	int _currentX;
	int _currentY;

	RECT rc;

	bool _isStart;

	POINT _startIdx;

	//����ġ
	POINT _endIdx;

	//��ȯ��
	POINT _giveIdx;

	//������ Ÿ�� �ִ밹��
	POINT* _tileNum;
	POINT p[4];
	//�񱳿� ����
	int _compareInt;

	//4����˻�
	bool _locCheck[4];

	//���ƿ�Ƚ��
	int _endG;
	bool _isStopEndG;

	int playX;
	int playY;

	int left, top;

	int centerX, centerY;



public:
	LuciaAstar();
	~LuciaAstar();


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



	void setlucia(Lucia* alph) { _lucia = alph; }

	LuciaMoving* getaStarTile(int x, int y) { return _LuciaAStar[y][x]; }

	POINT* getTileNum() { return _tileNum; }


	vector<POINT>* getLoad() { return &_LoadTile; }
};

