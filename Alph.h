#pragma once
#include "Player.h"


#define SPEED 4
class battleMap;

class Alph : public Player
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
	bool Move;
	bool Move2;
	bool change;
	bool h;
	bool stayBox;
	bool moveStay;

	
	bool attackRange;
	bool isAttack;
	bool isMagic;
	bool isSynerge;
	bool isHit;
	bool magicRange;
	int a;

	int c;

	bool synerge;
	int synergeGage;
	bool synergeRange;
	bool synergeCheck;

	int moveNumber;
	int idleNumber;
	int AtkNumber;
	int MgcNumber;
	int hitNumber;
	int SyCount;

	int moveStayNumber;
	int endNumber;
	int stayNumber;

	bool moveMotion;

	int boxNum;

	int subboxNum;

	bool isDead;
	int DeadNumber;

	bool e;
	bool f;
	bool MgcPoint;



	bool starrender;

	bool alphRange;

	bool moveEnd;


	bool moveTile;
	bool Start;

	battleMap* _battle;

	int atkCount;
	int MgcCount;
	int HitCount;
public:
	Alph();
	~Alph();

	virtual HRESULT init(string PlayerName, const char* imageName, int x, int y);
	virtual void release();
	virtual void update(int x, int y);
	virtual void render(float cameraX, float cameraY);


	void StateRender();

	void alphState();
	void moving();


	//콜백 함수/////////

	static void callbackAttack(void* obj);

	void alphinit(const char* imageName);

	void setBattleManagerAddressLink(battleMap* battle) { _battle = battle; }


	bool getCheck() { return check; }
	void setCheck(bool c) { check = c; }

	bool getMove() { return Move; }
	void setMove(bool c) { Move = c; }

	bool getMoveMotion() { return moveMotion; }
	void setMoveMotion(bool c) { moveMotion = c; }


	int getmoveNum() { return moveNumber; }
	void setmoveNum(int a) { moveNumber = a; }

	int getidleNum() { return idleNumber; }
	void setidleNum(int a) { idleNumber = a; }


	bool getalphRange() { return alphRange; }
	void setalphRange(bool v) { alphRange = v; }

	int getZlevel() { return c; }
	void setZlevel(int a) { c = a; }

	bool getMoveEnd() { return moveEnd; }
	void setMoveEnd(bool v) { moveEnd = v; }


	bool getmoveTile() { return moveTile; }
	void setmoveTile(bool v) { moveTile = v; }

	bool getE() { return e; }
	void setE(bool v) { e = v; }


	bool getF() { return f; }
	void setF(bool v) { f = v; }

	bool getchange() { return change; }
	void setchange(bool v) { change = v; }


	bool getAtkRange() { return attackRange; }
	void setAtkRange(bool v) { attackRange = v; }

	
	bool getMgcRange() { return magicRange; }


	bool getASrender() { return starrender; }
	void setASrender(bool v) { starrender = v; }


	int getAtkNumber() { return AtkNumber; }
	void setAtkNumber(int a) { AtkNumber = a; }

	int getMgcNumber() { return MgcNumber; }
	void setMgcNumber(int a) { MgcNumber = a; }

	bool getisAttack() { return isAttack; }
	void setisAttack(bool v) { isAttack = v; }

	bool getisMagic() { return isMagic; }
	void setisMagic(bool v) { isMagic = v; }
	
	bool getisMgcPoint() { return MgcPoint; }
	void setisMgcPoint(bool v) { MgcPoint = v; }


	bool getHit() { return isHit; }
	void setHit(bool v) { isHit = v; }

	int getHitNumber() { return hitNumber; }
	void setHitNumber(int v) { hitNumber = v; }


	bool getDead() { return isDead; }
	void setDead(bool v) { isDead = v; }

	void setDeadNumber(int a) { DeadNumber = a; }


	bool getSynerge() { return synerge; }
	void setSynerge(bool v) { synerge = v; }

	int  getSygage() { return synergeGage; }
	void setSygage(int a) { synergeGage = a; }

	bool getsynergeRange() { return synergeRange; }
	void setsynergeRange(bool v) { synergeRange = v; }

	bool getsynergeCheck() {return synergeCheck;}
	void setsynergeCheck(bool v) { synergeCheck = v; }
};

