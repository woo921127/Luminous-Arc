#include "stdafx.h"
#include "Lucia.h"
#include "battleMap.h"

Lucia::Lucia()
{
}


Lucia::~Lucia()
{
}

HRESULT Lucia::init(string PlayerName, const char * imageName, int x, int y)
{
	Player::init(PlayerName, imageName, x, y);
	Player::initState(242, 242, 23, 20, 38, 35, 4, 20, 5.f, 31 ,1 ,0);
	_player.name = PlayerName;
	_player.image = IMAGEMANAGER->findImage(imageName);
	_player.x = x;
	_player.y = y;
	_player.viewX = _player.x;
	_player.viewY = _player.y;
	IMAGEMANAGER->findImage(imageName)->setAlpahBlend(true);
	_player.direction = LUCIA_DIRECTION_RIGHT_TOP;
	_player.state = LUCIA_STATE_IDLE;
	_player.alphaValue = 255;


	check = false;
	check2 = false;
	Move = false;

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

	luciainit(imageName);


	return S_OK;
}

void Lucia::release()
{
}

void Lucia::update(int x, int y)
{

	_player.viewX = x;
	_player.viewY = y;
	
	_player.ani->start();
	
	luciaState();
	moving();

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

void Lucia::render(float cameraX, float cameraY)
{
	_player.image->alphaAniRenderCenter(getMemDC(), _player.viewX - cameraX, _player.viewY - cameraY - 45 - zLevel, _player.ani, _player.alphaValue);

}

void Lucia::StateRender()
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

	else if (check2 == true)
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

		if (stateNum == 0)
		{
			IMAGEMANAGER->render("attack2", getMemDC(), subrc[0].left, subrc[0].top);
		}

		else if (stateNum == 1)
		{
			IMAGEMANAGER->render("magic2", getMemDC(), subrc[1].left, subrc[1].top);
		}

		else if (stateNum == 2)
		{
			IMAGEMANAGER->render("synergy2", getMemDC(), subrc[2].left, subrc[2].top);
		}
	}

	else if (check3 == true)
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

		if (stateNum == 0)
		{
			IMAGEMANAGER->render("attack2", getMemDC(), subrc[0].left, subrc[0].top);

		}
		else if (stateNum == 1)
		{
			IMAGEMANAGER->render("magic2", getMemDC(), subrc[1].left, subrc[1].top);
		}
		else if (stateNum == 2)
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


	char str[128];

	//sprintf_s(str, "루시아메인박스:%d  루시아행동박스:%d  루시아앤드박스:%d 체크1: %d  체크2: %d  체크3: %d 무브앤드 :%d  카메라체인지 :%d ", boxNum, stateNum, endNumber, check,check2,check3 , moveEnd, change);
	//TextOut(getMemDC(), 50, 200, str, strlen(str));
	//sprintf_s(str, "무브:%d  무브타일:%d 무브대기:%d 무브대기넘버:%d 대기넘버:%d", Move, moveTile, moveStay, moveStayNumber, stayNumber);
	//TextOut(getMemDC(), 50, 150, str, strlen(str));
	//sprintf_s(str, "히트 :%d  히트넘버 :%d  히트카운트 :%d", isHit,HitNumber,HitCount);
	//TextOut(getMemDC(), 50, 150, str, strlen(str));

}

void Lucia::luciaState()
{
	if (_player.state == LUCIA_STATE_IDLE)
	{

		if (moveMotion == false)
		{
			if (idleNumber == 0)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftDownIdle");
			}
			if (idleNumber == 1)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightDownIdle");
			}
			if (idleNumber == 2)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftTopIdle");
			}
			if (idleNumber == 3)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightTopIdle");
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
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftUpMove");
			}
			if (moveNumber == 3)
			{
				_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightUpMove");
			}
		}

	}

	if (_player.state == LUCIA_STATE_ATTACK)
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

	if (_player.state == LUCIA_STATE_SKILL)
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

		if (HitNumber == 0)
		{
			_player.ani = KEYANIMANAGER->findAnimation(_player.name, "leftDownHit");
		}
		if (HitNumber == 1)
		{
			_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightDownHit");
		}
		if (HitNumber == 2)
		{
			_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightUpHit");
		}
		if (HitNumber == 3)
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

