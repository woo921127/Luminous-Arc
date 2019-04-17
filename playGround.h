#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "isoMetricScene.h"
#include "battleScene.h"
#include "battleMap.h"
#include "TitleScene.h"
#include "OptionScene.h"
class playGround : public gameNode
{
private:

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	

	playGround();
	~playGround();
};

