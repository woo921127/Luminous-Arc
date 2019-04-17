#include "stdafx.h"
#include "TitleScene.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

HRESULT TitleScene::init()
{
	setWindowsSize(WINSTARTX, WINSTARTY, GAMESIZEX, GAMESIZEY);

	logoDown = -50;
	logoAlpha = 0;
	volumeMax = 1.f;

	Boxopen = false;

	rc = RectMakeCenter(GAMESIZEX / 2, GAMESIZEY / 2 + 150, 400, 400);


	volumeRc = RectMakeCenter(GAMESIZEX / 2, GAMESIZEY / 2 + 90, 300, 10);
	voltRc = RectMakeCenter(GAMESIZEX / 2 + 147, GAMESIZEY / 2 + 90, 10, 30);

	eftVolRc = RectMakeCenter(GAMESIZEX / 2, GAMESIZEY / 2 + 270, 300, 10);
	eftVoltRc = RectMakeCenter(GAMESIZEX / 2 + 147, GAMESIZEY / 2 + 270, 10, 30);


	for (int i = 0; i < 2; ++i)
	{
		Box[i] = RectMakeCenter(GAMESIZEX / 2,( GAMESIZEY / 2 + 20) + (i * 180) , 200, 30);
	}
	IMAGEMANAGER->findImage("Logo")->setAlpahBlend(true);

	SOUNDMANAGER->play("TitleBGM", ASTAR->getVolume());
	return S_OK;
}

void TitleScene::release()
{
}

