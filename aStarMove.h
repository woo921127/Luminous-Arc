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


	//���� �ε���

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

