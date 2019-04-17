#include "stdafx.h"
#include "Alph.h"
#include "battleMap.h"

Alph::Alph()
{
}


Alph::~Alph()
{
}

HRESULT Alph::init(string PlayerName, const char * imageName, int x, int y)
{
	Player::init(PlayerName, imageName, x , y);
	Player::initState(242, 242, 34, 30, 22, 20, 3, 20, 5.f, 15 ,1 ,0);


	_player.name = PlayerName;
	_player.image = IMAGEMANAGER->findImage(imageName);
	_player.x = x;
	_player.y = y;
	_player.viewX = _player.x;
	_player.viewY = _player.y;
	_player.direction = ALPH_DIRECTION_RIGHT_BOTTOM;
	_player.state = ALPH_STATE_IDLE;
	
	IMAGEMANAGER->findImage(imageName)->setAlpahBlend(true);
	check = true;
	check2 = false;
	moveMotion = false;
	moveEnd = false;
	moveTile = false;

	

	for (int i = 0; i < 3; ++i)
	{
		rc[i] = RectMakeCenter(900, 100 + (i * 70), 200, 50);
	}
	for (int i = 0; i < 3; ++i)
	{
		subrc[i] = RectMakeCenter(900, 100 + (i * 70), 200, 50);
	}

	for (int i = 0; i < 3; ++i)
	{
		moveEndrc[i] = RectMakeCenter(900, 100 + (i * 70), 200, 50);
	}

	for (int i = 0; i < 2; ++i)
	{
		moveStayrc[i] = RectMakeCenter(900, 100 + (i * 70), 200, 50);
	}

	StayBoxrc = RectMakeCenter(900, 100, 200, 50);

	alphinit(imageName);

	_player.alphaValue = 255;
	boxNum = 0;
	subboxNum = 0;

	return S_OK;
}

void Alph::release()
{
}

void Alph::update(int x, int y)
{

	_player.viewX = x;
	_player.viewY = y;

	_player.ani->start();
//======================================================//

	moving();
	alphState();


	if (isHit == false && isDead == true)
	{
		if (_player.alphaValue > 0)
		{
			_player.alphaValue -= 3;
		}
		if (_player.alphaValue <= 0)
		{
			_player.alphaValue = 0;
		}
	}
}



void Alph::alphState()
{
	if (_player.state == ALPH_STATE_IDLE)
	{
		if (moveMotion == false)
		{
			if (idleNumber == 0)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightDownIdle");
			}
			if (idleNumber == 1)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftDownIdle");
			}
			if (idleNumber == 2)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightTopIdle");
			}
			if (idleNumber == 3)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftTopIdle");
			}
		}
	
		if (moveMotion == true)
		{
			if (moveNumber == 0)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftDownMove");
			}

			if (moveNumber == 1)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightDownMove");
			}
			if (moveNumber == 2)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightUpMove");
			}

			if (moveNumber == 3)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftUpMove");
			}

		}
	}

	if (_player.state == ALPH_STATE_ATTACK)
	{
		if (isAttack == true)
		{
			if (AtkNumber == 0)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftDownAtk");
			}
			if (AtkNumber == 1)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightDownAtk");
			}
			if (AtkNumber == 2)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightUpAtk");
			}
			if (AtkNumber == 3)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftUpAtk");
			}
		}
	}

	if (_player.state == ALPH_STATE_SKILL)
	{
		if (isMagic == true)
		{
			if (MgcNumber == 0)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftDownMgc");
			}
			if (MgcNumber == 1)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightDownMgc");
			}
			if (MgcNumber == 2)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightUpMgc");
			}
			if (MgcNumber == 3)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftUpMgc");
			}
		}
	}


	if (isHit == true)
	{
		HitCount++;

		if (hitNumber == 0)
		{
			_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftDownHit");
		}
		if (hitNumber == 1)
		{
			_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightDownHit");
		}
		if (hitNumber == 2)
		{
			_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightUpHit");
		}
		if (hitNumber == 3)
		{
			_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftUpHit");
		}

		if (HitCount > 70)
		{
			isHit = false;
			HitCount = 0;
		}
	}

	if (isHit == false && isDead == true)
	{
		if (DeadNumber == 0)
		{
			_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftDownEnd");
		}
		if (DeadNumber == 1)
		{
			_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightDownEnd");
		}
		if (DeadNumber == 2)
		{
			_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightUpEnd");
		}
		if (DeadNumber == 3)
		{
			_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftUpEnd");
		}
	}
}