void Lucia::moving()
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
				starrander = true;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}
		//첫번째 박스가 열린상태이며 행동버튼을 눌렀을때
		else if (boxNum == 1)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				check = false;
				check2 = true;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}
		//첫번째 박스가 열린상태이며 대기버튼을 눌렀을때
		else if (boxNum == 2)
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

	if (check2 == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (stateNum > 0)
			{
				stateNum--;
				SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (stateNum < 2)
			{
				stateNum++;
				SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			check = true;
			check2 = false;
			stateNum = 0;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}


		if (stateNum == 0)
		{
			if (KEYMANAGER->isOnceKeyDown('1'))
			{
				attackRange = true;
				check2 = false;
				f = true;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}

		if (stateNum == 1)
		{
			if (KEYMANAGER->isOnceKeyDown('1'))
			{
				magicRange = true;
				check2 = false;
				mgcPoint = true;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}

		if (stateNum == 2)
		{
			if (KEYMANAGER->isOnceKeyDown('1'))
			{
				if (synergeGage >= 242)
				{
					synergeRange = true;
					check2 = false;
					synergeCheck = true;
					SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
				}
			}
		}
	}

	if (attackRange == true && boxNum == 0)
	{
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			attackRange = false;
			check3 = true;
			f = false;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}
	}

	if (magicRange == true && boxNum == 0)
	{
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			magicRange = false;
			check3 = true;
			mgcPoint = false;
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
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}
	}

	if (attackRange == true && boxNum == 1)
	{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			attackRange = false;
			check2 = true;
			f = false;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}
	}

	if (magicRange == true && boxNum == 1)
	{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			magicRange = false;
			check2 = true;
			mgcPoint = false;
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
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}
	}


	//공격을 눌렀을때

	if (attackRange == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_player.state = LUCIA_STATE_ATTACK;
			isAttack = true;
			SOUNDMANAGER->play("spear", ASTAR->getEftVolume());
		}
	}

	//공격에 성공할때
	if (boxNum == 0 && isAttack == true)
	{
		AtkCount++;
		attackRange = false;

		if (AtkCount > 70)
		{
			isAttack = false;
			stayBox = true;
			f = false;
			_player.state = LUCIA_STATE_IDLE;
			AtkCount = 0;
		}
	}

	if (boxNum == 1 && isAttack == true)
	{
		AtkCount++;
		attackRange = false;

		if (AtkCount > 70)
		{
			isAttack = false;
			moveStay = true;
			f = false;
			_player.state = LUCIA_STATE_IDLE;
			AtkCount = 0;
		}
	}

	//마법공격에 성공할때

	if (magicRange == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_player.state = LUCIA_STATE_SKILL;
			isMagic = true;
			SOUNDMANAGER->play("fire", ASTAR->getEftVolume());
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
			mgcPoint = false;
			_player.state = LUCIA_STATE_IDLE;
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
			mgcPoint = false;
			_player.state = LUCIA_STATE_IDLE;
			MgcCount = 0;
		}
	}
	// 시너지공격 성공했을때
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
			starrander = false;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}

		if (moveTile == false)
		{
			Move = false;
			moveEnd = true;
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
				stateNum = 0;
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
			stateNum = 0;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (stateNum > 0)
			{
				stateNum--;
				SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (stateNum < 2)
			{
				stateNum++;
				SOUNDMANAGER->play("move", ASTAR->getEftVolume());
			}
		}

		if (stateNum == 0)
		{
			if (KEYMANAGER->isOnceKeyDown('1'))
			{
				attackRange = true;
				check3 = false;
				f = true;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}

		if (stateNum == 1)
		{
			if (KEYMANAGER->isOnceKeyDown('1'))
			{
				magicRange = true;
				check3 = false;
				mgcPoint = true;
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
				change = true;
				boxNum = 0;
				stateNum = 0;
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
				starrander = true;
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
				stateNum = 0;
				SOUNDMANAGER->play("choice", ASTAR->getEftVolume());
			}
		}
	}
	if (Move2 == true)
	{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			Move2 = false;
	
			e = false;
			starrander = false;
			moveStay = true;
			SOUNDMANAGER->play("back", ASTAR->getEftVolume());
		}

		if (moveTile == false)
		{
			Move2 = false;
			stayBox = true;
		}
	}
}

