#pragma once
#include "gameNode.h"
#include "camera.h"
#include "battleMap.h"
#include "Alph.h"
#include "Lucia.h"
#include "aStarMove.h"
#include "LuciaAstar.h"
#include "TitleScene.h"
#include "Enemy.h"
#include "EnemyAstar.h"

class battleScene : public gameNode
{
private:
	battleMap* _battle;
	camera* _camera;

	Alph* _alph;
	Lucia* _lucia;
	Enemy* _enemy;
	aStarMove* _astar;
	LuciaAstar* _luciaAstar;
	EnemyAstar* _enemyAstar;
	TitleScene* _title;
	POINTFLOAT view;

	int alphX, alphY;
	int luciaX, luciaY;
	int enemyX, enemyY;
	int Zlevel = 0;

	int aZ;
	int lZ;

	int x;

	int alPhZ;
	int luciaZ;
	int enemyZ;

	bool Camerachange;
	bool Enemychange;
	bool alphCamera;
	bool luciaCamera;
	bool enemyCamera;
	bool StartCamera;

	bool SyAtk;
	bool SyAtk2;
	bool SyAtk3;
	bool SyAtk4;
	bool SyAtk5;
	int checkNum;
	bool luciaChange;
	//마름모//
	POINT p[4];
	int centerX;
	int centerY;
	int left, top;
	char str[128];


	//체력바//

	RECT alphHp;
	RECT alphMp;
	RECT alphFp;

	RECT luciaHp;
	RECT luciaMp;
	RECT luciaFp;


	RECT EnemyHp;
	RECT EnemyMp;
	RECT EnemyFp;

	int _alphHp;
	int _alphMp;
	int _alphFp;

	int _luciaHp;
	int _luciaMp;
	int _luciaFp;


	int _enemyHp;
	int _enemyMp;
	int _enemyFp;

	int Hitcount;
	int luciaHitCount;
	int enemyHitCount;
	int enemyHitCount2;
	//=======//
	
	bool tt;
	
	POINT _currentIdx;
	POINT _tileNum;
	POINT _luciaTileNum;
	POINT _enemyTileNum;

	POINT NumTile;
	POINT LuciNumTile;
	POINT EnemyNumtile;
	POINTFLOAT save;
	
	//a스타//
	POINT alphStay;
	POINT MoveStay;
	POINTFLOAT StaySave;


	POINT luciaStay;
	POINT MoveLucia;


	POINT MoveEnemy;
	POINT EnemyStay;

	int saveX, saveY;
	int MoveSaveX, MoveSaveY;

	
	int MovePointX, MovePointY;
	int alphAtkPointX, alphAtkPointY;
	int alphMgcPointX, alphMgcPointY;
	int alphSyPointX, alphSyPointY;

	int LuciaPointX, LuciaPointY;
	int luciaAtkPointX, luciaAtkPointY;
	int luciaMgcPointX, luciaMgcPointY;
	int luciaSyPointX, luciaSyPointY;


	int EnemyPointX, EnemyPointY;
	int EnemyAtkPointX, EnemyAtkPointY;
	int EnemyMgcPointX, EnemyMgcPointY;
	int EnemySyPointX, EnemySyPointY;

	vector<POINT>* _vvStar;
	vector<POINT>* _vvluciStar;
	vector<POINT>* _vvEnemyStar;

	int alphAtkDmg;
	int alphMgcDmg;

	int luciaAtkDmg;
	int luciaMgcDmg;

	int SynergeDmg;


	int EnemyAlphAtkDmg;
	int EnemyAlphMgcDmg;

	int EnemyLuciaAtkDmg;
	int EnemyLuciaMgcDmg;

	vector<POINT> _vAStar;
	vector<POINT> _luciaStar;
	vector<POINT> _EnemyStar;

	int q;

	int sampleNumber;

	int SynergeCount;

	float angle;
	float distance;


	float Luangle;
	float Ludistance;

	float Enemyangle;
	float EnemyDistance;


	bool alphmoving;
	bool luciamoving;
	bool enemymoving;
	bool Range;

	POINTFLOAT safetySave;

	int e;

	bool StarRender;


	image* fire;
	image* bomb;
	image* puple;

	int imageCount;
	int imageIndex;
	
	int bombCount;
	int bombIndex;


	int pupleCount;
	int pupleIndex;

	int pupleCount2;
	int pupleIndex2;

	int SyCount;
	int SyIndex;
	
	int SyCount2;
	int SyIndex2;

	int SyCount3;
	int SyIndex3;

	int SyCount4;
	int SyIndex4;

	int SyCount5;
	int SyIndex5;
public:
	battleScene();
	~battleScene();


	HRESULT init();
	void release();
	void update();
	void render();

	void drawRhombus(int left, int top);

	void astarMove();

	void alphMove();
	void luciaMove();
	void EnemyMove();
	void drawTile();
	void LuciadrawTile();
	void EnemydrawTile();
	void alphTileMove();
	void luciaTileMove();
	void EnemyTileMove();
	void zMove();
	void cameraMove();


	void PlayerDead();
	void HitDemege();



	void alphState();
	void luciaState();
	void enemyState();
	void alphView();
	void luciaView();
	void enemyView();
	void SynergeSkill();

	void PlayerCollision();


	int getLuciaPointX() { return LuciaPointX; }
	void setLuciaPointX(int a) { luciaAtkPointX = a; }

	int getLuciaPointY() { return luciaAtkPointY; }
	void setLuciaPointY(int a) { luciaAtkPointY = a; }


	void setVolume(TitleScene* volume) { _title = volume; };

};

