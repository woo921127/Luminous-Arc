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
		TOOL_CURSOR,					//Ŀ��
		TOOL_RECT_SELLECT,				//��Ʈ�� ���� �ϱ�
		TOOL_AUTO_SELLECT,				//���� Ÿ�ϸ� ����
		TOOL_SPOID,						//Ÿ�� �Ӽ����� ��������
		TOOL_ERASER,					//���찳
		TOOL_PAINT,						//���� Ÿ���� ��� ĥ�ϱ�
		TOOL_HAND,						//��ó�� ��Ƽ� �����̱�
		TOOL_NONE,						//�ƹ��͵��ƴ�
		TOOL_COUNT = TOOL_NONE			//ī��Ʈ = NONE
	};
private:

	vector<vector<iSoTile*>>	_vvMap;//��

	vector<vector<Tile*>>	_isoMap;//��
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
	TOOL_BAR					_currentTool; //���� ���õ� ��
	unsigned int TILEX;
	unsigned int TILEY;
	int tilenum;
	int temp;
	int saveNumX;
	int saveNumY;

	char saveNum[100];
	//============================üũ ����Ʈ ���� ����=============================
	vector<vector<bool>>		_check;
	POINT					_saveCamera;
	POINT					_savePoint;				//����Ǿ� �ִ� ��ǥ
	bool						_isShift;				//����ƮŰ ������
	bool						_isMultipleSelection;	//������ �����ߴ�
	UINT						_saveCheckX;			//���̺�üũ����Ʈ
	UINT						_saveCheckY;			//���̺�üũ����Ʈ
	


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

	//Ÿ�ϸ� �׷��ִ� �Լ�
	void drawTileMap2();
	void drawVecTile();
	//������ �׷��ִ� �Լ�
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

