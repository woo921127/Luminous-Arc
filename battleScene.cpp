#include "stdafx.h"
#include "battleScene.h"


battleScene::battleScene()
{
}


battleScene::~battleScene()
{
}

HRESULT battleScene::init()
{
	setWindowsSize(WINSTARTX, WINSTARTY, 1800, GAMESIZEY);

	
	_battle = new battleMap;
	_camera = new camera;
	_alph = new Alph;
	_lucia = new Lucia;
	_astar = new aStarMove;
	_luciaAstar = new LuciaAstar;
	_enemy = new Enemy;
	_enemyAstar = new EnemyAstar;

	fire = IMAGEMANAGER->findImage("fire2");
	bomb = IMAGEMANAGER->findImage("fireBomb");
	puple = IMAGEMANAGER->findImage("puple2");
	Zlevel = 0;

	aZ = 37;
	lZ = 38;
	//알프 초기위치//
	alphX = 1;
	alphY = 8;

	//루시아 초기위치//
	luciaX = 9;
	luciaY = 9;

	//에너미 초기위치//

	enemyX = 0;
	enemyY = 0;

	//알프 루시아 기본 세팅 //
	_alphHp = 242;
	_alphMp = 242;
	_alphFp = 242;

	_luciaHp = 242;
	_luciaMp = 242;
	_luciaFp = 242;


	_enemyHp = 242;
	_enemyMp = 242;
	_enemyFp = 242;


	_alph->setSygage(_alphFp);
	_lucia->setSygage(_luciaFp);
	_enemy->setSygage(_enemyFp);
	//========================//
	
	//체력바 위치//
	alphHp = RectMake(18, 314, _alphHp, 26);
	alphMp = RectMake(18, 367, _alphMp, 26);
	alphFp = RectMake(18, 447, _alphFp, 26);

	luciaHp = RectMake(18, 314, _luciaHp, 26);
	luciaMp = RectMake(18, 367, _luciaMp, 26);
	luciaFp = RectMake(18, 447, _luciaFp, 26);


	EnemyHp = RectMake(18, 314, _enemyHp, 26);
	EnemyMp = RectMake(18, 367, _enemyMp, 26);
	EnemyFp = RectMake(18, 447, _enemyFp, 26);
	//==============//

	


	MovePointX = alphX;
	MovePointY = alphY;

	LuciaPointX = luciaX;
	LuciaPointY = luciaY;

	EnemyPointX = enemyX;
	EnemyPointY = enemyY;


	Camerachange = false;
	alphCamera = true;
	luciaCamera = false;


	StartCamera = false;

	alphmoving = false;
	luciamoving = false;
	
	_battle->init();
	_alph->init("alph2", "alph2", _battle->getclassTile(alphX, alphY)->getPos(), _battle->getclassTile(alphX, alphY)->getPosY() - alPhZ);
	_lucia->init("lucia2,", "lucia2", _battle->getclassTile(luciaX, luciaY)->getPos(), _battle->getclassTile(luciaX, luciaY)->getPosY() - luciaZ + 6);
	_enemy->init("Iris", "Iris", _battle->getclassTile(enemyX, enemyY)->getPos(), _battle->getclassTile(enemyX, enemyY)->getPosY() - enemyZ);


	_astar->init();
	_astar->setTileNum(&NumTile);
	_vvStar = _astar->getLoad();


	_luciaAstar->init();
	_luciaAstar->setTileNum(&LuciNumTile);
	_vvluciStar = _luciaAstar->getLoad();


	_enemyAstar->init();
	_enemyAstar->setTileNum(&EnemyNumtile);
	_vvEnemyStar = _enemyAstar->getLoad();

	_tileNum = {12,12};
	_luciaTileNum = { 12,12};
	_enemyTileNum = { 12,12 };


	ZORDER->InPutObj(_alph);
	ZORDER->InPutObj(_lucia);
	ZORDER->InPutObj(_enemy);

	_alph->setBattleManagerAddressLink(_battle);
	_lucia->setBattleManagerAddressLink(_battle);
	_enemy->setBattleManagerAddressLink(_battle);

	_battle->setLuciaManagerAddressLink(_lucia);
	_battle->setAlphManagerAddressLink(_alph);
	_battle->setEnemyManagerAddressLink(_enemy);
	
	_camera->init(2400, GAMESIZEY, 4200, 3000);

	_astar->setAlph(_alph);
	
	_luciaAstar->setlucia(_lucia);

	_enemyAstar->setEnemy(_enemy);

	SOUNDMANAGER->play("BattleBGM", ASTAR->getVolume());

	return S_OK;
}

void battleScene::release()
{
	SAFE_DELETE(_alph);
	SAFE_DELETE(_lucia);
	SAFE_DELETE(_battle);
	SAFE_DELETE(_enemy);
	ZORDER->Release();
	ASTAR->release();
}

void battleScene::update()
{
	_alph->setZorderY(_alph->getViewY());
	_lucia->setZorderY(_lucia->getViewY());
	_enemy->setZorderY(_enemy->getViewY());

	ZORDER->update();

	_alph->update(_alph->getViewX(), _alph->getViewY());
	_lucia->update(_lucia->getViewX(), _lucia->getViewY());
	_enemy->update(_enemy->getViewX(), _enemy->getViewY());

	alphTileMove();
	luciaTileMove();
	EnemyTileMove();

	PlayerCollision();
	zMove();
	cameraMove();
	PlayerDead();
	//==================aStar 확인해보기 ================================//

	astarMove();

	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD2))
	{
		_alph->setExp(_alph->getExp() + 2);
	}

	if (_alph->getExp() >= 100)
	{
		_alph->setLevel(_alph->getLevel() + 1);
		_alph->setAtkDmg(_alph->getAtkDmg() + 2);
		_alph->setAtkDef(_alph->getAtkDef() + 2);
		_alph->setMgcDmg(_alph->getMgcDmg() + 1);
		_alph->setMgcDef(_alph->getMgcDef() + 1);
		_alph->setAccuracy(_alph->getAccuracy() + 2);
		_alph->setmoveSpeed(_alph->getmoveSpeed() + 2);
		
		_alph->setExp(0);
	}

	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		tt = true;
	}

	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD1))
	{
		//if (_alph->getCurrentMp() > 0)
		{
			_alph->setMaxMp(_alph->getMaxMp() - 1);
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD3))
	{
		if (_alphFp < 242)
		{
			_alphFp++;
			_alph->setSygage(_alph->getSygage() + 1);
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD4))
	{
		if (_luciaFp < 242)
		{
			_luciaFp++;
			_lucia->setSygage(_lucia->getSygage() + 1);
		}
	}


	alphMgcDmg = (_alph->getMgcDmg() * 6) - (_enemy->getMgcDef() * 5);
	alphAtkDmg = (_alph->getAtkDmg() * 4) - (_enemy->getAtkDef() * 5);

	luciaMgcDmg = (_lucia->getMgcDmg() * 4) - (_enemy->getMgcDef() * 5);
	luciaAtkDmg = (_lucia->getAtkDmg() * 5) - (_enemy->getAtkDef() * 5);


	EnemyAlphMgcDmg = (_enemy->getMgcDmg() * 6) - (_alph->getMgcDef() * 5);
	EnemyAlphAtkDmg = (_enemy->getAtkDmg() * 10) - (_alph->getAtkDef() * 5);

	EnemyLuciaMgcDmg = (_enemy->getMgcDmg() * 8) - (_lucia->getMgcDef() * 5);
	EnemyLuciaAtkDmg = (_enemy->getAtkDmg() * 8) - (_lucia->getAtkDef() * 5);

	SynergeDmg = 150;


	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		SOUNDMANAGER->play("Synerge", ASTAR->getEftVolume());
	}

}

void battleScene::render()
{
	PatBlt(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	
	IMAGEMANAGER->render("gameBack", getMemDC(), 768,0);


	_battle->render(_camera->getCameraX(), _camera->getCameraY());
	
	

	_astar->render(_camera->getCameraX(), _camera->getCameraY());
	_luciaAstar->render(_camera->getCameraX(), _camera->getCameraY());
	_enemyAstar->render(_camera->getCameraX(), _camera->getCameraY());

	drawTile();
	LuciadrawTile();
	//EnemydrawTile();

	ZORDER->render(_camera->getCameraX(),_camera->getCameraY());
	
	
	
	if (_enemy->getHit() == true)
	{
		if (luciaMgcPointX == enemyX && luciaMgcPointY == enemyY)
		{
			fire->frameRender(getMemDC(), fire->GetX() - _camera->getCameraX(), fire->GetY() - _camera->getCameraY(), fire->getFrameX(), 0);
		}

		if (alphMgcPointX == enemyX && alphMgcPointY == enemyY)
		{
		bomb->frameRender(getMemDC(), bomb->GetX() - _camera->getCameraX(), bomb->GetY() - _camera->getCameraY(), bomb->getFrameX(), 0);
		}
	}

	if (_alph->getHit() == true)
	{
		if (EnemyMgcPointX == alphX && EnemyMgcPointY == alphY)
		{
			puple->frameRender(getMemDC(), puple->GetX() - _camera->getCameraX(), puple->GetY() - _camera->getCameraY(), puple->getFrameX(), 0);
		}
	}

	if (_lucia->getHit() == true)
	{
		if (EnemyMgcPointX == luciaX && EnemyMgcPointY == luciaY)
		{
			puple->frameRender(getMemDC(), puple->GetX() - _camera->getCameraX(), puple->GetY() - _camera->getCameraY(), puple->getFrameX(), 0);
		}
	}

	if (tt == false)
	{
		_alph->StateRender();
		_lucia->StateRender();
		//_enemy->StateRender();

	}

	//===========================================================//

	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 0, 0));

	//sprintf_s(str, "루시아마법 : %d  루시아어택 : %d", luciaMgcDmg, luciaAtkDmg);
	//TextOut(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 50, 620, str, strlen(str));
	//
	//sprintf_s(str, "아이리스->루시아마법 :%d   공격 %d  아이리스->알프 마법:%d   공격 %d  ", EnemyLuciaMgcDmg, EnemyLuciaAtkDmg, EnemyAlphMgcDmg, EnemyAlphAtkDmg);
	//TextOut(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 50, 650, str, strlen(str));
	//
	//sprintf_s(str, "알프마법: %d  알프어택: %d", alphMgcDmg, alphAtkDmg);
	//TextOut(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 50, 680, str, strlen(str));

	//sprintf_s(str, "에너미어택 :%d  에너미어택 : %d  에너미마법 :%d  에너미마법 :%d", EnemyAtkPointX , EnemyAtkPointY, EnemyMgcPointX , EnemyMgcPointY);
	//TextOut(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 50, 650, str, strlen(str));
	//
	//sprintf_s(str, "에너미포인트x :%d 에너미포인트y :%d", EnemyPointX, EnemyPointY);
	//TextOut(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 50, 680, str, strlen(str));
	//
	//sprintf_s(str, "에너미x :%d 에너미y :%d", enemyX, enemyY);
	//TextOut(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 50, 710, str, strlen(str));
	//
	//sprintf_s(str, "좌표x %d  좌표y %d", _battle->getclassTile(MovePointX, MovePointY)->getPos(), _battle->getclassTile(MovePointX, MovePointY)->getPosY());
	//TextOut(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 50, 620, str, strlen(str));

	//sprintf_s(str, "카메라x %f  카메라y %f", _camera->getCameraX(), _camera->getCameraY());
	//TextOut(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 400, 600, str, strlen(str));
	//
	//sprintf_s(str, "알프x %f  알프y %f", _alph->getViewX(),_alph->getViewY());
	//TextOut(IMAGEMANAGER->findImage("Gameground")->getMemDC(),50,590, str, strlen(str));
