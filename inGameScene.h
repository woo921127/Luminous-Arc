#pragma once
#include "gameNode.h"

//������ �ΰ����� ������ Ŭ���

class inGameScene : public gameNode
{
public:
	inGameScene();
	~inGameScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

