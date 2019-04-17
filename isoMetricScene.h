#pragma once
#include "gameNode.h"
#include "camera.h"
#include "MapNode.h"
#include "tileNode.h"
#include "Tile.h"
#pragma warning(disable:4996)
class isoMetricScene : public gameNode
{
public:
	enum TOOL_BAR
	{
		TOOL_CURSOR,					//커서
		TOOL_RECT_SELLECT,				//렉트로 선택 하기
		TOOL_AUTO_SELLECT,				//같은 타일만 선택
		TOOL_SPOID,						//타일 속성정보 가져오기
		TOOL_ERASER,					//지우개
		TOOL_PAINT,						//같은 타일은 모두 칠하기
		TOOL_HAND,						//손처럼 잡아서 움직이기
		TOOL_NONE,						//아무것도아님
		TOOL_COUNT = TOOL_NONE			//카운트 = NONE
	};
private:

	vector<vector<iSoTile*>>	_vvMap;//맵

	vector<vector<Tile*>>	_isoMap;//맵
	isoBox _isoBox;
	int _tileMap[TILE_COUNT_X][TILE_COUNT_Y];
	int tileXNum, tileYNum;
	int _corner;
	int left, top;
	char str[128];
	POINT p[4];
	int centerX, centerY;
	isoSetting _isoSetting[TrTileX * TrTileY];
	camera* _camera;
	POINTFLOAT view;
	RECT viewRc;
	CTRL Click;
	RECT rc;
	POINT ptmouse2;
	TOOL_BAR					_currentTool; //현재 선택된 툴
	unsigned int TILEX;
	unsigned int TILEY;
	int tilenum;
	int temp;
	int saveNumX;
	int saveNumY;

	char saveNum[100];
	//============================체크 포인트 관련 변수=============================
	vector<vector<bool>>		_check;
	POINT					_saveCamera;
	POINT					_savePoint;				//저장되어 있는 좌표
	bool						_isShift;				//쉬프트키 눌럿니
	bool						_isMultipleSelection;	//여러개 선택했니
	UINT						_saveCheckX;			//세이브체크포인트
	UINT						_saveCheckY;			//세이브체크포인트
	


	bool ClickMouse;

	UINT _index;
	float _count;

	image* _image;


	RECT saveload[2];


public:
	HRESULT init();
	void release();
	void update();
	void render();

	//타일맵 그려주는 함수
	void drawTileMap2();
	void drawVecTile();
	//마름모 그려주는 함수
	void drawRhombus(int left, int top);
	
	void rhombusIn();

	void setMap();
	
	void viewMove();

	void mapSize();


	void save();

	void load();


	void classSave();
	void classLoad();

	TERRAIN_ARRAY_NUM1 terrainSelect(int frameX, int frameY);

	OBJECT objSelect(int frameX, int frameY);

	bool tileIndexInCheck(int x, int y);


	void mapZtile();

	isoMetricScene();
	~isoMetricScene();
};