//===========================================================================================================///


	//=====================게임그라운드 버퍼용===================================//
	IMAGEMANAGER->render("state", IMAGEMANAGER->findImage("Gameground")->getMemDC());
	IMAGEMANAGER->render("Notice", IMAGEMANAGER->findImage("Gameground")->getMemDC(), 0, 500);

	if (Camerachange == false)
	{
		IMAGEMANAGER->render("alphLog", IMAGEMANAGER->findImage("Gameground")->getMemDC());
		IMAGEMANAGER->findImage("Hpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), alphHp.left, alphHp.top, 0, 0, _alphHp, 26);
		IMAGEMANAGER->findImage("Mpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), alphMp.left, alphMp.top, 0, 0, _alph->getMaxMp(), 26);
		IMAGEMANAGER->findImage("Fpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), alphFp.left, alphFp.top, 0, 0, _alphFp, 26);
		IMAGEMANAGER->findImage("alphName")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 40, 160);
		IMAGEMANAGER->findImage("human")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 40, 240);
		alphState();
	}

	if (luciaChange == true)
	{
		IMAGEMANAGER->render("luciaLog", IMAGEMANAGER->findImage("Gameground")->getMemDC());
		IMAGEMANAGER->findImage("Hpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), luciaHp.left, luciaHp.top, 0, 0, _luciaHp, 26);
		IMAGEMANAGER->findImage("Mpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), luciaMp.left, luciaMp.top, 0, 0, _luciaMp, 26);
		IMAGEMANAGER->findImage("Fpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), luciaFp.left, luciaFp.top, 0, 0, _luciaFp, 26);
		IMAGEMANAGER->findImage("luciaName")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 40, 160);
		IMAGEMANAGER->findImage("witch")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 40, 240);
		luciaState();
	}

	if (Enemychange == true)
	{
		IMAGEMANAGER->render("irisLog", IMAGEMANAGER->findImage("Gameground")->getMemDC());
		IMAGEMANAGER->findImage("Hpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), EnemyHp.left, EnemyHp.top, 0, 0, _enemyHp, 26);
		IMAGEMANAGER->findImage("Mpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), EnemyMp.left, EnemyMp.top, 0, 0, _enemyMp, 26);
		IMAGEMANAGER->findImage("Fpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), EnemyFp.left, EnemyFp.top, 0, 0, _enemyFp, 26);
		IMAGEMANAGER->findImage("irisName")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 40, 160);
		IMAGEMANAGER->findImage("human")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 40, 240);
		enemyState();
	}

	HitDemege();


	if ((luciaMgcPointX == enemyX && luciaMgcPointY == enemyY) || (luciaAtkPointX == enemyX && luciaAtkPointY == enemyY) || (luciaSyPointX == enemyX && luciaSyPointY == enemyY))
	{
		enemyView();
	}

	if ((alphMgcPointX == enemyX && alphMgcPointY == enemyY) || (alphAtkPointX == enemyX && alphAtkPointY == enemyY) || (alphSyPointX == enemyX && alphSyPointY == enemyY))
	{
		enemyView();
	}

	if ((EnemyAtkPointX == alphX && EnemyAtkPointY == alphY) || (EnemyMgcPointX == alphX && EnemyMgcPointY == alphY) || (EnemySyPointX == alphX) && (EnemySyPointY == alphY ))
	{
		alphView();
	}
	if ((EnemyAtkPointX == luciaX && EnemyAtkPointY == luciaY) || (EnemyMgcPointX == luciaX && EnemyMgcPointY == luciaY) || (EnemySyPointX == luciaX)&& (EnemySyPointY == luciaY))
	{
		luciaView();
	}

	IMAGEMANAGER->render("edge", IMAGEMANAGER->findImage("Gameground")->getMemDC());

	SynergeSkill();

	IMAGEMANAGER->render("Gameground", getMemDC(), 0, 0, 0, 0, 768, 768);
}

void battleScene::drawRhombus(int left, int top)
{
	centerX = left + RADIUS_WIDTH;
	centerY = top + RADIUS_HEIGHT;

	p[0].x = centerX - _camera->getCameraX();
	p[0].y = centerY - RADIUS_HEIGHT - _camera->getCameraY();
	p[1].x = centerX + RADIUS_WIDTH - _camera->getCameraX();
	p[1].y = centerY - _camera->getCameraY();
	p[2].x = centerX - _camera->getCameraX();
	p[2].y = centerY + RADIUS_HEIGHT - _camera->getCameraY();
	p[3].x = centerX - RADIUS_WIDTH - _camera->getCameraX();
	p[3].y = centerY - _camera->getCameraY();

	Polygon(getMemDC(), p, 4);
}

void battleScene::astarMove()
{
	for (int i = 0; i < _battle->getTileY(); i++)
	{
		for (int j = 0; j < _battle->getTileX(); j++)
		{
			_currentIdx = { j,i };
			_battle->getclassTile(i, j)->settileXNum(_currentIdx.x);
			_battle->getclassTile(i, j)->settileYNum(_currentIdx.y);
		}
	}
	{
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			_vAStar = ASTAR->getLoad({ alphX,alphY }, { MovePointX,MovePointY }, _tileNum);
			alphmoving = true;
			_alph->setMoveMotion(true);
			_alph->setASrender(false);
		}

		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_luciaStar = ASTAR->getLoad({ luciaX,luciaY }, { LuciaPointX ,LuciaPointY }, _luciaTileNum);
			luciamoving = true;
			_lucia->setMoveMotion(true);
			_lucia->setASrender(false);
		}


		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			_EnemyStar = ASTAR->getLoad({ enemyX,enemyY }, { EnemyPointX,EnemyPointY }, _enemyTileNum);
			enemymoving = true;
			_enemy->setMoveMotion(true);
			_enemy->setASrender(false);
			
		}


		_astar->update();
		_astar->setMonsterIdx({ ((_battle->getclassTile(MovePointX,MovePointY)->gettileXNum())),((_battle->getclassTile(MovePointX,MovePointY)->gettileYNum())) });
		_astar->setPlayerIdx({ ((_battle->getclassTile(alphX, alphY)->gettileXNum())), ((_battle->getclassTile(alphX, alphY)->gettileYNum())) });
		_astar->setAstar();



		_luciaAstar->update();
		_luciaAstar->setMonsterIdx({ ((_battle->getclassTile(LuciaPointX,LuciaPointY)->gettileXNum())),((_battle->getclassTile(LuciaPointX,LuciaPointY)->gettileYNum())) });
		_luciaAstar->setPlayerIdx({ ((_battle->getclassTile(luciaX, luciaY)->gettileXNum())), ((_battle->getclassTile(luciaX, luciaY)->gettileYNum())) });
		_luciaAstar->setAstar();


		_enemyAstar->update();
		_enemyAstar->setMonsterIdx({ ((_battle->getclassTile(EnemyPointX,EnemyPointY)->gettileXNum())),((_battle->getclassTile(EnemyPointX,EnemyPointY)->gettileYNum())) });
		_enemyAstar->setPlayerIdx({ ((_battle->getclassTile(enemyX, enemyY)->gettileXNum())), ((_battle->getclassTile(enemyX, enemyY)->gettileYNum())) });
		_enemyAstar->setAstar();

		alphMove();
		luciaMove();
		EnemyMove();
	}
}

void battleScene::alphMove()
{
	//alph 이동//
	if (alphmoving == true)
	{
		MoveStay.x = _vAStar[_vAStar.size() - 2].x;
		MoveStay.y = _vAStar[_vAStar.size() - 2].y;

		alphStay.x = _vAStar[_vAStar.size() - 1].x;
		alphStay.y = _vAStar[_vAStar.size() - 1].y;


		angle = getAngle((abs(_battle->getclassTile(MoveStay.x, MoveStay.y)->getPos())),
			(abs(_battle->getclassTile(MoveStay.x, MoveStay.y)->getPosY())),
			_alph->getViewX(),
			_alph->getViewY());

		distance = getDistance((float)(abs(_battle->getclassTile(MoveStay.x, MoveStay.y)->getPos())),
			(float)(abs(_battle->getclassTile(MoveStay.x, MoveStay.y)->getPosY())),
			(abs(_alph->getViewX())),
			(abs(_alph->getViewY())));

		if (_vAStar.size() > 2)
		{
			if (distance < _alph->getSpeed())
			{
				_vAStar.erase(_vAStar.end() - 1);

			}
		}
		if (distance < _alph->getSpeed())
		{
			alphX = MoveStay.x;
			alphY = MoveStay.y;

			_alph->setviewX(_battle->getclassTile(alphX, alphY)->getPos());
			_alph->setviewY(_battle->getclassTile(alphX, alphY)->getPosY());

		}
		else
		{
			_alph->setviewX(_alph->getViewX() + -cosf(angle) * _alph->getSpeed());
			_alph->setviewY(_alph->getViewY() + sinf(angle) * _alph->getSpeed());
		}

		if (_alph->getViewX() == _battle->getclassTile(MovePointX, MovePointY)->getPos() &&
			_alph->getViewY() == _battle->getclassTile(MovePointX, MovePointY)->getPosY())
		{
			_alph->setMoveMotion(false);
			_alph->setmoveTile(false);
			_alph->setE(false);
			alphmoving = false;
		}

		if (_alph->getMoveMotion() == false)
		{
			if (MoveStay.x > alphStay.x)
			{
				_alph->setidleNum(0);
			}
			if (MoveStay.y > alphStay.y)
			{
				_alph->setidleNum(1);
			}
			if (MoveStay.x < alphStay.x)
			{
				_alph->setidleNum(3);
			}
			if (MoveStay.y < alphStay.y)
			{
				_alph->setidleNum(2);
			}
		}

		if (MoveStay.x > alphStay.x)
		{
			_alph->setmoveNum(1);
		}
		else if (MoveStay.y > alphStay.y)
		{
			_alph->setmoveNum(0);
		}
		else if (MoveStay.x < alphStay.x)
		{
			_alph->setmoveNum(3);
		}
		else if (MoveStay.y < alphStay.y)
		{
			_alph->setmoveNum(2);
		}
	}

	//알프 공격

	if (_alph->getisAttack() == true)
	{
		if (alphX < alphAtkPointX)
		{
			_alph->setAtkNumber(1);
			_alph->setidleNum(0);
		}
		if (alphX > alphAtkPointX)
		{
			_alph->setAtkNumber(3);
			_alph->setidleNum(3);
		}
		if (alphY < alphAtkPointY)
		{
			_alph->setAtkNumber(0);
			_alph->setidleNum(1);
		}
		if (alphY > alphAtkPointY)
		{
			_alph->setAtkNumber(2);
			_alph->setidleNum(2);
		}
	}
	
	//알프 마법
	if (_alph->getisMagic() == true)
	{
		if (alphX < alphMgcPointX)
		{
			_alph->setMgcNumber(1);
			_alph->setidleNum(0);
		}
		if (alphX > alphMgcPointX)
		{
			_alph->setMgcNumber(3);
			_alph->setidleNum(3);
		}
		if (alphY < alphMgcPointY)
		{
			_alph->setMgcNumber(0);
			_alph->setidleNum(1);
		}
		if (alphY > alphMgcPointY)
		{
			_alph->setMgcNumber(2);
			_alph->setidleNum(2);
		}
	}

}

void battleScene::luciaMove()
{

	//lucia 이동//

	if (luciamoving == true)
	{
		MoveLucia.x = _luciaStar[_luciaStar.size() - 2].x;
		MoveLucia.y = _luciaStar[_luciaStar.size() - 2].y;

		luciaStay.x = _luciaStar[_luciaStar.size() - 1].x;
		luciaStay.y = _luciaStar[_luciaStar.size() - 1].y;


		Luangle = getAngle((abs(_battle->getclassTile(MoveLucia.x, MoveLucia.y)->getPos())),
			(abs(_battle->getclassTile(MoveLucia.x, MoveLucia.y)->getPosY())),
			_lucia->getViewX(),
			_lucia->getViewY());

		Ludistance = getDistance((float)(abs(_battle->getclassTile(MoveLucia.x, MoveLucia.y)->getPos())),
			(float)(abs(_battle->getclassTile(MoveLucia.x, MoveLucia.y)->getPosY())),
			(abs(_lucia->getViewX())),
			(abs(_lucia->getViewY())));

		if (_luciaStar.size() > 2)
		{
			if (Ludistance < _lucia->getSpeed())
			{
				_luciaStar.erase(_luciaStar.end() - 1);

			}
		}
		if (Ludistance < _lucia->getSpeed())
		{
			luciaX = MoveLucia.x;
			luciaY = MoveLucia.y;

			_lucia->setviewX(_battle->getclassTile(luciaX, luciaY)->getPos());
			_lucia->setviewY(_battle->getclassTile(luciaX, luciaY)->getPosY());

		}
		else
		{
			_lucia->setviewX(_lucia->getViewX() + -cosf(Luangle) * _lucia->getSpeed());
			_lucia->setviewY(_lucia->getViewY() + sinf(Luangle) * _lucia->getSpeed());
		}

		if (_lucia->getViewX() == _battle->getclassTile(LuciaPointX, LuciaPointY)->getPos() &&
			_lucia->getViewY() == _battle->getclassTile(LuciaPointX, LuciaPointY)->getPosY())
		{
			_lucia->setMoveMotion(false);
			_lucia->setmoveTile(false);
			_lucia->setMovePoint(false);
			luciamoving = false;
		}

		if (_lucia->getMoveMotion() == false)
		{
			if (MoveLucia.x > luciaStay.x)
			{
				_lucia->setidleNumber(1);
			}
			if (MoveLucia.y > luciaStay.y)
			{
				_lucia->setidleNumber(0);
			}
			if (MoveLucia.x < luciaStay.x)
			{
				_lucia->setidleNumber(2);
			}
			if (MoveLucia.y < luciaStay.y)
			{
				_lucia->setidleNumber(3);
			}
		}

		if (MoveLucia.x > luciaStay.x)
		{
			_lucia->setmoveNumber(1);
		}
		else if (MoveLucia.y > luciaStay.y)
		{
			_lucia->setmoveNumber(0);
		}
		else if (MoveLucia.x < luciaStay.x)
		{
			_lucia->setmoveNumber(2);
		}
		else if (MoveLucia.y < luciaStay.y)
		{
			_lucia->setmoveNumber(3);
		}
	}

	//루시아 공격
	if (_lucia->getisAttack() == true)
	{
		if (luciaX < luciaAtkPointX)
		{
			_lucia->setAtkNumber(1);
			_lucia->setidleNum(1);
		}
		if (luciaX > luciaAtkPointX)
		{
			_lucia->setAtkNumber(3);
			_lucia->setidleNum(2);
		}
		if (luciaY < luciaAtkPointY)
		{
			_lucia->setAtkNumber(0);
			_lucia->setidleNum(0);
		}
		if (luciaY > luciaAtkPointY)
		{
			_lucia->setAtkNumber(2);
			_lucia->setidleNum(3);
		}
	}

	//루시아 마법
	if (_lucia->getisMagic() == true)
	{
		if (luciaX < luciaMgcPointX)
		{
			_lucia->setMgcNumber(1);
			_lucia->setidleNum(1);
		}
		if (luciaX > luciaMgcPointX)
		{
			_lucia->setMgcNumber(3);
			_lucia->setidleNum(2);
		}
		if (luciaY < luciaMgcPointY)
		{
			_lucia->setMgcNumber(0);
			_lucia->setidleNum(0);
		}
		if (luciaY > luciaMgcPointY)
		{
			_lucia->setMgcNumber(2);
			_lucia->setidleNum(3);
		}
	}


}

