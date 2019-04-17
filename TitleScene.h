#pragma once
#include "gameNode.h"

class TitleScene : public gameNode
{
private:


	RECT rc;
	RECT volumeRc;
	RECT voltRc;

	RECT eftVolRc;
	RECT eftVoltRc;

	RECT Box[2];

	char _str[128];

	int logoDown;
	int logoAlpha;
	int moveCount;
	int logoCount;
	
	float volumeMax;

	int TitleNumber;

	bool movecheck;
	bool Boxopen;

	bool z;

	int boxNum;


public:
	TitleScene();
	~TitleScene();


	HRESULT init();
	void release();
	void update();
	void render();


	float getVolume() { return volumeMax; }
	void setVolume(float a) { volumeMax = a; }

};