void Alph::moving()
{

	if (check == true)
	{
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
			if (boxNum < 2)
			{
				boxNum++;
				SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}
		//첫번째 박스가 열린상태이며 이동버튼을 눌렀을때
		if (boxNum == 0)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				check = false;
				Move = true;
				moveTile = true;
				e = true;
				starrender = true;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}
		//첫번째 박스가 열린상태이며 행동버튼을 눌렀을때
		if (boxNum == 1)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				check = false;
				check2 = true;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}
		//첫번째 박스가 열린상태이며 대기버튼을 눌렀을때
		if (boxNum == 2)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				check = false;
				change = true;
				boxNum = 0;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}
	}
	//행동 박스가 열린 상태
	if (check2 == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (subboxNum > 0)
			{
				subboxNum--;
				SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (subboxNum < 2)
			{
				subboxNum++;
				SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			check = true;
			check2 = false;
			subboxNum = 0;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}

		//행동박스가 열린상태에서 공격 버튼을 눌렀을때
		if (subboxNum == 0)
		{
			if (KEYMANAGER->isOnceKeyDown('1'))
			{
				attackRange = true;
				f = true;
				check2 = false;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}

		if (subboxNum == 1)
		{
			if (KEYMANAGER->isOnceKeyDown('1'))
			{
				magicRange = true;
				check2 = false;
				MgcPoint = true;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}

		if (subboxNum == 2)
		{
			if (KEYMANAGER->isOnceKeyDown('1'))
			{
				synergeRange = true;
				check2 = false;
				synergeCheck = true;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
				
			}
		}
	}


//==========공격중에 취소를 할때=============//
	if (attackRange == true && boxNum == 0)
	{
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			attackRange = false;
			check3 = true;
			isAttack = false;
			f = false;
			_player.state = ALPH_STATE_IDLE;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}
	}

	if (magicRange == true && boxNum == 0)
	{
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			magicRange = false;
			check3 = true;
			isMagic = false;
			MgcPoint = false;
			_player.state = ALPH_STATE_IDLE;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}
	}

	if (synergeRange == true && boxNum == 0)
	{
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			synergeRange = false;
			check3 = true;
			isSynerge = false;
			synergeCheck = false;
			_player.state = ALPH_STATE_IDLE;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}
	}

	if (attackRange == true && boxNum == 1)
	{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			attackRange = false;
			check2 = true;
			isAttack = false;
			f = false;
			_player.state = ALPH_STATE_IDLE;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}
	}

	if (magicRange == true && boxNum == 1)
	{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			magicRange = false;
			check2 = true;
			isMagic = false;
			MgcPoint = false;
			_player.state = ALPH_STATE_IDLE;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}
	}

	if (synergeRange == true && boxNum == 1)
	{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			synergeRange = false;
			check2 = true;
			isSynerge = false;
			synergeCheck = false;
			_player.state = ALPH_STATE_IDLE;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}
	}

	//공격에 성공했을 때
	if (attackRange == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_player.state = ALPH_STATE_ATTACK;
			isAttack = true;
			SOUNDMANAGER->play("Sword", ASTAR->getEftVolume());
		}
	}

	if (boxNum == 0 && isAttack == true)
	{
		atkCount++;
		attackRange = false;
	
		if (atkCount > 70)
		{
			isAttack = false;
			stayBox = true;	
			f = false;
			_player.state = ALPH_STATE_IDLE;
			atkCount = 0;
		}
	}

	if (boxNum == 1 && isAttack == true)
	{
		atkCount++;
		attackRange = false;

		if (atkCount > 70)
		{
			isAttack = false;
			moveStay = true;
			f = false;
			_player.state = ALPH_STATE_IDLE;
			atkCount = 0;
		}
	}


	//마법 공격
	if (magicRange == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_player.state = ALPH_STATE_SKILL;
			isMagic = true;
			SOUNDMANAGER->play("bomb", ASTAR->getEftVolume());
		}
	}

	
	if (boxNum == 0 && isMagic == true)
	{
		MgcCount++;
		magicRange = false;

		if (MgcCount > 70)
		{
			isMagic = false;
			stayBox = true;
			MgcPoint = false;
			_player.state = ALPH_STATE_IDLE;
			MgcCount = 0;
		}
	}

	if (boxNum == 1 && isMagic == true)
	{
		MgcCount++;
		magicRange = false;

		if (MgcCount > 70)
		{
			isMagic = false;
			moveStay = true;
			MgcPoint = false;
			_player.state = ALPH_STATE_IDLE;
			MgcCount = 0;
		}
	}

	//시너지 공격
	if (synergeRange == true)
	{
		if (KEYMANAGER->isOnceKeyDown('2'))
		{
			if (synergeGage >= 242)
			{
				synerge = true;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}
	}

	if (boxNum == 0 && synerge == true)
	{
		SyCount++;

		if (SyCount > 90)
		{
			stayBox = true;
			SyCount = 0;
		}
	}
	
	if (boxNum == 1 && synerge == true)
	{
		SyCount++;

		if (SyCount > 90)
		{
			moveStay = true;
		}
	}

	//=================이동을 눌렀을때 ====================//
	
	if (Move == true)
	{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			Move = false;
			check = true;
			e = false;
			starrender = false;
			a = 0;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}

		if (moveTile == false)
		{
			Move = false;
			moveEnd = true;
			a = 0;
			
		}
	}

	if (moveEnd == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (endNumber > 0)
			{
				endNumber--;
				SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (endNumber < 1)
			{
				endNumber++;
				SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}

		if (endNumber == 0)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				check3 = true;
				moveEnd = false;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}
		if (endNumber == 1)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				moveEnd = false;
				change = true;
				endNumber = 0;
				boxNum = 0;
				subboxNum = 0;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}

		}
	}

	if (check3 == true)
	{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			moveEnd = true;
			check3 = false;
			subboxNum = 0;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (subboxNum > 0)
			{
				subboxNum--;
				SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (subboxNum < 2)
			{
				subboxNum++;
				SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}

		if (subboxNum == 0)
		{
			if (KEYMANAGER->isOnceKeyDown('1'))
			{
				attackRange = true;
				f = true;
				check3 = false;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}

		if (subboxNum == 1)
		{
			if (KEYMANAGER->isOnceKeyDown('1'))
			{
				magicRange = true;
				check3 = false;
				MgcPoint = true;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}

		if (subboxNum == 2)
		{
			if (KEYMANAGER->isOnceKeyDown('1'))
			{
				synergeRange = true;
				check3 = false;
				synergeCheck = true;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}
	}


	if (stayBox == true)
	{
		if (stayNumber == 0)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				stayBox = false;
				change  = true;
				boxNum = 0;
				subboxNum = 0;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}

	}


	if (moveStay == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (moveStayNumber > 0)
			{
				moveStayNumber--;
				SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (moveStayNumber < 1)
			{
				moveStayNumber++;
				SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}

		if (moveStayNumber == 0)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				Move2 = true;
				moveTile = true;
				e = true;
				starrender = true;
				moveStay = false;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}
		if (moveStayNumber == 1)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				moveStay = false;
				change = true;
				moveStayNumber = 0;
				boxNum = 0;
				subboxNum = 0;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}
	}


	if (Move2 == true)
	{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			Move2 = false;
			//moveTile = false;
			e = false;
			starrender = false;
			moveStay = true;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}

		if (moveTile == false)
		{
			Move2 = false;
			stayBox = true;
			a = 0;

		}
	}



}