void battleScene::EnemyMove()
{
	if (enemymoving == true)
	{
		MoveEnemy.x = _EnemyStar[_EnemyStar.size() - 2].x;
		MoveEnemy.y = _EnemyStar[_EnemyStar.size() - 2].y;

		EnemyStay.x = _EnemyStar[_EnemyStar.size() - 1].x;
		EnemyStay.y = _EnemyStar[_EnemyStar.size() - 1].y;


		Enemyangle = getAngle((abs(_battle->getclassTile(MoveEnemy.x, MoveEnemy.y)->getPos())),
			(abs(_battle->getclassTile(MoveEnemy.x, MoveEnemy.y)->getPosY())),
			_enemy->getViewX(),
			_enemy->getViewY());

		EnemyDistance = getDistance((float)(abs(_battle->getclassTile(MoveEnemy.x, MoveEnemy.y)->getPos())),
			(float)(abs(_battle->getclassTile(MoveEnemy.x, MoveEnemy.y)->getPosY())),
			(abs(_enemy->getViewX())),
			(abs(_enemy->getViewY())));

		if (_EnemyStar.size() > 2)
		{
			if (EnemyDistance < _enemy->getSpeed())
			{
				_EnemyStar.erase(_EnemyStar.end() - 1);

			}
		}
		if (EnemyDistance < _enemy->getSpeed())
		{
			enemyX = MoveEnemy.x;
			enemyY = MoveEnemy.y;

			_enemy->setviewX(_battle->getclassTile(enemyX, enemyY)->getPos());
			_enemy->setviewY(_battle->getclassTile(enemyX, enemyY)->getPosY());

		}
		else
		{
			_enemy->setviewX(_enemy->getViewX() + -cosf(Enemyangle) * _enemy->getSpeed());
			_enemy->setviewY(_enemy->getViewY() + sinf(Enemyangle) * _enemy->getSpeed());
		}

		if (_enemy->getViewX() == _battle->getclassTile(EnemyPointX, EnemyPointY)->getPos() &&
			_enemy->getViewY() == _battle->getclassTile(EnemyPointX, EnemyPointY)->getPosY())
		{
			_enemy->setMoveMotion(false);
			_enemy->setmoveTile(false);
			_enemy->setMovePoint(false);
			enemymoving = false;
		}

		if (_enemy->getMoveMotion() == false)
		{
			if (MoveEnemy.x > EnemyStay.x)
			{
				_enemy->setidleNum(0);
			}
			if (MoveEnemy.y > EnemyStay.y)
			{
				_enemy->setidleNum(1);
			}
			if (MoveEnemy.x < EnemyStay.x)
			{
				_enemy->setidleNum(3);
			}
			if (MoveEnemy.y < EnemyStay.y)
			{
				_enemy->setidleNum(2);
			}
		}

		if (MoveEnemy.x > EnemyStay.x)
		{
			_enemy->setmoveNum(1);
		}
		else if (MoveEnemy.y > EnemyStay.y)
		{
			_enemy->setmoveNum(0);
		}
		else if (MoveEnemy.x < EnemyStay.x)
		{
			_enemy->setmoveNum(3);
		}
		else if (MoveEnemy.y < EnemyStay.y)
		{
			_enemy->setmoveNum(2);
		}
	}
	//에너미 공격
	if (_enemy->getisAttack() == true)
	{
		if (enemyX < EnemyAtkPointX)
		{
			_enemy->setAtkNumber(1);
			_enemy->setidleNum(0);
		}
		if (enemyX > EnemyAtkPointX)
		{
			_enemy->setAtkNumber(3);
			_enemy->setidleNum(3);
		}
		if (enemyY < EnemyAtkPointY)
		{
			_enemy->setAtkNumber(0);
			_enemy->setidleNum(1);
		}
		if (enemyY > EnemyAtkPointY)
		{
			_enemy->setAtkNumber(2);
			_enemy->setidleNum(2);
		}
	}

	//에너미 마법
	if (_enemy->getisMagic() == true)
	{
		if (enemyX < EnemyMgcPointX)
		{
			_enemy->setMgcNumber(1);
			_enemy->setidleNum(0);
		}
		if (enemyX > EnemyMgcPointX)
		{
			_enemy->setMgcNumber(3);
			_enemy->setidleNum(3);
		}
		if (enemyY < EnemyMgcPointY)
		{
			_enemy->setMgcNumber(0);
			_enemy->setidleNum(1);
		}
		if (enemyY > EnemyMgcPointY)
		{
			_enemy->setMgcNumber(2);
			_enemy->setidleNum(2);
		}
	}
}

void battleScene::PlayerCollision()
{
	////알프
	//{
	//	//마법 공격
	//	if (alphMgcPointX == luciaX && alphMgcPointY == luciaY)
	//	{
	//		if (_alph->getMgcRange() == false && _alph->getAtkRange() == false && _alph->getmoveTile() == false)
	//		{
	//			_lucia->setHit(true);
	//
	//			bomb->SetX(_battle->getclassTile(alphMgcPointX, alphMgcPointY)->getPos() - 80);
	//			bomb->SetY(_battle->getclassTile(alphMgcPointX, alphMgcPointY)->getPosY() - 90);
	//
	//			if (_lucia->getHit() == true)
	//			{
	//				bombCount++;
	//				Hitcount++;
	//				if (bombCount % 1 == 0)
	//				{
	//					bombIndex++;
	//					bomb->SetFrameX(bombIndex);
	//
	//					if (bombIndex > 4) bombIndex = 0;
	//
	//					bombCount = 0;
	//				}		
	//				if (Hitcount < 2)
	//				{
	//					// Fp
	//					if (_alphFp <= 242)
	//					{
	//						_alphFp += 68;
	//					}
	//					if (_alphFp >= 242)
	//					{
	//						_alphFp = 242;
	//					}
	//					// Mp
	//				
	//					_alphMp -= 34;
	//					_alph->setMaxMp(_alph->getMaxMp() - 34);
	//					_luciaHp -= alphMgcDmg;
	//					_lucia->setCurrentHp(_lucia->getCurrentHp() - alphMgcDmg);
	//				}
	//			}
	//
	//			if (alphY < luciaY)
	//			{
	//				_lucia->setHitNumber(2);
	//				_lucia->setidleNum(3);
	//			}
	//
	//			if (alphY > luciaY)
	//			{
	//				_lucia->setHitNumber(0);
	//				_lucia->setidleNum(0);
	//			}
	//
	//			if (alphX > luciaX)
	//			{
	//				_lucia->setHitNumber(1);
	//				_lucia->setidleNum(1);
	//			}
	//
	//			if (alphX < luciaX)
	//			{
	//				_lucia->setHitNumber(3);
	//				_lucia->setidleNum(2);
	//			}
	//		}
	//	}
	//	
	//
	//	//일반 공격
	//	 if (alphAtkPointX == luciaX && alphAtkPointY == luciaY)
	//	{
	//		if (_alph->getMgcRange() == false && _alph->getAtkRange() == false && _alph->getmoveTile() == false)
	//		{
	//			_lucia->setHit(true);
	//
	//			if (_lucia->getHit() == true)
	//			{
	//				Hitcount++;
	//				
	//				if (Hitcount < 2)
	//				{
	//					if (_alphFp <= 242)
	//					{
	//						_alphFp += 34;
	//					}
	//					if (_alphFp >= 242)
	//					{
	//						_alphFp = 242;
	//					}
	//					_luciaHp -= alphAtkDmg;
	//					_lucia->setCurrentHp(_lucia->getCurrentHp() - alphAtkDmg);
	//				}
	//			}
	//
	//			if (alphY < luciaY)
	//			{
	//				_lucia->setHitNumber(2);
	//				_lucia->setidleNum(3);
	//			}
	//
	//			if (alphY > luciaY)
	//			{
	//				_lucia->setHitNumber(0);
	//				_lucia->setidleNum(0);
	//			}
	//
	//			if (alphX > luciaX)
	//			{
	//				_lucia->setHitNumber(1);
	//				_lucia->setidleNum(1);
	//			}
	//
	//			if (alphX < luciaX)
	//			{
	//				_lucia->setHitNumber(3);
	//				_lucia->setidleNum(2);
	//			}
	//		}
	//	}
	//}
	//if (_lucia->getHit() == false)
	//{
	//	Hitcount = 0;
	//}
//==//====================== 루시아 =============================//
	//
	//if (luciaMgcPointX == alphX && luciaMgcPointY == alphY)
	//{
	//	if (_lucia->getMgcRange() == false && _lucia->getAtkRange() == false && _lucia->getmoveTile() == false)
	//	{
	//		_alph->setHit(true);
	//
	//		fire->SetX(_battle->getclassTile(luciaMgcPointX, luciaMgcPointY)->getPos() - 98);
	//		fire->SetY(_battle->getclassTile(luciaMgcPointX, luciaMgcPointY)->getPosY() - 64);
	//
	//		if (_alph->getHit() == true)
	//		{
	//			imageCount++;
	//			luciaHitCount++;
	//			if (imageCount % 1 == 0)
	//			{
	//				imageIndex++;
	//				fire->SetFrameX(imageIndex);
	//
	//				if (imageIndex > 22) imageIndex = 1;
	//
	//				imageCount = 0;
	//
	//				if (luciaHitCount < 2)
	//				{
	//					_alphHp -= luciaMgcDmg;
	//					_alph->setCurrentHp(_alph->getCurrentHp() - luciaMgcDmg);
	//				}
	//			}
	//		}
	//
	//		if (alphY < luciaY)
	//		{
	//			_alph->setHitNumber(0);
	//			_alph->setidleNum(1);
	//		}
	//		if (alphY > luciaY)
	//		{
	//			_alph->setHitNumber(1);
	//			_alph->setidleNum(2);
	//		}
	//		if (alphX > luciaX)
	//		{
	//			_alph->setHitNumber(3);
	//			_alph->setidleNum(3);
	//		}
	//		if (alphX < luciaX)
	//		{
	//			_alph->setHitNumber(2);
	//			_alph->setidleNum(0);
	//		}
	//	}
	//}
	////일반 공격
	//else if (luciaAtkPointX == alphX && luciaAtkPointY == alphY)
	//{
	//	if (_lucia->getMgcRange() == false && _lucia->getAtkRange() == false && _lucia->getmoveTile() == false)
	//	{
	//		_alph->setHit(true);
	//
	//
	//		if (_alph->getHit() == true)
	//		{
	//			
	//			luciaHitCount++;
	//			
	//				if (luciaHitCount < 2)
	//				{
	//					_alphHp -= luciaAtkDmg;
	//					_alph->setCurrentHp(_alph->getCurrentHp() - luciaAtkDmg);
	//				}
	//			
	//		}
	//		if (alphY < luciaY)
	//		{
	//			_alph->setHitNumber(0);
	//			_alph->setidleNum(1);
	//		}
	//		if (alphY > luciaY)
	//		{
	//			_alph->setHitNumber(1);
	//			_alph->setidleNum(2);
	//		}
	//		if (alphX > luciaX)
	//		{
	//			_alph->setHitNumber(3);
	//			_alph->setidleNum(3);
	//		}
	//		if (alphX < luciaX)
	//		{
	//			_alph->setHitNumber(2);
	//			_alph->setidleNum(0);
	//		}
	//	}
	//}
	//if (_alph->getHit() == false)
	//{
	//	luciaHitCount = 0;
	//}

//====위에 노터치======//
	//알프
	{
		//마법 공격
		if (alphMgcPointX == enemyX && alphMgcPointY == enemyY)
		{
			if (_alph->getMgcRange() == false && _alph->getAtkRange() == false && _alph->getmoveTile() == false)
			{
				_enemy->setHit(true);

				bomb->SetX(_enemy->getViewX() - 80 );
				bomb->SetY(_enemy->getViewY() - 90 - _enemy->getZlevel());

				if (_enemy->getHit() == true)
				{
					bombCount++;
					Hitcount++;
					if (bombCount % 1 == 0)
					{
						bombIndex++;
						bomb->SetFrameX(bombIndex);

						if (bombIndex > 4) bombIndex = 0;

						bombCount = 0;
					}
					if (Hitcount < 2)
					{
						// Fp
						if (_alphFp <= 242)
						{
							_alphFp += 68;
						}
						if (_alphFp >= 242)
						{
							_alphFp = 242;
						}
						// Mp

						_alphMp -= 34;
						_alph->setMaxMp(_alph->getMaxMp() - 34);
						_enemyHp -= alphMgcDmg;
						_enemy->setCurrentHp(_enemy->getCurrentHp() - alphMgcDmg);
					}
				}

				if (alphY < enemyY)
				{
					_enemy->setHitNumber(2);
					_enemy->setidleNum(2);
				}

				if (alphY > enemyY)
				{
					_enemy->setHitNumber(0);
					_enemy->setidleNum(1);
				}

				if (alphX > enemyX)
				{
					_enemy->setHitNumber(1);
					_enemy->setidleNum(0);
				}

				if (alphX < enemyX)
				{
					_enemy->setHitNumber(3);
					_enemy->setidleNum(3);
				}
			}
		}


		//일반 공격
		if (alphAtkPointX == enemyX && alphAtkPointY == enemyY)
		{
			if (_alph->getMgcRange() == false && _alph->getAtkRange() == false && _alph->getmoveTile() == false)
			{
				_enemy->setHit(true);

				if (_enemy->getHit() == true)
				{
					Hitcount++;

					if (Hitcount < 2)
					{
						if (_alphFp <= 242)
						{
							_alphFp += 34;
						}
						if (_alphFp >= 242)
						{
							_alphFp = 242;
						}
						_enemyHp -= alphAtkDmg;
						_enemy->setCurrentHp(_enemy->getCurrentHp() - alphAtkDmg);
					}
				}

				if (alphY < enemyY)
				{
					_enemy->setHitNumber(2);
					_enemy->setidleNum(2);
				}

				if (alphY > enemyY)
				{
					_enemy->setHitNumber(0);
					_enemy->setidleNum(1);
				}

				if (alphX > enemyX)
				{
					_enemy->setHitNumber(1);
					_enemy->setidleNum(0);
				}

				if (alphX < enemyX)
				{
					_enemy->setHitNumber(3);
					_enemy->setidleNum(3);
				}
			}
		}
	}
	if (_enemy->getHit() == false)
	{
		Hitcount = 0;
	}
	//======================== 루시아 =============================//

	if (luciaMgcPointX == enemyX && luciaMgcPointY == enemyY)
	{
		if (_lucia->getMgcRange() == false && _lucia->getAtkRange() == false && _lucia->getmoveTile() == false)
		{
			_enemy->setHit(true);

			fire->SetX(_battle->getclassTile(luciaMgcPointX, luciaMgcPointY)->getPos() - 98);
			fire->SetY(_battle->getclassTile(luciaMgcPointX, luciaMgcPointY)->getPosY() - 64 - _enemy->getZlevel());

			if (_enemy->getHit() == true)
			{
				imageCount++;
				luciaHitCount++;

				if (imageCount % 1 == 0)
				{
					imageIndex++;
					fire->SetFrameX(imageIndex);

					if (imageIndex > 22) imageIndex = 1;

					imageCount = 0;

				}
				if (luciaHitCount < 2)
				{
					_enemyHp -= luciaMgcDmg;
					_enemy->setCurrentHp(_enemy->getCurrentHp() - luciaMgcDmg);
				}
			}

			if (enemyY > luciaY)
			{
				_enemy->setHitNumber(2);
				_enemy->setidleNum(2);
			}
			if (enemyY < luciaY)
			{
				_enemy->setHitNumber(0);
				_enemy->setidleNum(1);
			}
			if (enemyX < luciaX)
			{
				_enemy->setHitNumber(1);
				_enemy->setidleNum(0);
			}
			if (enemyX > luciaX)
			{
				_enemy->setHitNumber(3);
				_enemy->setidleNum(3);
			}
		}
	}
	//일반 공격
	if (luciaAtkPointX == enemyX && luciaAtkPointY == enemyY)
	{
		if (_lucia->getMgcRange() == false && _lucia->getAtkRange() == false && _lucia->getmoveTile() == false)
		{
			_enemy->setHit(true);

			if (_enemy->getHit() == true)
			{

				luciaHitCount++;

				if (luciaHitCount < 2)
				{
					_enemyHp -= luciaAtkDmg;
					_enemy->setCurrentHp(_enemy->getCurrentHp() - luciaAtkDmg);
				}

			}
			if (enemyY > luciaY)
			{
				_enemy->setHitNumber(2);
				_enemy->setidleNum(2);
			}
			if (enemyY < luciaY)
			{
				_enemy->setHitNumber(0);
				_enemy->setidleNum(1);
			}
			if (enemyX < luciaX)
			{
				_enemy->setHitNumber(1);
				_enemy->setidleNum(0);
			}
			if (enemyX > luciaX)
			{
				_enemy->setHitNumber(3);
				_enemy->setidleNum(3);
			}
		}
	}
	if (_enemy->getHit() == false)
	{
		luciaHitCount = 0;
	}

	//===================================== 에너미 -> 루시아 ====================================//
	
	if (EnemyMgcPointX == luciaX && EnemyMgcPointY == luciaY)
	{
		if (_enemy->getMgcRange() == false && _enemy->getAtkRange() == false && _enemy->getmoveTile() == false)
		{
			_lucia->setHit(true);

			puple->SetX(_battle->getclassTile(EnemyMgcPointX, EnemyMgcPointY)->getPos() - 55);
			puple->SetY(_battle->getclassTile(EnemyMgcPointX, EnemyMgcPointY)->getPosY() - 64 - _lucia->getZlevel());

			if (_lucia->getHit() == true)
			{
				pupleCount++;

				if (pupleCount % 1 == 0)
				{
					pupleIndex++;
					puple->SetFrameX(pupleIndex);

					if (pupleIndex > 6) pupleIndex = 1;

					pupleCount = 0;

					enemyHitCount++;

					if (enemyHitCount < 2)
					{
						_luciaHp -= EnemyLuciaMgcDmg;
						_lucia->setCurrentHp(_lucia->getCurrentHp() - EnemyLuciaMgcDmg);
					}
				}

				if (enemyY > luciaY)
				{
					_lucia->setHitNumber(0);
					_lucia->setidleNum(0);
				}
				if (enemyY < luciaY)
				{
					_lucia->setHitNumber(2);
					_lucia->setidleNum(3);
				}
				if (enemyX < luciaX)
				{
					_lucia->setHitNumber(3);
					_lucia->setidleNum(2);
				}
				if (enemyX > luciaX)
				{
					_lucia->setHitNumber(1);
					_lucia->setidleNum(1);
				}
			}
		}
	}
		//일반 공격
	if (EnemyAtkPointX == luciaX && EnemyAtkPointY == luciaY)
	{
		if (_enemy->getMgcRange() == false && _enemy->getAtkRange() == false && _enemy->getmoveTile() == false)
		{
			_lucia->setHit(true);

			if (_lucia->getHit() == true)
			{
				enemyHitCount++;

				if (enemyHitCount < 2)
				{
					_luciaHp -= EnemyLuciaAtkDmg;
					_lucia->setCurrentHp(_lucia->getCurrentHp() - EnemyLuciaAtkDmg);
				}

			}
			if (enemyY > luciaY)
			{
				_lucia->setHitNumber(0);
				_lucia->setidleNum(0);
			}
			if (enemyY < luciaY)
			{
				_lucia->setHitNumber(2);
				_lucia->setidleNum(3);
			}
			if (enemyX < luciaX)
			{
				_lucia->setHitNumber(3);
				_lucia->setidleNum(2);
			}
			if (enemyX > luciaX)
			{
				_lucia->setHitNumber(1);
				_lucia->setidleNum(1);
			}
		}
	}
	if (_lucia->getHit() == false)
	{
		enemyHitCount = 0;
	}



		//============================= 에너미 -> 알프-=============================//
		if (EnemyMgcPointX == alphX && EnemyMgcPointY == alphY)
		{
			if (_enemy->getMgcRange() == false && _enemy->getAtkRange() == false && _enemy->getmoveTile() == false)
			{
				_alph->setHit(true);

				puple->SetX(_battle->getclassTile(EnemyMgcPointX, EnemyMgcPointY)->getPos() - 55);
				puple->SetY(_battle->getclassTile(EnemyMgcPointX, EnemyMgcPointY)->getPosY() - 64 - _alph->getZlevel());

				if (_alph->getHit() == true)
				{
					pupleCount2++;

					if (pupleCount2 % 1 == 0)
					{
						pupleIndex2++;
						puple->SetFrameX(pupleIndex2);

						if (pupleIndex2 > 6) pupleIndex2 = 1;

						pupleCount2 = 0;

						enemyHitCount2++;

						if (enemyHitCount2 < 2)
						{
							_alphHp -= EnemyAlphMgcDmg;
							_alph->setCurrentHp(_alph->getCurrentHp() - EnemyAlphMgcDmg);
						}
					}
				}

				if (enemyY > alphY)
				{
					_alph->setHitNumber(0);
					_alph->setidleNum(1);
				}
				if (enemyY < alphY)
				{
					_alph->setHitNumber(2);
					_alph->setidleNum(2);
				}
				if (enemyX < alphX)
				{
					_alph->setHitNumber(3);
					_alph->setidleNum(3);
				}
				if (enemyX > alphX)
				{
					_alph->setHitNumber(1);
					_alph->setidleNum(0);
				}
			}
		}
		//일반 공격
		if (EnemyAtkPointX == alphX && EnemyAtkPointY == alphY)
		{
			if (_enemy->getMgcRange() == false && _enemy->getAtkRange() == false && _enemy->getmoveTile() == false)
			{
				_alph->setHit(true);

				if (_alph->getHit() == true)
				{
					enemyHitCount2++;

					if (enemyHitCount2 < 2)
					{
						_alphHp -= EnemyAlphAtkDmg;
						_alph->setCurrentHp(_alph->getCurrentHp() - EnemyAlphAtkDmg);
					}

				}
				if (enemyY > alphY)
				{
					_alph->setHitNumber(0);
					_alph->setidleNum(1);
				}
				if (enemyY < alphY)
				{
					_alph->setHitNumber(2);
					_alph->setidleNum(2);
				}
				if (enemyX < alphX)
				{
					_alph->setHitNumber(3);
					_alph->setidleNum(3);
				}
				if (enemyX > alphX)
				{
					_alph->setHitNumber(1);
					_alph->setidleNum(0);
				}
			}
		}
		if (_alph->getHit() == false)
		{
			enemyHitCount2 = 0;
		}
	
}

