#pragma once
#include "gameNode.h"
class OptionScene : public gameNode
{
private:


public:
	OptionScene();
	~OptionScene();


	HRESULT init();
	void release();
	void update();
	void render();
};

