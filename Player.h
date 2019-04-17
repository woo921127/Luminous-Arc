#pragma once
#include "gameNode.h"
#include "playerState.h"


struct PlayerState
{
	image* image;
	string name;
	animation* ani;
	POINT Pos;
	int zLevel;
	int x,y;
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

class Player : public gameNode
{
protected:
	PlayerState _player;


public:
	Player();
	~Player();

	virtual HRESULT init(string PlayerName, const char* imageName, int x , int y);
	virtual void release();
	virtual void update();
	virtual void render(float cameraX, float cameraY);

	void initState(int hp, int mp, int AtkDemage, int AtkDefence, int MgDemage, int MgDefence, int move, int jump, int speed, int Accuracy, int level, int exp);



	PlayerState getPlayer() { return _player; }
	image* getimage() { return _player.image; }
	//==================Z레벨====================//
	int getZlevel() { return _player.zLevel; }
	void setZlevel(int Z) { _player.zLevel = Z; }
	//==========================================//


	//============플레이어좌표===============//
	float getX() { return _player.x; }
	float getY() { return _player.y; }
	float getViewX() { return _player.viewX; }
	float getViewY() { return _player.viewY; }

	void setX(float X) { _player.x = X; }
	void setY(float Y) { _player.y = Y; }
	void setviewX(float X) { _player.viewX = X; }
	void setviewY(float Y) { _player.viewY = Y; }
	//=========================================//


	//===========플레이어 스텟=================//
	float getSpeed() { return _player.Speed; }
	void setSpeed(float S) { _player.Speed = S; }


	int getCurrentHp() { return _player.currentHP; }
	void setCurrentHp(int a) { _player.currentHP = a; }


	int getMaxHp() { return _player.MaxHp; }
	void setMaxHp(int a) { _player.MaxHp = a; }

	int getAtkDmg() { return _player.AttackDemage; }
	void setAtkDmg(int a) { _player.AttackDemage = a; }

	int getAtkDef() { return _player.AttackDefence; }
	void setAtkDef(int a) { _player.AttackDefence = a; }

	int getMgcDmg() { return _player.MagicDemage; }
	void setMgcDmg(int a) { _player.MagicDemage = a; }

	int getMgcDef() { return _player.MagicDefence; }
	void setMgcDef(int a) { _player.MagicDefence = a; }


	int getmoveSpeed() { return _player.jump; }
	void setmoveSpeed(int a) { _player.jump = a; }
	
	int getAccuracy() { return _player.Accuracy; }
	void setAccuracy(int a) { _player.Accuracy = a; }

	int getMove() { return _player.Move; }
	void setMove(int a) { _player.Move = a; }

	int getLevel() { return _player.Level; }
	void setLevel(int a) { _player.Level = a; }

	int getExp() { return _player.Exp; }
	void setExp(int a) { _player.Exp = a; }

	int getCurrentMp() { return _player.currentMp; }
	void setCurrentMp(int a) { _player.currentMp; }

	int getMaxMp() { return _player.MaxMp; }
	void setMaxMp(int a) { _player.MaxMp = a; }

	//=========================================//
};