void Alph::callbackAttack(void * obj)
{
	Player* AlphAttack = (Player*)obj;

}

void Alph::alphinit(const char* imageName)
{
	int leftDownIdle[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftDownIdle", imageName, leftDownIdle, 4, SPEED, true);

	int rightDownIdle[] = { 7, 6, 5 ,4 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightDownIdle", imageName, rightDownIdle, 4, SPEED, true);

	int leftTopIdle[] = { 8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftTopIdle", imageName, leftTopIdle, 4, SPEED, true);

	int rightTopIdle[] = { 15, 14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightTopIdle", imageName, rightTopIdle, 4, SPEED, true);

	int leftDownMove[] = { 24,25,26,27,28,29};
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftDownMove", imageName, leftDownMove, 6, SPEED, true);
	
	int rightDownMove[] = {35,34,33,32,31,30};
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightDownMove", imageName, rightDownMove, 6, SPEED, true);

	int leftUpMove[] = { 36,37,38,39,40,41};
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftUpMove", imageName, leftUpMove, 6, SPEED, true);

	int rightUpMove[] = { 47,46,45,44,43,42};
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightUpMove", imageName, rightUpMove, 6, SPEED, true);


	int leftDownAtk[] = { 48,49,50,51 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftDownAtk", imageName, leftDownAtk, 4,4, true);

	int rightDownAtk[] = { 55,54,53,52 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightDownAtk", imageName, rightDownAtk, 4, 4, true);

	int leftUpAtk[] = { 56,57,58,59 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftUpAtk", imageName, leftUpAtk, 4, 4, true);
	
	int rightUpAtk[] = { 63,62,61,60 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightUpAtk", imageName, rightUpAtk, 4, 4, true);
	
	int leftDownMgc[] = { 72,73,74,75 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftDownMgc", imageName, leftDownMgc, 4, 4, true);

	int rightDownMgc[] = { 79,78,77,76 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightDownMgc", imageName, rightDownMgc, 4, 4, true);

	int leftUpMgc[] = { 80,81,82,83 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftUpMgc", imageName, leftUpMgc, 4, 4, true);

	int rightUpMgc[] = { 87,86,85,84 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightUpMgc", imageName, rightUpMgc, 4, 4, true);

	int leftDownHit[] = { 96,97,98,99,100,101,102 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftDownHit", imageName, leftDownHit, 7, 4, true);

	int rightDownHit[] = { 109,108,107,106,105,104,103 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightDownHit", imageName, rightDownHit, 7, 4, true);

	int leftUpHit[] = { 120,121,122,123,124,125,126};
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftUpHit", imageName, leftUpHit, 7, 4, true);

	int rightUpHit[] = { 133,132,131,130,129,128,127 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightUpHit", imageName, rightUpHit, 7, 4, true);

	int leftDownEnd[]{ 110 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftDownEnd", imageName, leftDownEnd, 1, 4, false);

	int rightDownEnd[]{ 111 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightDownEnd", imageName, rightDownEnd, 1, 4, false);

	int leftUpEnd[]{ 134 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftUpEnd", imageName, leftUpEnd, 1, 4, false);

	int rightUpEnd[]{ 135 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightUpEnd", imageName, rightUpEnd, 1, 4, false);



	_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftDownIdle");
}

void Alph::StateRender()
{
	if (check == true)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (i == 0)
			{
				IMAGEMANAGER->render("move", getMemDC(), rc[i].left, rc[i].top);
			}

			if (i == 1)
			{
				IMAGEMANAGER->render("action", getMemDC(), rc[i].left, rc[i].top);
			}

			if (i == 2)
			{
				IMAGEMANAGER->render("wait", getMemDC(), rc[i].left, rc[i].top);
			}
		}

		if (boxNum == 0)
		{
			IMAGEMANAGER->render("move2", getMemDC(), rc[0].left, rc[0].top);
		}

		else if (boxNum == 1)
		{
			IMAGEMANAGER->render("action2", getMemDC(), rc[1].left, rc[1].top);
		}

		else if (boxNum == 2)
		{
			IMAGEMANAGER->render("wait2", getMemDC(), rc[2].left, rc[2].top);
		}

	}

	if (check2 == true)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (i == 0)
			{
				IMAGEMANAGER->render("attack", getMemDC(), subrc[i].left, subrc[i].top);
			}
			if (i == 1)
			{
				IMAGEMANAGER->render("magic", getMemDC(), subrc[i].left, subrc[i].top);
			}
			if (i == 2)
			{
				IMAGEMANAGER->render("synergy", getMemDC(), subrc[i].left, subrc[i].top);
			}
		}

		if (subboxNum == 0)
		{
			IMAGEMANAGER->render("attack2", getMemDC(), subrc[0].left, subrc[0].top);

		}
		else if (subboxNum == 1)
		{
			IMAGEMANAGER->render("magic2", getMemDC(), subrc[1].left, subrc[1].top);
		}
		else if (subboxNum == 2)
		{
			IMAGEMANAGER->render("synergy2", getMemDC(), subrc[2].left, subrc[2].top);
		}
	}

	if (check3 == true)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (i == 0)
			{
				IMAGEMANAGER->render("attack", getMemDC(), subrc[i].left, subrc[i].top);
			}
			if (i == 1)
			{
				IMAGEMANAGER->render("magic", getMemDC(), subrc[i].left, subrc[i].top);
			}
			if (i == 2)
			{
				IMAGEMANAGER->render("synergy", getMemDC(), subrc[i].left, subrc[i].top);
			}
		}

		if (subboxNum == 0)
		{
			IMAGEMANAGER->render("attack2", getMemDC(), subrc[0].left, subrc[0].top);

		}
		else if (subboxNum == 1)
		{
			IMAGEMANAGER->render("magic2", getMemDC(), subrc[1].left, subrc[1].top);
		}
		else if (subboxNum == 2)
		{
			IMAGEMANAGER->render("synergy2", getMemDC(), subrc[2].left, subrc[2].top);
		}
	}


	if (moveEnd == true)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (i == 0)
			{
				IMAGEMANAGER->render("action", getMemDC(), moveEndrc[i].left, moveEndrc[i].top);
			}
			if (i == 1)
			{
				IMAGEMANAGER->render("wait", getMemDC(), moveEndrc[i].left, moveEndrc[i].top);
			}
		}
		if (endNumber == 0)
		{
			IMAGEMANAGER->render("action2", getMemDC(), moveEndrc[0].left, moveEndrc[0].top);
		}
		else if (endNumber == 1)
		{
			IMAGEMANAGER->render("wait2", getMemDC(), moveEndrc[1].left, moveEndrc[1].top);
		}
	}

	if (stayBox == true)
	{
		if (stayNumber == 0)
		{
			IMAGEMANAGER->render("wait2", getMemDC(), StayBoxrc.left, StayBoxrc.top);
		}
	}



	if (moveStay == true)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (i == 0)
			{
				IMAGEMANAGER->render("move", getMemDC(), moveStayrc[i].left, moveStayrc[i].top);
			}
			if (i == 1)
			{
				IMAGEMANAGER->render("wait", getMemDC(), moveStayrc[i].left, moveStayrc[i].top);
			}
		}
		if (moveStayNumber == 0)
		{
			IMAGEMANAGER->render("move2", getMemDC(), moveStayrc[0].left, moveStayrc[0].top);
		}
		else if (moveStayNumber == 1)
		{
			IMAGEMANAGER->render("wait2", getMemDC(), moveStayrc[1].left, moveStayrc[1].top);
		}
	}



	if (moveMotion == true)
	{
		a = 1;
	}
	
	char str[128];

	sprintf_s(str, "알프메인박스:%d  알프행동박스:%d  알프앤드박스:%d  체크1: %d  체크2: %d  체크3: %d 무브앤드: %d  카메라체인지: %d" , boxNum, subboxNum, endNumber, check  , check2,check3 , moveEnd , change);
	TextOut(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 20, 500, str, strlen(str));
	sprintf_s(str, "무브:%d  무브타일:%d   e : %d  어택상태 : %d  어택카운터 : %d", Move , moveTile , e, attackRange , atkCount);
	TextOut(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 20, 530, str, strlen(str));
	sprintf_s(str, "히트 :%d  히트넘버 :%d  히트카운트 :%d  무브스테이 :%d 무브스테이넘버 :%d 스테이박스 :%d  스테이넘버 :%d", isHit, hitNumber, HitCount , moveStay , moveStayNumber, stayBox , stayNumber);
	TextOut(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 20, 560, str, strlen(str));
	sprintf_s(str, "시너지 :%d  시너지범위 :%d  시너지체크 :%d", synerge, synergeRange, synergeCheck);
	TextOut(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 20, 750, str, strlen(str));
}
void Alph::render(float cameraX, float cameraY)
{
	_player.image->alphaAniRenderCenter(getMemDC(), _player.viewX - cameraX, _player.viewY - cameraY -32 - c  , _player.ani, _player.alphaValue);
}