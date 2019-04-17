#pragma once
#include "Player.h"
#define SPEED 10

class battleMap;

class Lucia : public Player
{
private:
	
	RECT rc[6];
	RECT subrc[5];
	RECT StayBoxrc;
	RECT moveEndrc[3];
	RECT moveStayrc[2];
	
	float CameraX;
	float CameraY;



	bool check;
	bool check2;
	bool check3;
	bool change;
	bool moveTile;
	bool Move;
	bool Move2;
	bool moveEnd;
	
	//이동 공격 포인트
	bool e;
	bool f;
	bool mgcPoint;

	bool stayBox;
	bool moveStay;

	

	bool isAttack;
	bool isMagic;

	bool isHit;

	bool starrander;
	bool attackRange;
	bool magicRange;

	bool isDead;



	int boxNum;
	int stateNum;


	int moveStayNumber;
	int stayNumber;

	bool synerge;
	int synergeGage;
	bool synergeRange;
	bool synergeCheck;
	int SyCount;
	bool isSynerge;


	bool moveMotion;
	int idleNumber;
	int moveNumber;
	int endNumber;
	int AtkNumber;
	int MgcNumber;
	int HitNumber;
	int DeadNumber;
	int AtkCount;
	int MgcCount;
	int HitCount;
	int zLevel;

	battleMap* _battle;

public:
	Lucia();
	~Lucia();

	virtual HRESULT init(string PlayerName, const char* imageName, int x, int y);
	virtual void release();
	virtual void update(int x, int y);
	virtual void render(float cameraX, float cameraY);


	void StateRender();

	void luciaState();
	void moving();

	void luciainit(const char* imageName);

	void setBattleManagerAddressLink(battleMap* battle) { _battle = battle; }


	bool getcheck() { return check; }
	void setcheck(bool v) { check = v; }

	bool getchange() { return change; }
	void setchange(bool v) { change = v; }

	bool getmoveTile() { return moveTile; }
	void setmoveTile(bool v) { moveTile = v; }

	bool getMoveMotion() { return moveMotion; }
	void setMoveMotion(bool v) { moveMotion = v; }

	int getidleNumber() { return idleNumber; }
	void setidleNumber(int a) { idleNumber = a; }

	int getmoveNumber() { return moveNumber; }
	void setmoveNumber(int a) { moveNumber = a; }


	int getZlevel() { return zLevel; }
	void setZlevel(int a) { zLevel = a; }

	bool getMovePoint() { return e; }
	void setMovePoint(bool v) { e = v; }

	bool getAtkPoint() { return f; }
	void setAtkPoint(bool v) { f = v; }

	bool getASrender() { return starrander; }
	void setASrender(bool v) { starrander = v; }

	bool getAtkRange() { return attackRange; }
	void setAtkRange(bool v) { attackRange = v; }

	bool getMgcRange() { return magicRange; }
	void setMgcRange(bool v) { magicRange = v; }

	bool getisAttack() { return isAttack; }
	void setisAttack(bool v) { isAttack = v; }

	bool getisMagic() { return isMagic; }
	void setisMagic(bool v) { isMagic = v; }


	int getidleNum() { return idleNumber; }
	void setidleNum(int a) { idleNumber = a; }

	int getAtkNumber() { return AtkNumber; }
	void setAtkNumber(int a) { AtkNumber = a; }

	int getMgcNumber() { return MgcNumber; }
	void setMgcNumber(int a) { MgcNumber = a; }


	bool getMgcPoint() { return mgcPoint; }
	void setMgcPoint(bool v) { mgcPoint = v; }


	bool getHit() { return isHit; }
	void setHit(bool v) { isHit = v; }


	int getHitNumber() { return HitNumber; }
	void setHitNumber(int a) { HitNumber = a; }


	int getHitCount() { return HitCount; }
	void setHitCount(int a) { HitCount = a; }

	bool getDead() { return isDead; }
	void setDead(bool v) { isDead = v; }

	void setDeadNumber(int a) { DeadNumber = a; }

	bool getSynerge() { return synerge; }
	void setSynerge(bool v) { synerge = v; }

	int  getSygage() { return synergeGage; }
	void setSygage(int a) { synergeGage = a; }

	bool getsynergeCheck() { return synergeCheck; }
	void setsynergeCheck(bool v) { synergeCheck = v; }

	bool getsynergeRange() { return synergeRange; }
	void setsynergeRange(bool v) { synergeRange = v; }
};