void battleScene::drawTile()
{
	if (_alph->getE() == true)
	{
		if (_battle->getclassTile(MovePointX, MovePointY)->getZlevel() == 0)
		{
			left = _battle->getclassTile(MovePointX, MovePointY)->getPos() - 64;
			top = _battle->getclassTile(MovePointX, MovePointY)->getPosY() - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}

		else if (_battle->getclassTile(MovePointX, MovePointY)->getZlevel() > 0)
		{
			left = _battle->getclassTile(MovePointX, MovePointY)->getPos() - 64;
			top = _battle->getclassTile(MovePointX, MovePointY)->getPosY() - (_battle->getclassTile(MovePointX, MovePointY)->getZlevel() * 32) - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}
	}
	if (_alph->getF() == true)
	{
		if (_battle->getclassTile(alphAtkPointX, alphAtkPointY)->getZlevel() == 0)
		{
			left = _battle->getclassTile(alphAtkPointX, alphAtkPointY)->getPos() - 64;
			top = _battle->getclassTile(alphAtkPointX, alphAtkPointY)->getPosY() - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}

		else if (_battle->getclassTile(alphAtkPointX, alphAtkPointY)->getZlevel() > 0)
		{
			left = _battle->getclassTile(alphAtkPointX, alphAtkPointY)->getPos() - 64;
			top = _battle->getclassTile(alphAtkPointX, alphAtkPointY)->getPosY() - (_battle->getclassTile(alphAtkPointX, alphAtkPointY)->getZlevel() * 32) - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}
	}

	if (_alph->getisMgcPoint() == true)
	{
		if (_battle->getclassTile(alphMgcPointX, alphMgcPointY)->getZlevel() == 0)
		{
			left = _battle->getclassTile(alphMgcPointX, alphMgcPointY)->getPos() - 64;
			top = _battle->getclassTile(alphMgcPointX, alphMgcPointY)->getPosY() - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(255,125 , 125));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}

		else if (_battle->getclassTile(alphMgcPointX, alphMgcPointY)->getZlevel() > 0)
		{
			left = _battle->getclassTile(alphMgcPointX, alphMgcPointY)->getPos() - 64;
			top = _battle->getclassTile(alphMgcPointX, alphMgcPointY)->getPosY() - (_battle->getclassTile(alphMgcPointX, alphMgcPointY)->getZlevel() * 32) - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(255, 125, 125));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}
	}
	
	if (_alph->getsynergeCheck() == true)
	{
		if (_battle->getclassTile(alphSyPointX, alphSyPointY)->getZlevel() == 0)
		{
			left = _battle->getclassTile(alphSyPointX, alphSyPointY)->getPos() - 64;
			top = _battle->getclassTile(alphSyPointX, alphSyPointY)->getPosY() - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(255, 125, 125));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}

		else if (_battle->getclassTile(alphSyPointX, alphSyPointY)->getZlevel() > 0)
		{
			left = _battle->getclassTile(alphSyPointX, alphSyPointY)->getPos() - 64;
			top = _battle->getclassTile(alphSyPointX, alphSyPointY)->getPosY() - (_battle->getclassTile(alphSyPointX, alphSyPointY)->getZlevel() * 32) - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(255, 125, 125));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}
	}
}

void battleScene::LuciadrawTile()
{
	if (_lucia->getMovePoint() == true)
	{
		if (_battle->getclassTile(LuciaPointX, LuciaPointY)->getZlevel() == 0)
		{
			left = _battle->getclassTile(LuciaPointX, LuciaPointY)->getPos() - 64;
			top = _battle->getclassTile(LuciaPointX, LuciaPointY)->getPosY() - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}

		else if (_battle->getclassTile(LuciaPointX, LuciaPointY)->getZlevel() > 0)
		{
			left = _battle->getclassTile(LuciaPointX, LuciaPointY)->getPos() - 64;
			top = _battle->getclassTile(LuciaPointX, LuciaPointY)->getPosY() - (_battle->getclassTile(LuciaPointX, LuciaPointY)->getZlevel() * 32) - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}
	}

	if (_lucia->getAtkPoint() == true)
	{
		if (_battle->getclassTile(luciaAtkPointX, luciaAtkPointY)->getZlevel() == 0)
		{
			left = _battle->getclassTile(luciaAtkPointX, luciaAtkPointY)->getPos() - 64;
			top = _battle->getclassTile(luciaAtkPointX, luciaAtkPointY)->getPosY() - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(125, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}

		else if (_battle->getclassTile(luciaAtkPointX, luciaAtkPointY)->getZlevel() > 0)
		{
			left = _battle->getclassTile(luciaAtkPointX, luciaAtkPointY)->getPos() - 64;
			top = _battle->getclassTile(luciaAtkPointX, luciaAtkPointY)->getPosY() - (_battle->getclassTile(luciaAtkPointX, luciaAtkPointY)->getZlevel() * 32) - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(125, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}
	}

	if (_lucia->getMgcPoint() == true)
	{
		if (_battle->getclassTile(luciaMgcPointX, luciaMgcPointY)->getZlevel() == 0)
		{
			left = _battle->getclassTile(luciaMgcPointX, luciaMgcPointY)->getPos() - 64;
			top = _battle->getclassTile(luciaMgcPointX, luciaMgcPointY)->getPosY() - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(125, 0, 125));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}

		else if (_battle->getclassTile(luciaMgcPointX, luciaMgcPointY)->getZlevel() > 0)
		{
			left = _battle->getclassTile(luciaMgcPointX, luciaMgcPointY)->getPos() - 64;
			top = _battle->getclassTile(luciaMgcPointX, luciaMgcPointY)->getPosY() - (_battle->getclassTile(luciaMgcPointX, luciaMgcPointY)->getZlevel() * 32) - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(125, 0, 125));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}
	}

	if (_lucia->getsynergeCheck() == true)
	{
		if (_battle->getclassTile(luciaSyPointX, luciaSyPointY)->getZlevel() == 0)
		{
			left = _battle->getclassTile(luciaSyPointX, luciaSyPointY)->getPos() - 64;
			top = _battle->getclassTile(luciaSyPointX, luciaSyPointY)->getPosY() - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(125, 0, 125));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}

		else if (_battle->getclassTile(luciaSyPointX, luciaSyPointY)->getZlevel() > 0)
		{
			left = _battle->getclassTile(luciaSyPointX, luciaSyPointY)->getPos() - 64;
			top = _battle->getclassTile(luciaSyPointX, luciaSyPointY)->getPosY() - (_battle->getclassTile(luciaSyPointX, luciaSyPointY)->getZlevel() * 32) - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(125, 0, 125));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}
	}
}