void TitleScene::update()
{

	
	if (logoAlpha <= 255)
	{
		logoAlpha += 4;
	}
	if (logoAlpha > 255)
	{
		logoAlpha = 255;
	}

	if (logoDown < 100)
	{
		logoDown += 2;
		
	}
	
	if (logoDown >= 100)
	{
		logoDown = 100;
	
	}
	if (z == false)
	{
		if (logoDown == 100)
		{
			movecheck = true;
		}
	}
	if (movecheck == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (TitleNumber > 0)
			{
				TitleNumber--;
			SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (TitleNumber < 2)
			{
				TitleNumber++;
			SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			if (TitleNumber == 0)
			{
				SCENEMANAGER->changeScene("배틀");
				SOUNDMANAGER->stop("TitleBGM");
			}

			if (TitleNumber == 1)
			{
				SCENEMANAGER->changeScene("메트릭스");
				SOUNDMANAGER->stop("TitleBGM");
			}
			if (TitleNumber == 2)
			{
				Boxopen = true;
				movecheck = false;
				z = true;
			}

			SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
		}
	}


	if (Boxopen == true)
	{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			Boxopen = false;
			movecheck = true;
			z = false;
			boxNum = 0;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (boxNum > 0)
			{
				boxNum--;
				SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (boxNum < 1)
			{
				boxNum++;
				SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}



		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (boxNum == 0)
			{
				if (voltRc.left >= volumeRc.left)
				{
					voltRc.left -= 3;
					voltRc.right -= 3;

					if (ASTAR->getVolume() > 0)
					{
						ASTAR->setVolume(ASTAR->getVolume() - 0.011f);
					}
					SOUNDMANAGER->volume("TitleBGM", ASTAR->getVolume());
					SOUNDMANAGER->volume("BattleBGM", ASTAR->getVolume());
					SOUNDMANAGER->volume("MapToolBGM", ASTAR->getVolume());
					if (ASTAR->getVolume() <= 0)
					{
						ASTAR->setVolume(0.0f);
					}
				}
			}
			if (boxNum == 1)
			{
				if (eftVoltRc.left >= eftVolRc.left)
				{
					eftVoltRc.left -= 3;
					eftVoltRc.right -= 3;


					if (ASTAR->getEftVolume() > 0)
					{
						ASTAR->setEftVolume(ASTAR->getEftVolume() - 0.011f);
					}
					SOUNDMANAGER->volume("Synerge", ASTAR->getEftVolume());
					SOUNDMANAGER->volume("choice", ASTAR->getEftVolume());
					SOUNDMANAGER->volume("back", ASTAR->getEftVolume());
					SOUNDMANAGER->volume("move", ASTAR->getEftVolume());

					if (ASTAR->getEftVolume() <= 0)
					{
						ASTAR->setEftVolume(0.0f);
					}
				}
			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (boxNum == 0)
			{
				if (voltRc.right <= volumeRc.right)
				{
					voltRc.left += 3;
					voltRc.right += 3;
					if (ASTAR->getVolume() < 1.0f)
					{
						ASTAR->setVolume(ASTAR->getVolume() + 0.011f);
					}
					SOUNDMANAGER->volume("TitleBGM", ASTAR->getVolume());
					SOUNDMANAGER->volume("BattleBGM", ASTAR->getVolume());
					SOUNDMANAGER->volume("MapToolBGM", ASTAR->getVolume());

					if (ASTAR->getVolume() >= 1.0f)
					{
						ASTAR->setVolume(1.0f);
					}
				}
			}
			if (boxNum == 1)
			{
				if (eftVoltRc.right <= eftVolRc.right)
				{
					eftVoltRc.left += 3;
					eftVoltRc.right += 3;

					if (ASTAR->getEftVolume() < 1.0f)
					{
						ASTAR->setEftVolume(ASTAR->getEftVolume() + 0.011f);
					}
					SOUNDMANAGER->volume("Synerge", ASTAR->getEftVolume());
					SOUNDMANAGER->volume("choice", ASTAR->getEftVolume());
					SOUNDMANAGER->volume("back", ASTAR->getEftVolume());
					SOUNDMANAGER->volume("move", ASTAR->getEftVolume());

					if (ASTAR->getEftVolume() >= 1.0f)
					{
						ASTAR->setEftVolume(1.0f);
					}
				}
			}
		}
	}

}

void TitleScene::render()
{

	IMAGEMANAGER->findImage("Title")->render(getMemDC());

	IMAGEMANAGER->findImage("Logo")->alphaRender(getMemDC(), 212, logoDown, logoAlpha);
	
	if (movecheck == true)
	{
		IMAGEMANAGER->findImage("Start")->render(getMemDC(), 360, 420);
		IMAGEMANAGER->findImage("Maptool")->render(getMemDC(), 360, 520);
		IMAGEMANAGER->findImage("Option")->render(getMemDC(), 360, 620);


		if (TitleNumber == 0)
		{
			IMAGEMANAGER->findImage("Start2")->render(getMemDC(), 360, 420);
		}

		if (TitleNumber == 1)
		{
			IMAGEMANAGER->findImage("Maptool2")->render(getMemDC(), 360, 520);
		}

		if (TitleNumber == 2)
		{
			IMAGEMANAGER->findImage("Option2")->render(getMemDC(), 360, 620);
		}
	}

	if (Boxopen == true)
	{
	
		IMAGEMANAGER->findImage("Edge2")->render(getMemDC(), rc.left, rc.top);

		Rectangle(getMemDC(), volumeRc);
		Rectangle(getMemDC(), voltRc);
		Rectangle(getMemDC(), eftVolRc);
		Rectangle(getMemDC(), eftVoltRc);


		IMAGEMANAGER->findImage("BGM")->render(getMemDC(), Box[0].left, Box[0].top);
		IMAGEMANAGER->findImage("Effect")->render(getMemDC(), Box[1].left, Box[1].top);



		if (boxNum == 0)
		{
			IMAGEMANAGER->findImage("BGM2")->render(getMemDC(), Box[0].left, Box[0].top);
		}

		if (boxNum == 1)
		{
			IMAGEMANAGER->findImage("Effect2")->render(getMemDC(), Box[1].left, Box[1].top);
		}

	}

	//char str[128];
	//sprintf_s(str, "박스오픈 :%d 무브체크 :%d", Boxopen, movecheck);
	//TextOut(getMemDC(), 50, 150, str, strlen(str));


}
