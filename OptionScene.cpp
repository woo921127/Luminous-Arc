#include "stdafx.h"
#include "OptionScene.h"


OptionScene::OptionScene()
{
}


OptionScene::~OptionScene()
{
}

HRESULT OptionScene::init()
{

	setWindowsSize(WINSTARTX, WINSTARTY, GAMESIZEX, GAMESIZEY);


	return S_OK;
}

void OptionScene::release()
{
}

void OptionScene::update()
{

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		SCENEMANAGER->changeScene("Å¸ÀÌÆ²");
	}

}

void OptionScene::render()
{
	IMAGEMANAGER->findImage("Title")->render(getMemDC());
}