void battleScene::EnemydrawTile()
{
	if (_enemy->getMovePoint() == true)
	{
		if (_battle->getclassTile(EnemyPointX, EnemyPointY)->getZlevel() == 0)
		{
			left = _battle->getclassTile(EnemyPointX, EnemyPointY)->getPos() - 64;
			top = _battle->getclassTile(EnemyPointX, EnemyPointY)->getPosY() - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}

		else if (_battle->getclassTile(EnemyPointX, EnemyPointY)->getZlevel() > 0)
		{
			left = _battle->getclassTile(EnemyPointX, EnemyPointY)->getPos() - 64;
			top = _battle->getclassTile(EnemyPointX, EnemyPointY)->getPosY() - (_battle->getclassTile(EnemyPointX, EnemyPointY)->getZlevel() * 32) - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}
	}

	if (_enemy->getAtkPoint() == true)
	{
		if (_battle->getclassTile(EnemyAtkPointX, EnemyAtkPointY)->getZlevel() == 0)
		{
			left = _battle->getclassTile(EnemyAtkPointX, EnemyAtkPointY)->getPos() - 64;
			top = _battle->getclassTile(EnemyAtkPointX, EnemyAtkPointY)->getPosY() - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(125, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}

		else if (_battle->getclassTile(EnemyAtkPointX, EnemyAtkPointY)->getZlevel() > 0)
		{
			left = _battle->getclassTile(EnemyAtkPointX, EnemyAtkPointY)->getPos() - 64;
			top = _battle->getclassTile(EnemyAtkPointX, EnemyAtkPointY)->getPosY() - (_battle->getclassTile(EnemyAtkPointX, EnemyAtkPointY)->getZlevel() * 32) - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(125, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}
	}

	if (_enemy->getMgcPoint() == true)
	{
		if (_battle->getclassTile(EnemyMgcPointX, EnemyMgcPointY)->getZlevel() == 0)
		{
			left = _battle->getclassTile(EnemyMgcPointX, EnemyMgcPointY)->getPos() - 64;
			top = _battle->getclassTile(EnemyMgcPointX, EnemyMgcPointY)->getPosY() - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(125, 0, 125));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}

		else if (_battle->getclassTile(EnemyMgcPointX, EnemyMgcPointY)->getZlevel() > 0)
		{
			left = _battle->getclassTile(EnemyMgcPointX, EnemyMgcPointY)->getPos() - 64;
			top = _battle->getclassTile(EnemyMgcPointX, EnemyMgcPointY)->getPosY() - (_battle->getclassTile(EnemyMgcPointX, EnemyMgcPointY)->getZlevel() * 32) - 32;
			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;
			HPEN myPen = CreatePen(PS_SOLID, 3, RGB(125, 0, 125));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
			drawRhombus(left, top);
			DeleteObject(SelectObject(getMemDC(), oldPen));
		}
	}
}

void battleScene::alphTileMove()
{
	//알프 이동
	if (_alph->getmoveTile() == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (MovePointX < _battle->getTileX() - 1)
			{
				MovePointX++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (MovePointX > 0)
			{
				MovePointX--;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (MovePointY < _battle->getTileY() - 1)
			{
				MovePointY++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (MovePointY > 0)
			{
				MovePointY--;
			}
		}
	}



	//알프 공격
	if (_alph->getF() == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (alphAtkPointX < _battle->getTileX() - 1)
			{
				alphAtkPointX++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (alphAtkPointX > 0)
			{
				alphAtkPointX--;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (alphAtkPointY < _battle->getTileY() - 1)
			{
				alphAtkPointY++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (alphAtkPointY > 0)
			{
				alphAtkPointY--;
			}
		}
	}

	if (_alph->getF() == false)
	{
		alphAtkPointX = MovePointX;
		alphAtkPointY = MovePointY;
	}

	//알프 마법
	if (_alph->getisMgcPoint() == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (alphMgcPointX < _battle->getTileX() - 1)
			{
				alphMgcPointX++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (alphMgcPointX > 0)
			{
				alphMgcPointX--;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (alphMgcPointY < _battle->getTileY() - 1)
			{
				alphMgcPointY++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (alphMgcPointY > 0)
			{
				alphMgcPointY--;
			}
		}
	}

	if (_alph->getisMgcPoint() == false)
	{
		alphMgcPointX = MovePointX;
		alphMgcPointY = MovePointY;
	}



	if (_alph->getsynergeCheck() == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (alphSyPointX < _battle->getTileX() - 1)
			{
				alphSyPointX++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (alphSyPointX > 0)
			{
				alphSyPointX--;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (alphSyPointY < _battle->getTileY() - 1)
			{
				alphSyPointY++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (alphSyPointY > 0)
			{
				alphSyPointY--;
			}
		}
	}

	if (_alph->getsynergeCheck() == false)
	{
		alphSyPointX = MovePointX;
		alphSyPointY = MovePointY;
	}
}

void battleScene::luciaTileMove()
{

	if (_lucia->getmoveTile() == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (LuciaPointX < _battle->getTileX() - 1)
			{
				LuciaPointX++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (LuciaPointX > 0)
			{
				LuciaPointX--;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (LuciaPointY < _battle->getTileY() - 1)
			{
				LuciaPointY++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (LuciaPointY > 0)
			{
				LuciaPointY--;
			}
		}
	}

	//루시아 공격
	if (_lucia->getAtkPoint() == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (luciaAtkPointX < _battle->getTileX() - 1)
			{
				luciaAtkPointX++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (luciaAtkPointX > 0)
			{
				luciaAtkPointX--;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (luciaAtkPointY < _battle->getTileY() - 1)
			{
				luciaAtkPointY++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (luciaAtkPointY > 0)
			{
				luciaAtkPointY--;
			}
		}
	}

	if (_lucia->getAtkPoint() == false)
	{
		luciaAtkPointX = LuciaPointX;
		luciaAtkPointY = LuciaPointY;
	}


	//루시아 마법공격

	if (_lucia->getMgcPoint() == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (luciaMgcPointX < _battle->getTileX() - 1)
			{
				luciaMgcPointX++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (luciaMgcPointX > 0)
			{
				luciaMgcPointX--;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (luciaMgcPointY < _battle->getTileY() - 1)
			{
				luciaMgcPointY++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (luciaMgcPointY > 0)
			{
				luciaMgcPointY--;
			}
		}
	}
	if (_lucia->getMgcPoint() == false)
	{
		luciaMgcPointX = LuciaPointX;
		luciaMgcPointY = LuciaPointY;
	}

	if (_lucia->getsynergeCheck() == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (luciaSyPointX < _battle->getTileX() - 1)
			{
				luciaSyPointX++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (luciaSyPointX > 0)
			{
				luciaSyPointX--;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (luciaSyPointY < _battle->getTileY() - 1)
			{
				luciaSyPointY++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (luciaSyPointY > 0)
			{
				luciaSyPointY--;
			}
		}
	}

	if (_lucia->getsynergeCheck() == false)
	{
		luciaSyPointX = LuciaPointX;
		luciaSyPointY = LuciaPointY;
	}
}

void battleScene::EnemyTileMove()
{
	if (_enemy->getmoveTile() == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (EnemyPointX < _battle->getTileX() - 1)
			{
				EnemyPointX++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (EnemyPointX > 0)
			{
				EnemyPointX--;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (EnemyPointY < _battle->getTileY() - 1)
			{
				EnemyPointY++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (EnemyPointY > 0)
			{
				EnemyPointY--;
			}
		}
	}

	//에너미 공격
	if (_enemy->getAtkPoint() == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (EnemyAtkPointX < _battle->getTileX() - 1)
			{
				EnemyAtkPointX++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (EnemyAtkPointX > 0)
			{
				EnemyAtkPointX--;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (EnemyAtkPointY < _battle->getTileY() - 1)
			{
				EnemyAtkPointY++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (EnemyAtkPointY > 0)
			{
				EnemyAtkPointY--;
			}
		}
	}

	if (_enemy->getAtkPoint() == false)
	{
		EnemyAtkPointX = EnemyPointX;
		EnemyAtkPointY = EnemyPointY;
	}

	//에너미 마법
	if (_enemy->getMgcPoint() == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (EnemyMgcPointX < _battle->getTileX() - 1)
			{
				EnemyMgcPointX++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (EnemyMgcPointX > 0)
			{
				EnemyMgcPointX--;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (EnemyMgcPointY < _battle->getTileY() - 1)
			{
				EnemyMgcPointY++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (EnemyMgcPointY > 0)
			{
				EnemyMgcPointY--;
			}
		}
	}

	if (_enemy->getMgcPoint() == false)
	{
		EnemyMgcPointX = EnemyPointX;
		EnemyMgcPointY = EnemyPointY;
	}
}

void battleScene::zMove()
{
	if (_battle->getclassTile(alphX, alphY)->getZlevel() == 0)
	{
	alPhZ = 0;
	_alph->setZlevel(alPhZ);
	}
	else if (_battle->getclassTile(alphX, alphY)->getZlevel() == 1)
	{
	alPhZ = aZ * 1;
	_alph->setZlevel(alPhZ);
	}
	else if (_battle->getclassTile(alphX, alphY)->getZlevel() == 2)
	{
	alPhZ = aZ * 2;
	_alph->setZlevel(alPhZ);
	}
	else if (_battle->getclassTile(alphX, alphY)->getZlevel() == 3)
	{
	alPhZ = aZ * 3;
	_alph->setZlevel(alPhZ);
	}
	else if (_battle->getclassTile(alphX, alphY)->getZlevel() == 4)
	{
	alPhZ = aZ * 4;
	_alph->setZlevel(alPhZ);
	}
	else if (_battle->getclassTile(alphX, alphY)->getZlevel() == 5)
	{
	alPhZ = aZ * 5;
	_alph->setZlevel(alPhZ);
	}
	else if (_battle->getclassTile(alphX, alphY)->getZlevel() == 6)
	{
	alPhZ = aZ * 6;
	_alph->setZlevel(alPhZ);
	}
	else if (_battle->getclassTile(alphX, alphY)->getZlevel() == 7)
	{
	alPhZ = aZ * 7;
	_alph->setZlevel(alPhZ);
	}



	if (_battle->getclassTile(luciaX, luciaY)->getZlevel() == 0)
	{
		luciaZ = 0;
		_lucia->setZlevel(luciaZ);
	}

	else if (_battle->getclassTile(luciaX, luciaY)->getZlevel() == 1)
	{
		luciaZ = (lZ * 1) - 12;
		_lucia->setZlevel(luciaZ);
	}
	else if (_battle->getclassTile(luciaX, luciaY)->getZlevel() == 2)
	{
		luciaZ = (lZ * 2) - 18;
		_lucia->setZlevel(luciaZ);
	}
	else if (_battle->getclassTile(luciaX, luciaY)->getZlevel() == 3)
	{
		luciaZ = (lZ * 3) - 24;
		_lucia->setZlevel(luciaZ);
	}
	else if (_battle->getclassTile(luciaX, luciaY)->getZlevel() == 4)
	{
		luciaZ = (lZ * 4) - 30;
		_lucia->setZlevel(luciaZ);
	}
	else if (_battle->getclassTile(luciaX, luciaY)->getZlevel() == 5)
	{
		luciaZ = (lZ * 5) - 36;
		_lucia->setZlevel(luciaZ);
	}
	else if (_battle->getclassTile(luciaX, luciaY)->getZlevel() == 6)
	{
		luciaZ = (lZ * 6) - 42;
		_lucia->setZlevel(luciaZ);
	}
	else if (_battle->getclassTile(luciaX, luciaY)->getZlevel() == 7)
	{
		luciaZ = (lZ * 7) - 48;
		_lucia->setZlevel(luciaZ);
	}
	else if (_battle->getclassTile(luciaX, luciaY)->getZlevel() == 8)
	{
		luciaZ = (lZ * 8) - 54;
		_lucia->setZlevel(luciaZ);
	}
	else if (_battle->getclassTile(luciaX, luciaY)->getZlevel() == 9)
	{
		luciaZ = (lZ * 9) - 60;
		_lucia->setZlevel(luciaZ);
	}


//======================enemy========================//
	if (_battle->getclassTile(enemyX, enemyY)->getZlevel() == 0)
	{
		enemyZ = 0;
		_enemy->setZlevel(enemyZ);
	}

	else if (_battle->getclassTile(enemyX, enemyY)->getZlevel() == 1)
	{
		enemyZ = (lZ * 1) - 12;
		_enemy->setZlevel(enemyZ);
	}
	else if (_battle->getclassTile(enemyX, enemyY)->getZlevel() == 2)
	{
		enemyZ = (lZ * 2) - 18;
		_enemy->setZlevel(enemyZ);
	}
	else if (_battle->getclassTile(enemyX, enemyY)->getZlevel() == 3)
	{
		enemyZ = (lZ * 3) - 24;
		_enemy->setZlevel(enemyZ);
	}
	else if (_battle->getclassTile(enemyX, enemyY)->getZlevel() == 4)
	{
		enemyZ = (lZ * 4) - 30;
		_enemy->setZlevel(enemyZ);
	}
	else if (_battle->getclassTile(enemyX, enemyY)->getZlevel() == 5)
	{
		enemyZ = (lZ * 5) - 36;
		_enemy->setZlevel(enemyZ);
	}
	else if (_battle->getclassTile(enemyX, enemyY)->getZlevel() == 6)
	{
		enemyZ = (lZ * 6) - 42;
		_enemy->setZlevel(enemyZ);
	}
	else if (_battle->getclassTile(enemyX, enemyY)->getZlevel() == 7)
	{
		enemyZ = (lZ * 7) - 48;
		_enemy->setZlevel(enemyZ);
	}
	else if (_battle->getclassTile(enemyX, enemyY)->getZlevel() == 8)
	{
		enemyZ = (lZ * 8) - 54;
		_enemy->setZlevel(enemyZ);
	}
	else if (_battle->getclassTile(enemyX, enemyY)->getZlevel() == 9)
	{
		enemyZ = (lZ * 9) - 60;
		_enemy->setZlevel(enemyZ);
	}

}

void battleScene::cameraMove()
{

//초기 카메라 위치 세팅//
	if (StartCamera == false)
	{
		_camera->playerMode(_alph->getViewX(), _alph->getViewY() - alPhZ);
	}

// 대기할때 카메라 시점 변경 //
	
//==============알프 -> 루시아================//
	if (_alph->getchange() == true)
	{
		Camerachange = true;
		StartCamera = true;
		alphCamera = true;
		luciaChange = true;
	}
	if (luciaChange == true)
	{
		if (alphCamera == true)
		{
		_camera->linearMove(_battle->getclassTile(luciaX, luciaY)->getPos(), _battle->getclassTile(luciaX, luciaY)->getPosY() - luciaZ, 1);
		_camera->linearMoving();
	
		_lucia->setcheck(true);
		}
		if (_camera->getCameraMode() == 0)
		{
			alphCamera = false;
			_camera->playerMode(_lucia->getViewX(), _lucia->getViewY() - luciaZ);
			_alph->setchange(false);
		}
	}

//=============루시아 -> 에너미 ==================//
	if (_lucia->getchange() == true)
	{
		luciaCamera = true;
		Enemychange = true;
		luciaChange = false;
	}

	if (Enemychange == true)
	{
		if (luciaCamera == true)
		{
			_camera->linearMove(_battle->getclassTile(enemyX, enemyY)->getPos(), _battle->getclassTile(enemyX, enemyY)->getPosY() - alPhZ, 1);
			_camera->linearMoving();
	
			_enemy->setCheck(true);
		}
		if (_camera->getCameraMode() == 0)
		{
			luciaCamera = false;
			_camera->playerMode(_enemy->getViewX(), _enemy->getViewY() - alPhZ);
			_lucia->setchange(false);
		}
	}

//===============에너미 -> 알프=====================//
	if (_enemy->getchange() == true)
	{
		enemyCamera = true;
		Enemychange = false;
		Camerachange = false;
	}

	if (Camerachange == false)
	{
		if (enemyCamera == true)
		{
			_camera->linearMove(_battle->getclassTile(alphX, alphY)->getPos(), _battle->getclassTile(alphX, alphY)->getPosY() - alPhZ, 1);
			_camera->linearMoving();

			_alph->setCheck(true);
		}

		if (_camera->getCameraMode() == 0)
		{
			enemyCamera = false;
			_camera->playerMode(_alph->getViewX(), _alph->getViewY() - alPhZ);
			_enemy->setchange(false);
		}
	}

// 밑에 건드리지 말것 //
//====================루시아로 시점 변경====================//
	//if (_alph->getchange() == true)
	//{
	//	Camerachange = true;
	//	StartCamera = true;
	//	alphCamera = true;
	//}
 	//if (Camerachange == true)
	//{
	//	if (alphCamera == true)
	//	{
	//	_camera->linearMove(_battle->getclassTile(luciaX, luciaY)->getPos(), _battle->getclassTile(luciaX, luciaY)->getPosY() - luciaZ, 1);
	//	_camera->linearMoving();
	//
	//	_lucia->setcheck(true);
	//	}
	//	if (_camera->getCameraMode() == 0)
	//	{
	//		alphCamera = false;
	//		_camera->playerMode(_lucia->getViewX(), _lucia->getViewY() - luciaZ);
	//		_alph->setchange(false);
	//	}
	//}
	//
	////====================알프로 시점 변경====================//
	//if (_lucia->getchange() == true)
	//{
	//	luciaCamera = true;
	//	Camerachange = false;
	//}
	//if (Camerachange == false)
	//{
	//	if (luciaCamera == true)
	//	{
	//		_camera->linearMove(_battle->getclassTile(alphX, alphY)->getPos(), _battle->getclassTile(alphX, alphY)->getPosY() - alPhZ, 1);
	//		_camera->linearMoving();
	//
	//		_alph->setCheck(true);
	//	}
	//	if (_camera->getCameraMode() == 0)
	//	{
	//		luciaCamera = false;
	//		_camera->playerMode(_alph->getViewX(), _alph->getViewY() - alPhZ);
	//		_lucia->setchange(false);
	//	}
	//}

}

void battleScene::PlayerDead()
{

	if (_luciaHp <= 0)
	{
		_lucia->setDead(true);


		if (enemyY < luciaY)
		{
			_lucia->setDeadNumber(2);
		}

		if (enemyY > luciaY)
		{
			_lucia->setDeadNumber(0);
		}

		if (enemyX > luciaX)
		{
			_lucia->setDeadNumber(1);
		}

		if (enemyX < luciaX)
		{
			_lucia->setDeadNumber(3);
		}
	}

	if (_alphHp <= 0)
	{
		_alph->setDead(true);

		if (alphY < enemyY)
		{
			_alph->setDeadNumber(0);
		}
		if (alphY > enemyY)
		{
			_alph->setDeadNumber(1);
		}
		if (alphX > enemyX)
		{
			_alph->setDeadNumber(3);
		}
		if (alphX < enemyX)
		{
			_alph->setDeadNumber(2);
		}
	}

	if (_enemyHp <= 0)
	{
		_enemy->setDead(true);

		if (Camerachange == false)
		{
			if (alphY < enemyY)
			{
				_enemy->setDeadNumber(2);
			}
			if (alphY > enemyY)
			{
				_enemy->setDeadNumber(0);
			}
			if (alphX > enemyX)
			{
				_enemy->setDeadNumber(1);
			}
			if (alphX < enemyX)
			{
				_enemy->setDeadNumber(3);
			}
		}


		if (luciaChange == true)
		{
			if (luciaY < enemyY)
			{
				_enemy->setDeadNumber(2);
			}
			if (luciaY > enemyY)
			{
				_enemy->setDeadNumber(0);
			}
			if (luciaX > enemyX)
			{
				_enemy->setDeadNumber(1);
			}
			if (luciaX < enemyX)
			{
				_enemy->setDeadNumber(3);
			}
		}
	}

}

void battleScene::HitDemege()
{
	if (_lucia->getHit() == true)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (EnemyMgcPointX == luciaX && EnemyMgcPointY == luciaY)
			{
				if (EnemyLuciaMgcDmg % 10 == i)
				{
					IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(luciaX, luciaY)->getPos() - _camera->getCameraX(), _battle->getclassTile(luciaX, luciaY)->getPosY() - 60 - _camera->getCameraY() - _lucia->getZlevel(), i, 0);
				}

				if ((EnemyLuciaMgcDmg / 10) % 10 == i)
				{
					IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(luciaX, luciaY)->getPos() - _camera->getCameraX() - 20, _battle->getclassTile(luciaX, luciaY)->getPosY() - 60 - _camera->getCameraY() - _lucia->getZlevel(), i, 0);
				}
			}

			if (EnemyAtkPointX == luciaX && EnemyAtkPointY == luciaY)
			{
				if (EnemyLuciaAtkDmg % 10 == i)
				{
					IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(luciaX, luciaY)->getPos() - _camera->getCameraX(), _battle->getclassTile(luciaX, luciaY)->getPosY() - 60 - _camera->getCameraY() - _lucia->getZlevel(), i, 0);
				}

				if ((EnemyLuciaAtkDmg / 10) % 10 == i)
				{
					IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(luciaX, luciaY)->getPos() - _camera->getCameraX() - 20, _battle->getclassTile(luciaX, luciaY)->getPosY() - 60 - _camera->getCameraY() - _lucia->getZlevel(), i, 0);
				}
			}
		}
	}
	if (_alph->getHit() == true)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (EnemyMgcPointX == alphX && EnemyMgcPointY == alphY)
			{
				if (EnemyAlphMgcDmg % 10 == i)
				{
					IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(alphX, alphY)->getPos() - _camera->getCameraX(), _battle->getclassTile(alphX, alphY)->getPosY() - 60 - _camera->getCameraY() - _alph->getZlevel(), i, 0);
				}

				if ((EnemyAlphMgcDmg / 10) % 10 == i)
				{
					IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(alphX, alphY)->getPos() - _camera->getCameraX() - 20, _battle->getclassTile(alphX, alphY)->getPosY() - 60 - _camera->getCameraY() - _alph->getZlevel(), i, 0);
				}
			}

			if (EnemyAtkPointX == alphX && EnemyAtkPointY == alphY)
			{
				if (EnemyAlphAtkDmg % 10 == i)
				{
					IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(alphX, alphY)->getPos() - _camera->getCameraX(), _battle->getclassTile(alphX, alphY)->getPosY() - 60 - _camera->getCameraY() - _alph->getZlevel(), i, 0);
				}

				if ((EnemyAlphAtkDmg / 10) % 10 == i)
				{
					IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(alphX, alphY)->getPos() - _camera->getCameraX() - 20, _battle->getclassTile(alphX, alphY)->getPosY() - 60 - _camera->getCameraY() - _alph->getZlevel(), i, 0);
				}
			}
		}
	}

	if (_enemy->getHit() == true)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (luciaMgcPointX == enemyX && luciaMgcPointY == enemyY)
			{
				if (luciaMgcDmg % 10 == i)
				{
					IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(enemyX, enemyY)->getPos() - _camera->getCameraX(), _battle->getclassTile(enemyX, enemyY)->getPosY() - 60 - _camera->getCameraY() - _enemy->getZlevel(), i, 0);
				}

				if ((luciaMgcDmg / 10) % 10 == i)
				{
					IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(enemyX, enemyY)->getPos() - _camera->getCameraX() - 20, _battle->getclassTile(enemyX, enemyY)->getPosY() - 60 - _camera->getCameraY() - _enemy->getZlevel(), i, 0);
				}
			}

			if (luciaAtkPointX == enemyX && luciaAtkPointY == enemyY)
			{
				if (luciaAtkDmg % 10 == i)
				{
					IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(enemyX, enemyY)->getPos() - _camera->getCameraX(), _battle->getclassTile(enemyX, enemyY)->getPosY() - 60 - _camera->getCameraY() - _enemy->getZlevel(), i, 0);
				}

				if ((luciaAtkDmg / 10) % 10 == i)
				{
					IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(enemyX, enemyY)->getPos() - _camera->getCameraX() - 20, _battle->getclassTile(enemyX, enemyY)->getPosY() - 60 - _camera->getCameraY() - _enemy->getZlevel(), i, 0);
				}
			}



			if (alphMgcPointX == enemyX && alphMgcPointY == enemyY)
			{
				if (alphMgcDmg % 10 == i)
				{
					IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(enemyX, enemyY)->getPos() - _camera->getCameraX(), _battle->getclassTile(enemyX, enemyY)->getPosY() - 60 - _camera->getCameraY() - _enemy->getZlevel(), i, 0);
				}

				if ((alphMgcDmg / 10) % 10 == i)
				{
					IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(enemyX, enemyY)->getPos() - _camera->getCameraX() - 20, _battle->getclassTile(enemyX, enemyY)->getPosY() - 60 - _camera->getCameraY() - _enemy->getZlevel(), i, 0);
				}
			}

			if (alphAtkPointX == enemyX && alphAtkPointY == enemyY)
			{
				if (alphAtkDmg % 10 == i)
				{
					IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(enemyX, enemyY)->getPos() - _camera->getCameraX(), _battle->getclassTile(enemyX, enemyY)->getPosY() - 60 - _camera->getCameraY() - _enemy->getZlevel(), i, 0);
				}

				if ((alphAtkDmg / 10) % 10 == i)
				{
					IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(enemyX, enemyY)->getPos() - _camera->getCameraX() - 20, _battle->getclassTile(enemyX, enemyY)->getPosY() - 60 - _camera->getCameraY() - _enemy->getZlevel(), i, 0);
				}
			}
		}
	}
}

void battleScene::alphState()
{
	for (int i = 0; i < 10; ++i)
	{
		//현재 체력
		if (_alph->getCurrentHp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 140, 295, i, 0);
		}
		if (((_alph->getCurrentHp()) / 10) % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 120, 295, i, 0);
		}
		if (((_alph->getCurrentHp()) / 100) % 10 == i)
		{
	
		IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 100, 295, i, 0);

		}
		
		//현재 물리공격력
		if (_alph->getAtkDmg() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 75, i , 0);
		}
		if (((_alph->getAtkDmg()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 75, i, 0);
			}
		}
		if (((_alph->getAtkDmg()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 75, i, 0);
			}
		}
		//현재 물리방어력

		if (_alph->getAtkDef() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 130, i, 0);
		}
		if (((_alph->getAtkDef()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 130, i, 0);
			}
		}
		if (((_alph->getAtkDef()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 130, i, 0);
			}
		}
		//현재 스피드
		if (_alph->getmoveSpeed() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 185, i, 0);
		}
		if (((_alph->getmoveSpeed()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 185, i, 0);
			}
		}
		if (((_alph->getmoveSpeed()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 185, i, 0);
			}
		}
		//현재 명중률
		if (_alph->getAccuracy() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 240, i, 0);
		}
		if (((_alph->getAccuracy()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 240, i, 0);
			}
		}
		if (((_alph->getAccuracy()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 240, i, 0);
			}
		}
		//현재 마법공격
		if (_alph->getMgcDmg() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 295, i, 0);
		}
		if (((_alph->getMgcDmg()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 295, i, 0);
			}
		}
		if (((_alph->getMgcDmg()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 295, i, 0);
			}
		}
		
		//현재 마법방어
		if (_alph->getMgcDef() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 350, i, 0);
		}
		if (((_alph->getMgcDef()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 350, i, 0);
			}
		}
		if (((_alph->getMgcDef()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 350, i, 0);
			}
		}

		//현재 이동가능범위
		if (_alph->getMove() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 395, 3, 0);
		}
		if (((_alph->getMove()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 395, i, 0);
			}
		}
		if (((_alph->getMove()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 395, i, 0);
			}
		}

		//알프 레벨
		if (_alph->getLevel() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 240, 30, i, 0);
		}
		if (((_alph->getLevel()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 220,30, i, 0);
			}
		}
		if (((_alph->getLevel()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 200, 30, i, 0);
			}
		}

		//알프 경험치
		if (_alph->getExp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 240, 60, i, 0);
		}
		if (((_alph->getExp()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 220, 60, i, 0);
			}
		}
		if (((_alph->getExp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 200, 60, i, 0);
			}
		}

		//알프 맥스체력
		if (_alph->getMaxHp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 240, 295, i , 0);
		}
		if (((_alph->getMaxHp()) / 10) % 10 == i)
		{
		IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 220, 295, i , 0);

		}
		if (((_alph->getMaxHp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 200, 295, i , 0);
			}
		}

		//알프 마력
		if (_alph->getCurrentMp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 240, 350, i, 0);
		}
		if (((_alph->getCurrentMp()) / 10) % 10 == i)
		{
		
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 220, 350, i, 0);
			
		}
		if (((_alph->getCurrentMp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 200, 350, i, 0);
			}
		}

		//알프 맥스마력
		if (_alph->getMaxMp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 140, 350, i, 0);
		}
		if (((_alph->getMaxMp()) / 10) % 10 == i)
		{
			
			{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 120, 350, i, 0);
			}
		}
		if (((_alph->getMaxMp()) / 100) % 10 == i)
		{
			
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 100, 350, i, 0);
			}
		}	
	}
	
	if (_alphFp >= 0 && _alphFp <= 80)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 160, 420, 0, 0);
	}

	if (_alphFp >= 81 && _alphFp <= 161)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 160, 420, 1, 0);
	}

	if (_alphFp >= 162 && _alphFp <= 241)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 160, 420, 2, 0);
	}

	if (_alphFp == 242)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 160, 420, 3, 0);
	}

	IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 230, 420, 3, 0);


}