void Lucia::luciainit(const char * imageName)
{
	int leftDownIdle[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftDownIdle", imageName, leftDownIdle, 4, SPEED, true);

	int rightDownIdle[] = { 7, 6, 5,4 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightDownIdle", imageName, rightDownIdle, 4, SPEED, true);

	int leftTopIdle[] = { 8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftTopIdle", imageName, leftTopIdle, 4, SPEED, true);

	int rightTopIdle[] = { 15, 14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightTopIdle", imageName, rightTopIdle, 4, SPEED, true);

	int leftDownHit[] = { 18,19,20,21,22,23,24 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftDownHit", imageName, leftDownHit, 7, SPEED, true);

	int rightDownHit[] = { 31,30,29,28,27,26,25 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightDownHit", imageName, rightDownHit, 7, SPEED, true);

	int leftUpHit[] = { 36,37,38,39,40,41,42};
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftUpHit", imageName, leftUpHit, 7, SPEED, true);

	int rightUpHit[] = { 49,48,47,46,45,44,43 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightUpHit", imageName, rightUpHit, 7, SPEED, true);

	int leftDownMove[]{54,55,56,57,58,59};
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftDownMove", imageName, leftDownMove, 6, SPEED, true);

	int rightDownMove[]{ 65,64,63,62,61,60 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightDownMove", imageName, rightDownMove, 6, SPEED, true);

	int leftUpMove[]{ 72,73,74,75,76,77 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftUpMove", imageName, leftUpMove, 6, SPEED, true);

	int rightUpMove[]{ 83,82,81,80,79,78 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightUpMove", imageName, rightUpMove, 6, SPEED, true);

	int leftDownAtk[]{ 90,91,92,93 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftDownAtk", imageName, leftDownAtk, 4, 4, true);

	int rightDownAtk[]{ 97,96,95,94 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightDownAtk", imageName, rightDownAtk, 4, 4, true);

	int leftUpAtk[]{ 98,99,100,101 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftUpAtk", imageName, leftUpAtk, 4, 4, true);

	int rightUpAtk[]{ 105,104,103,102 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightUpAtk", imageName, rightUpAtk, 4, 4, true);

	int leftDownMgc[]{ 108,109,110,111 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftDownMgc", imageName, leftDownMgc, 4, 4, true);

	int rightDownMgc[]{ 115,114,113,112 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightDownMgc", imageName, rightDownMgc, 4, 4, true);

	int leftUpMgc[]{ 116,117,118,119 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftUpMgc", imageName, leftUpMgc, 4, 4, true);

	int rightUpMgc[]{ 120,121,122,123 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightUpMgc", imageName, rightUpMgc, 4, 5, true);

	int leftDownEnd[]{ 50 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftDownEnd", imageName, leftDownEnd, 1, 4, false);

	int rightDownEnd[]{ 51 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightDownEnd", imageName, rightDownEnd, 1, 4, false);

	int leftUpEnd[]{ 52 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "leftUpEnd", imageName, leftUpEnd, 1, 4, false);

	int rightUpEnd[]{ 53 };
	KEYANIMANAGER->addArrayFrameAnimation(_player.name, "rightUpEnd", imageName, rightUpEnd, 1, 4, false);

	_player.ani = KEYANIMANAGER->findAnimation(_player.name, "rightDownIdle");
}
