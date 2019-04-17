#pragma once
#include "gameNode.h"


struct EnemyState
{
	image* image;
	string name;
	animation* ani;
	POINT Pos;
	int zLevel;
	int x, y;
	int viewX, viewY;
	int AttackDemage;
	int AttackDefence;
	float Speed;
	int Accuracy;
	int MagicDemage;
	int MagicDefence;
	int Move;
	int jump;
	int currentHP, MaxHp;
	int currentMp, MaxMp;
	int FlashPoint;
	int Exp;
	bool isSkill;
	bool isSynergySkill;
	bool isAttack;
	bool isHit;
	bool isDead;
	int alphaValue;
	int direction;
	int state;
	int Level;
};

class EnemyManager : public gameNode
{
protected:


	EnemyState  _enemy;

public:
	EnemyManager();
	~EnemyManager();

	virtual HRESULT init(string PlayerName, const char* imageName, int x, int y);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);

	void initState(int hp, int mp, int AtkDemage, int AtkDefence, int MgDemage, int MgDefence, int move, int jump, int speed, int Accuracy, int level, int exp);


	EnemyState getEnemy() { return _enemy; }
	image* getimage() { return _enemy.image; }
	//==================Z레벨====================//
	int getZlevel() { return _enemy.zLevel; }
	void setZlevel(int Z) { _enemy.zLevel = Z; }
	//==========================================//


	//============플레이어좌표===============//
	float getX() { return _enemy.x; }
	float getY() { return _enemy.y; }
	float getViewX() { return _enemy.viewX; }
	float getViewY() { return _enemy.viewY; }

	void setX(float X) { _enemy.x = X; }
	void setY(float Y) { _enemy.y = Y; }
	void setviewX(float X) { _enemy.viewX = X; }
	void setviewY(float Y) { _enemy.viewY = Y; }
	//=========================================//


	//===========플레이어 스텟=================//
	float getSpeed() { return _enemy.Speed; }
	void setSpeed(float S) { _enemy.Speed = S; }


	int getCurrentHp() { return _enemy.currentHP; }
	void setCurrentHp(int a) { _enemy.currentHP = a; }


	int getMaxHp() { return _enemy.MaxHp; }
	void setMaxHp(int a) { _enemy.MaxHp = a; }

	int getAtkDmg() { return _enemy.AttackDemage; }
	void setAtkDmg(int a) { _enemy.AttackDemage = a; }

	int getAtkDef() { return _enemy.AttackDefence; }
	void setAtkDef(int a) { _enemy.AttackDefence = a; }

	int getMgcDmg() { return _enemy.MagicDemage; }
	void setMgcDmg(int a) { _enemy.MagicDemage = a; }

	int getMgcDef() { return _enemy.MagicDefence; }
	void setMgcDef(int a) { _enemy.MagicDefence = a; }


	int getmoveSpeed() { return _enemy.jump; }
	void setmoveSpeed(int a) { _enemy.jump = a; }

	int getAccuracy() { return _enemy.Accuracy; }
	void setAccuracy(int a) { _enemy.Accuracy = a; }

	int getMove() { return _enemy.Move; }
	void setMove(int a) { _enemy.Move = a; }

	int getLevel() { return _enemy.Level; }
	void setLevel(int a) { _enemy.Level = a; }

	int getExp() { return _enemy.Exp; }
	void setExp(int a) { _enemy.Exp = a; }

	int getCurrentMp() { return _enemy.currentMp; }
	void setCurrentMp(int a) { _enemy.currentMp; }

	int getMaxMp() { return _enemy.MaxMp; }
	void setMaxMp(int a) { _enemy.MaxMp = a; }
};