void battleScene::luciaState()
{
	for (int i = 0; i < 10; ++i)
	{
		//현재 체력
		if (_lucia->getCurrentHp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 140, 295, i , 0);
		}
		if (((_lucia->getCurrentHp()) / 10) % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 120, 295, i , 0);
		}
		if (((_lucia->getCurrentHp()) / 100) % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 100, 295, i, 0);
		}

		//현재 물리공격력
		if (_lucia->getAtkDmg() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 75, i, 0);
		}
		if (((_lucia->getAtkDmg()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 75, i, 0);
			}
		}
		if (((_lucia->getAtkDmg()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 75, i, 0);
			}
		}
		//현재 물리방어력

		if (_lucia->getAtkDef() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 130, i, 0);
		}
		if (((_lucia->getAtkDef()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 130, i, 0);
			}
		}
		if (((_lucia->getAtkDef()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 130, i, 0);
			}
		}
		//현재 스피드
		if (_lucia->getmoveSpeed() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 185, i, 0);
		}
		if (((_lucia->getmoveSpeed()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 185, i, 0);
			}
		}
		if (((_lucia->getmoveSpeed()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 185, i, 0);
			}
		}
		//현재 명중률
		if (_lucia->getAccuracy() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 240, i, 0);
		}
		if (((_lucia->getAccuracy()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 240, i, 0);
			}
		}
		if (((_lucia->getAccuracy()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 240, i, 0);
			}
		}
		//현재 마법공격
		if (_lucia->getMgcDmg() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 295, i, 0);
		}
		if (((_lucia->getMgcDmg()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 295, i, 0);
			}
		}
		if (((_lucia->getMgcDmg()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 295, i, 0);
			}
		}

		//현재 마법방어
		if (_lucia->getMgcDef() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 350, i, 0);
		}
		if (((_lucia->getMgcDef()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 350, i, 0);
			}
		}
		if (((_lucia->getMgcDef()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 350, i, 0);
			}
		}

		//현재 이동가능범위
		if (_lucia->getMove() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 395, i, 0);
		}
		if (((_lucia->getMove()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 395, i, 0);
			}
		}
		if (((_lucia->getMove()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 395, i, 0);
			}
		}

		//루시아 레벨
		if (_lucia->getLevel() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 240, 30, i, 0);
		}
		if (((_lucia->getLevel()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 220, 30, i, 0);
			}
		}
		if (((_lucia->getLevel()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 200, 30, i, 0);
			}
		}

		//루시아 경험치
		if (_lucia->getExp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 240, 60, i, 0);
		}
		if (((_lucia->getExp()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 220, 60, i, 0);
			}
		}
		if (((_lucia->getExp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 200, 60, i, 0);
			}
		}

		//루시아 맥스체력
		if (_lucia->getMaxHp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 240, 295, i , 0);
		}
		if (((_lucia->getMaxHp()) / 10) % 10 == i)
		{
		
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 220, 295, i , 0);
			
		}
		if (((_lucia->getMaxHp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 200, 295, i , 0);
			}
		}

		//루시아 마력
		if (_lucia->getCurrentMp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 140, 350, i, 0);
		}
		if (((_lucia->getCurrentMp()) / 10) % 10 == i)
		{
			
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 120, 350, i, 0);
			
		}
		if (((_lucia->getCurrentMp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 100, 350, i, 0);
			}
		}

		//루시아 맥스마력
		if (_lucia->getMaxMp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 240, 350, i, 0);
		}
		if (((_lucia->getMaxMp()) / 10) % 10 == i)
		{
		
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 220, 350, i, 0);
			
		}
		if (((_lucia->getMaxMp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 200, 350, i, 0);
			}
		}
	}

	if (_luciaFp >= 0 && _luciaFp <= 80)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 160, 420, 0, 0);
	}

	if (_luciaFp >= 81 && _luciaFp <= 161)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 160, 420, 1, 0);
	}

	if (_luciaFp >= 162 && _luciaFp <= 241)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 160, 420, 2, 0);
	}

	if (_luciaFp == 242)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 160, 420, 3, 0);
	}

	IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 230, 420, 3, 0);
}

void battleScene::enemyState()
{
	for (int i = 0; i < 10; ++i)
	{
		//현재 체력
		if (_enemy->getCurrentHp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 140, 295, i, 0);
		}
		if (((_enemy->getCurrentHp()) / 10) % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 120, 295, i, 0);
		}
		if (((_enemy->getCurrentHp()) / 100) % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 100, 295, i, 0);
		}

		//현재 물리공격력
		if (_enemy->getAtkDmg() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 75, i, 0);
		}
		if (((_enemy->getAtkDmg()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 75, i, 0);
			}
		}
		if (((_enemy->getAtkDmg()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 75, i, 0);
			}
		}
		//현재 물리방어력

		if (_enemy->getAtkDef() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 130, i, 0);
		}
		if (((_enemy->getAtkDef()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 130, i, 0);
			}
		}
		if (((_enemy->getAtkDef()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 130, i, 0);
			}
		}
		//현재 스피드
		if (_enemy->getmoveSpeed() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 185, i, 0);
		}
		if (((_enemy->getmoveSpeed()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 185, i, 0);
			}
		}
		if (((_enemy->getmoveSpeed()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 185, i, 0);
			}
		}
		//현재 명중률
		if (_enemy->getAccuracy() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 240, i, 0);
		}
		if (((_enemy->getAccuracy()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 240, i, 0);
			}
		}
		if (((_enemy->getAccuracy()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 240, i, 0);
			}
		}
		//현재 마법공격
		if (_enemy->getMgcDmg() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 295, i, 0);
		}
		if (((_enemy->getMgcDmg()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 295, i, 0);
			}
		}
		if (((_enemy->getMgcDmg()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 295, i, 0);
			}
		}

		//현재 마법방어
		if (_enemy->getMgcDef() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 350, i, 0);
		}
		if (((_enemy->getMgcDef()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 350, i, 0);
			}
		}
		if (((_enemy->getMgcDef()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 350, i, 0);
			}
		}

		//현재 이동가능범위
		if (_enemy->getMove() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 700, 395, 3, 0);
		}
		if (((_enemy->getMove()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 670, 395, i, 0);
			}
		}
		if (((_enemy->getMove()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 640, 395, i, 0);
			}
		}

		//루시아 레벨
		if (_enemy->getLevel() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 240, 30, i, 0);
		}
		if (((_enemy->getLevel()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 220, 30, i, 0);
			}
		}
		if (((_enemy->getLevel()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 200, 30, i, 0);
			}
		}

		//루시아 경험치
		if (_enemy->getExp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 240, 60, i, 0);
		}
		if (((_enemy->getExp()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 220, 60, i, 0);
			}
		}
		if (((_enemy->getExp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 200, 60, i, 0);
			}
		}

		//루시아 맥스체력
		if (_enemy->getMaxHp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 240, 295, i, 0);
		}
		if (((_enemy->getMaxHp()) / 10) % 10 == i)
		{

			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 220, 295, i, 0);

		}
		if (((_enemy->getMaxHp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 200, 295, i, 0);
			}
		}

		//루시아 마력
		if (_enemy->getCurrentMp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 140, 350, i, 0);
		}
		if (((_enemy->getCurrentMp()) / 10) % 10 == i)
		{

			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 120, 350, i, 0);

		}
		if (((_enemy->getCurrentMp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 100, 350, i, 0);
			}
		}

		//루시아 맥스마력
		if (_enemy->getMaxMp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 240, 350, i, 0);
		}
		if (((_enemy->getMaxMp()) / 10) % 10 == i)
		{

			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 220, 350, i, 0);

		}
		if (((_enemy->getMaxMp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 200, 350, i, 0);
			}
		}
	}

	if (_enemyFp >= 0 && _enemyFp <= 80)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 160, 420, 0, 0);
	}

	if (_enemyFp >= 81 && _enemyFp <= 161)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 160, 420, 1, 0);
	}

	if (_enemyFp >= 162 && _enemyFp <= 241)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 160, 420, 2, 0);
	}

	if (_enemyFp == 242)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 160, 420, 3, 0);
	}

	IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 230, 420, 3, 0);
}

void battleScene::alphView()
{
	IMAGEMANAGER->render("alphLog", IMAGEMANAGER->findImage("Gameground")->getMemDC(), 0, 500);
	IMAGEMANAGER->findImage("level")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 20, 660);
	IMAGEMANAGER->findImage("hp")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 555);
	IMAGEMANAGER->findImage("mp")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 605);
	IMAGEMANAGER->findImage("fp")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 675);
	IMAGEMANAGER->findImage("Hpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 580, 0, 0, _alphHp, 26);
	IMAGEMANAGER->findImage("Mpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 630, 0, 0, _alphMp, 26);
	IMAGEMANAGER->findImage("Fpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 700, 0, 0, _alphFp, 26);
	IMAGEMANAGER->findImage("atkDef")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 480, 560);
	IMAGEMANAGER->findImage("mgcDef")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 480, 640);
	IMAGEMANAGER->findImage("equl")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 540, 570);
	IMAGEMANAGER->findImage("equl")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 540, 650);

	for (int i = 0; i < 10; ++i)
	{
		//현재 체력
		if (_alph->getCurrentHp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 300, 559, i, 0);
		}
		if (((_alph->getCurrentHp()) / 10) % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 280, 559, i , 0);
		}
		if (((_alph->getCurrentHp()) / 100) % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 260, 559, i , 0);
		}

		//알프 맥스체력
		if (_alph->getMaxHp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 400, 559, i , 0);
		}
		if (((_alph->getMaxHp()) / 10) % 10 == i)
		{
		
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 380, 559, i , 0);
			
		}
		if (((_alph->getMaxHp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 360, 559, i , 0);
			}
		}

		//알프 레벨
		if (_alph->getLevel() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 120, 670, i, 0);
		}
		if (((_alph->getLevel()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 100, 670, i, 0);
			}
		}
		if (((_alph->getLevel()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 80, 670, i, 0);
			}
		}

		//물리 방어력
		if (_alph->getAtkDef() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 620, 572, i, 0);
		}
		if (((_alph->getAtkDef()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 590, 572, i, 0);
			}
		}
		if (((_alph->getAtkDef()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 560, 572, i, 0);
			}
		}

		//마법 방어력
		if (_alph->getMgcDef() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 620, 652, i, 0);
		}
		if (((_alph->getMgcDef()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 590, 652, i, 0);
			}
		}
		if (((_alph->getMgcDef()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 560, 652, i, 0);
			}
		}
		
		//알프 마력
		if (_alph->getCurrentMp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 300, 611, i, 0);
		}
		if (((_alph->getCurrentMp()) / 10) % 10 == i)
		{

			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 280, 611, i, 0);

		}
		if (((_alph->getCurrentMp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 260, 611, i, 0);
			}
		}

		//알프 맥스마력
		if (_alph->getMaxMp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 400, 611, i, 0);
		}
		if (((_alph->getMaxMp()) / 10) % 10 == i)
		{

			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 380, 611, i, 0);

		}
		if (((_alph->getMaxMp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 360, 611, i, 0);
			}
		}
	}

	if (_alphFp >= 0 && _alphFp <= 80)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 330, 674, 0, 0);
	}

	if (_alphFp >= 81 && _alphFp <= 161)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 330, 674, 1, 0);
	}

	if (_alphFp >= 162 && _alphFp <= 241)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 330, 674, 2, 0);
	}

	if (_alphFp == 242)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 330, 674, 3, 0);
	}

	IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 390, 674, 3, 0);
}

void battleScene::luciaView()
{
	IMAGEMANAGER->render("luciaLog", IMAGEMANAGER->findImage("Gameground")->getMemDC(), 0, 500);
	IMAGEMANAGER->findImage("level")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 20, 660);
	IMAGEMANAGER->findImage("hp")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 555);
	IMAGEMANAGER->findImage("mp")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 605);
	IMAGEMANAGER->findImage("fp")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 675);
	IMAGEMANAGER->findImage("Hpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 580, 0, 0, _luciaHp, 26);
	IMAGEMANAGER->findImage("Mpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 630, 0, 0, _luciaMp, 26);
	IMAGEMANAGER->findImage("Fpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 700, 0, 0, _luciaFp, 26);
	IMAGEMANAGER->findImage("atkDef")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 480, 560);
	IMAGEMANAGER->findImage("mgcDef")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 480, 640);
	IMAGEMANAGER->findImage("equl")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 540, 570);
	IMAGEMANAGER->findImage("equl")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 540, 650);

	for (int i = 0; i < 10; ++i)
	{
		//현재 체력
		if (_lucia->getCurrentHp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 300, 559, i, 0);
		}
		if (((_lucia->getCurrentHp()) / 10) % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 280, 559, i, 0);
		}
		if (((_lucia->getCurrentHp()) / 100) % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 260, 559, i, 0);
		}

		//루시아 맥스체력
		if (_lucia->getMaxHp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 400, 559, i, 0);
		}
		if (((_lucia->getMaxHp()) / 10) % 10 == i)
		{
			
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 380, 559, i, 0);

		}
		if (((_lucia->getMaxHp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 360, 559, i, 0);
			}
		}

		//루시아 레벨
		if (_lucia->getLevel() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 120, 670, i, 0);
		}
		if (((_lucia->getLevel()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 100, 670, i, 0);
			}
		}
		if (((_lucia->getLevel()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 80, 670, i, 0);
			}
		}

		//물리 방어력
		if (_lucia->getAtkDef() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 620, 572, i, 0);
		}
		if (((_lucia->getAtkDef()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 590, 572, i, 0);
			}
		}
		if (((_lucia->getAtkDef()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 560, 572, i, 0);
			}
		}

		//마법 방어력
		if (_lucia->getMgcDef() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 620, 652, i, 0);
		}
		if (((_lucia->getMgcDef()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 590, 652, i, 0);
			}
		}
		if (((_lucia->getMgcDef()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 560, 652, i, 0);
			}
		}

		//루시아 마력
		if (_lucia->getCurrentMp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 300, 611, i, 0);
		}
		if (((_lucia->getCurrentMp()) / 10) % 10 == i)
		{
		
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 280, 611, i, 0);
			
		}
		if (((_lucia->getCurrentMp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 260, 611, i, 0);
			}
		}

		//루시아 맥스마력
		if (_lucia->getMaxMp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 400, 611, i, 0);
		}
		if (((_lucia->getMaxMp()) / 10) % 10 == i)
		{
			
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 380, 611, i, 0);
			
		}
		if (((_lucia->getMaxMp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 360, 611, i, 0);
			}
		}
	}
	
	if (_luciaFp >= 0 && _luciaFp <= 80)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 330, 674, 0, 0);
	}

	if (_luciaFp >= 81 && _luciaFp <= 161)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 330, 674, 1, 0);
	}

	if (_luciaFp >= 162 && _luciaFp <= 241)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 330, 674, 2, 0);
	}

	if (_luciaFp == 242)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 330, 674, 3, 0);
	}

	IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 390, 674, 3, 0);
}

void battleScene::enemyView()
{
	IMAGEMANAGER->render("irisLog", IMAGEMANAGER->findImage("Gameground")->getMemDC(), 0, 500);
	IMAGEMANAGER->findImage("level")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 20, 660);
	IMAGEMANAGER->findImage("hp")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 555);
	IMAGEMANAGER->findImage("mp")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 605);
	IMAGEMANAGER->findImage("fp")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 675);
	IMAGEMANAGER->findImage("Hpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 580, 0, 0, _enemyHp, 26);
	IMAGEMANAGER->findImage("Mpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 630, 0, 0, _enemyMp, 26);
	IMAGEMANAGER->findImage("Fpbar")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 180, 700, 0, 0, _enemyFp, 26);
	IMAGEMANAGER->findImage("atkDef")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 480, 560);
	IMAGEMANAGER->findImage("mgcDef")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 480, 640);
	IMAGEMANAGER->findImage("equl")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 540, 570);
	IMAGEMANAGER->findImage("equl")->render(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 540, 650);

	for (int i = 0; i < 10; ++i)
	{
		//현재 체력
		if (_enemy->getCurrentHp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 300, 559, i, 0);
		}
		if (((_enemy->getCurrentHp()) / 10) % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 280, 559, i, 0);
		}
		if (((_enemy->getCurrentHp()) / 100) % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 260, 559, i, 0);
		}

		//에너미 맥스체력
		if (_enemy->getMaxHp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 400, 559, i, 0);
		}
		if (((_enemy->getMaxHp()) / 10) % 10 == i)
		{

			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 380, 559, i, 0);

		}
		if (((_enemy->getMaxHp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 360, 559, i, 0);
			}
		}

		//에너미 레벨
		if (_enemy->getLevel() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 120, 670, i, 0);
		}
		if (((_enemy->getLevel()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 100, 670, i, 0);
			}
		}
		if (((_enemy->getLevel()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 80, 670, i, 0);
			}
		}

		//물리 방어력
		if (_enemy->getAtkDef() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 620, 572, i, 0);
		}
		if (((_enemy->getAtkDef()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 590, 572, i, 0);
			}
		}
		if (((_enemy->getAtkDef()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 560, 572, i, 0);
			}
		}

		//마법 방어력
		if (_enemy->getMgcDef() % 10 == i)
		{
			IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 620, 652, i, 0);
		}
		if (((_enemy->getMgcDef()) / 10) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 590, 652, i, 0);
			}
		}
		if (((_enemy->getMgcDef()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 560, 652, i, 0);
			}
		}

		//에너미 마력
		if (_enemy->getCurrentMp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 300, 611, i, 0);
		}
		if (((_enemy->getCurrentMp()) / 10) % 10 == i)
		{

			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 280, 611, i, 0);

		}
		if (((_enemy->getCurrentMp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 260, 611, i, 0);
			}
		}

		//에너미 맥스마력
		if (_enemy->getMaxMp() % 10 == i)
		{
			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 400, 611, i, 0);
		}
		if (((_enemy->getMaxMp()) / 10) % 10 == i)
		{

			IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 380, 611, i, 0);

		}
		if (((_enemy->getMaxMp()) / 100) % 10 == i)
		{
			if (i != 0)
			{
				IMAGEMANAGER->findImage("number")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 360, 611, i, 0);
			}
		}
	}

	if (_enemyFp >= 0 && _enemyFp <= 80)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 330, 674, 0, 0);
	}

	if (_enemyFp >= 81 && _enemyFp <= 161)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 330, 674, 1, 0);
	}

	if (_enemyFp >= 162 && _enemyFp <= 241)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 330, 674, 2, 0);
	}

	if (_enemyFp == 242)
	{
		IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 330, 674, 3, 0);
	}

	IMAGEMANAGER->findImage("number2")->frameRender(IMAGEMANAGER->findImage("Gameground")->getMemDC(), 390, 674, 3, 0);
}

void battleScene::SynergeSkill()
{
		if (_alph->getSygage() >= 242 && _lucia->getSygage() >= 242)
		{
			if (_alph->getSynerge() == true || _lucia->getSynerge() == true)
			{
 				//if (_alph->getMgcRange() == false && _alph->getAtkRange() == false && _alph->getmoveTile() == false)
				{
					if ((alphSyPointX == enemyX && alphSyPointY == enemyY) || luciaSyPointX == enemyX && luciaSyPointY == enemyY)
					{
						SynergeCount++;
						
						if (SynergeCount <= 100)
						{
							
							IMAGEMANAGER->findImage("Synerge")->render(getMemDC(), 768, 0);
							_alphFp = 0;
							_luciaFp = 0;

						}
						if (SynergeCount > 100)
						{
							_alph->setSynerge(false);
							_lucia->setSynerge(false);
							_alph->setsynergeCheck(false);
							_alph->setsynergeRange(false);
							_alph->setSygage(_alphFp);
							_lucia->setSygage(_luciaFp);
							SyAtk = true;
							SynergeCount = 0;
						}
					}
				}
			}
		}

		if (SyAtk == true)
		{
			SyCount++;
			if (SyCount % 3 == 0)
			{
				SyIndex++;
				if (SyIndex > 27)
				{
					SyAtk = false;
					SyAtk2 = true;
					SyIndex = 0;
				}
				SyCount = 0;
			}
			IMAGEMANAGER->findImage("Syattack")->frameRender(getMemDC(), 768, 0, SyIndex, 0);
		}
		if (SyAtk2 == true)
		{
			SyCount2++;
			if (SyCount2 % 3 == 0)
			{
				SyIndex2++;

				if (SyIndex2 > 27)
				{
					SyAtk2 = false;
					SyAtk3 = true;
					SyIndex2 = 0;
				}
				SyCount2 = 0;
			}

			IMAGEMANAGER->findImage("Syattack2")->frameRender(getMemDC(), 768, 0, SyIndex2, 0);
		}

		if (SyAtk3 == true)
		{
			SyCount3++;
			if (SyCount3 % 3 == 0)
			{
				SyIndex3++;

				if (SyIndex3 > 27)
				{
					SyAtk3 = false;
					SyAtk4 = true;
					SyIndex3 = 0;
				}
				SyCount3 = 0;
			}

			IMAGEMANAGER->findImage("Syattack3")->frameRender(getMemDC(), 768, 0, SyIndex3, 0);
		}

		if (SyAtk4 == true)
		{
			SyCount4++;
			if (SyCount4 % 3 == 0)
			{
				SyIndex4++;

				if (SyIndex4 > 27)
				{
					SyAtk4 = false;
					SyAtk5 = true;
					SyIndex4 = 0;
				}
				SyCount4 = 0;
			}

			IMAGEMANAGER->findImage("Syattack4")->frameRender(getMemDC(), 768, 0, SyIndex4, 0);
		}

		if (SyAtk5 == true)
		{
			SyCount5++;

			if (SyCount5 % 3 == 0)
			{
				SyIndex5++;

				if (SyIndex5 > 13)
				{
					SyAtk5 = false;

					if (Camerachange == false)
					{
						_enemy->setHit(true);
					}
					if (luciaChange == true)
					{
						_enemy->setHit(true);
					}

					SyIndex5 = 0;
				}
				SyCount5 = 0;
			}
			IMAGEMANAGER->findImage("Syattack5")->frameRender(getMemDC(), 768, 0, SyIndex5, 0);


			if (_enemy->getHit() == true)
			{
				Hitcount++;

				for (int i = 0; i < 10; ++i)
				{
					//if ((alphMgcPointX != enemyX && alphMgcPointY != enemyY) && (alphAtkPointX != enemyX && alphAtkPointY != enemyY))// && (luciaAtkPointX != enemyX && luciaAtkPointY != enemyY) && (luciaMgcPointX != enemyX && luciaMgcPointY != enemyY))
					{
						if (SynergeDmg % 10 == i)
						{
							IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(enemyX, enemyY)->getPos() - _camera->getCameraX() + 20, _battle->getclassTile(enemyX, enemyY)->getPosY() - 60 - _camera->getCameraY(), i, 0);
						}

						if ((SynergeDmg / 10) % 10 == i)
						{
							IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(enemyX, enemyY)->getPos() - _camera->getCameraX(), _battle->getclassTile(enemyX, enemyY)->getPosY() - 60 - _camera->getCameraY(), i, 0);
						}

						if ((SynergeDmg / 100) % 10 == i)
						{
							IMAGEMANAGER->findImage("number")->frameRender(getMemDC(), _battle->getclassTile(enemyX, enemyY)->getPos() - _camera->getCameraX() - 20, _battle->getclassTile(enemyX, enemyY)->getPosY() - 60 - _camera->getCameraY(), i, 0);
						}
					}
				}
				if (Hitcount < 2)
				{
					_enemyHp -= SynergeDmg;
					_enemy->setCurrentHp(_enemy->getCurrentHp() - SynergeDmg);
				}
			}
		}
}



