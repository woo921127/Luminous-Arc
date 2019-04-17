#include "stdafx.h"
#include "isoMetricScene.h"


isoMetricScene::isoMetricScene()
{
}


isoMetricScene::~isoMetricScene()
{

}

HRESULT isoMetricScene::init()
{

	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	IMAGEMANAGER->addFrameImage("isoZtile", "Tile\\Tile.bmp", 768, 256, 6, 4, true, MAGENTA);
	
	IMAGEMANAGER->findImage("back");
	_image = IMAGEMANAGER->findImage("isoZtile");

	SOUNDMANAGER->play("MapToolBGM", 1);

	_currentTool = TOOL_CURSOR;
	//_saveCheckX = 0;
	//_saveCheckY = 0;
	
	_isMultipleSelection = false;
	_isShift = false;

	_camera = new camera;
	_camera->init(800, 800, 6000, 6000);

	
	ClickMouse = false;

	ptmouse2.x = 0;
	ptmouse2.y = 0;

	view.x = 2000;
	view.y = 0;

	viewRc = RectMake(view.x, view.y, 5, 5);

	//int size = sizeof(_tileMap);
	//memset(_tileMap, 0, size);



	drawVecTile();
	for (int i = 0; i < 2; ++i)
	{
		saveload[i] = RectMake(1000 + (i * 150), 550, 119, 49);
	}

	return S_OK;
}

void isoMetricScene::release()
{

}

void isoMetricScene::update()
{

	
	//useTool();
	
	_camera->update(view.x, view.y);


	//카메라 무브//
	viewMove();
	//=========//
	
	setMap();

	
	ptmouse2.x = _ptMouse.x + _camera->getCameraX();
	ptmouse2.y = _ptMouse.y + _camera->getCameraY();

	mapSize();

	viewRc = RectMake(view.x - _camera->getCameraX(), view.y - _camera->getCameraY(), 20, 20);

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		tilenum--;
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		tilenum++;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&saveload[0], _ptMouse))
		{
			classSave();
			//save();
		}

		if (PtInRect(&saveload[1], _ptMouse))
		{
			classLoad();
			//load();
		}
	}

	//========================= iso 키핑 검출 =================================//

	tileXNum = ((ptmouse2.x - INIT_X) + (ptmouse2.y - INIT_Y) * 2) / 128;
	tileYNum = -1;
	if ((ptmouse2.y - INIT_Y) * 2 - (ptmouse2.x - INIT_X) > 0)
	{
		tileYNum = (2 * (ptmouse2.y - INIT_Y) - (ptmouse2.x - INIT_X)) / 128;
	}
	if (tileYNum <= -1) return;
	//=========================================================================//





}

void isoMetricScene::render()
{
	PatBlt(IMAGEMANAGER->findImage("background")->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	
	IMAGEMANAGER->render("back", getMemDC());

	drawTileMap2();

	//Rectangle(IMAGEMANAGER->findImage("background")->getMemDC(), viewRc);


	if (tilenum == 0)
	{
		IMAGEMANAGER->render("isoZtile", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("isoZtile")->GetWidth(), 0);
	}

	else if (tilenum == 1)
	{
		IMAGEMANAGER->render("isoZtile1", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("isoZtile1")->GetWidth(), 0);
	}

	//sprintf_s(str, "마지막타일 x : %d   마지막타일 y : %d", _isoBox.x, _isoBox.y);
	//TextOut(getMemDC(), 1300, 550, str, strlen(str));

	//for (int i = 0; i < _isoMap.size(); ++i)
	//{
	//	for (int j = 0; j < _isoMap[i].size(); ++j)
	//	{
	//	sprintf_s(str, "저장 : %d %d ", _isoMap[j][i]->getsaveNumX(), _isoMap[j][i]->getsaveNumY());
	//
	//	}
	//	//TextOut(getMemDC(), 1300, 600, str, strlen(str));
	//}
		//sprintf_s(str, "저장 : %d %d ",saveNumX,saveNumY);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		sprintf_s(str, "마우스 : %d %d ", tileXNum, tileYNum);
		TextOut(getMemDC(), 1300, 650, str, strlen(str));
	}
	//for (int i = 0; i < 2; ++i)
	//{
	//	Rectangle(getMemDC(), saveload[i]);
	//}

	IMAGEMANAGER->findImage("save")->render(getMemDC(), saveload[0].left, saveload[0].top);

	IMAGEMANAGER->findImage("load")->render(getMemDC(), saveload[1].left, saveload[1].top);

	IMAGEMANAGER->render("background", getMemDC(), 0, 0, 0, 0, 1000, WINSIZEY);
}
//타일맵 그려주는 함수
void isoMetricScene::drawTileMap2()
{
	{

		if (saveNumY >= TILEY) saveNumY = 0;
		if (saveNumX >= TILEX) saveNumX = 0;

		Tile* _tile = _isoMap[saveNumY][saveNumX];

		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8))
		{
			if (_tile->getZlevel() < 10)
			{
				_tile->setZlevel(_tile->getZlevel() + 1);
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2))
		{
			if (_tile->getZlevel() > 0)
			{
				_tile->setZlevel(_tile->getZlevel() - 1);
			}
		}
	}

	mapZtile();

//=================================타일맵쪽===========================================//
	if (tilenum == 0)
	{
		for (int i = 0; i < TrTileY; ++i)
		{
			for (int j = 0; j < TrTileX; ++j)
			{
				_isoSetting[i * TrTileX + j].isoX = j;
				_isoSetting[i * TrTileX + j].isoY = i;

				SetRect(&_isoSetting[i * TrTileX + j].isoRc,
					(WINSIZEX - IMAGEMANAGER->findImage("isoZtile")->GetWidth()) + j * CELL_WIDTH,
					i * CELL_HEIGHT,
					(WINSIZEX - IMAGEMANAGER->findImage("isoZtile")->GetWidth()) + j * CELL_WIDTH + CELL_WIDTH,
					i * CELL_HEIGHT + CELL_HEIGHT);
			}
		}
	}
	else if(tilenum  == 1)
	{
		for (int i = 0; i < TrTileY; ++i)
		{
			for (int j = 0; j < TrTileX; ++j)
			{
				_isoSetting[i * TrTileX + j].isoX = j;
				_isoSetting[i * TrTileX + j].isoY = i;

				SetRect(&_isoSetting[i * TrTileX + j].isoRc,
					(WINSIZEX - IMAGEMANAGER->findImage("isoZtile1")->GetWidth()) + j * CELL_WIDTH,
					i * 96,
					(WINSIZEX - IMAGEMANAGER->findImage("isoZtile1")->GetWidth()) + j * CELL_WIDTH + CELL_WIDTH,
					i * 96 + 96);
			}
		}
	}
}

void isoMetricScene::drawVecTile()
{

	TILEX = 12;
	TILEY = 12;

	for (int i = 0; i < TILEY; ++i)
	{
		vector<Tile*> _vTile;
		vector<bool> vCheck;
		for (int j = 0; j < TILEX; ++j)
		{
			Tile* _Tile = new Tile;

			_Tile->setSelectTile(0);
			_Tile->setFrameX(0);
			_Tile->setFrameY(5);
			_Tile->setTerrain(terrainSelect(_Tile->getFrameX(), _Tile->getFrameY()));
			//_Tile->setPos({centerX, centerY});
			_Tile->setPosX(centerX);
			_Tile->setPosY(centerY);
			//_Tile->selectTile = 0;
			//_Tile->FrameX = 0;
			//_Tile->FrameY = 5;
			//_Tile->objFrameX = 0;
			//_Tile->objFrameY = 0;
			//_Tile->terrain = terrainSelect(_Tile->FrameX, _Tile->FrameY);
			//_Tile->obj = OBJ_NONE;
			//_Tile->Pos.x = centerX;
			//_Tile->Pos.y = centerY;
		
			
			_vTile.push_back(_Tile);
			if (i == 0 && j == 0)
			{
				vCheck.push_back(false);
			}
			else
				vCheck.push_back(false);
		}
		_isoMap.push_back(_vTile);
		_check.push_back(vCheck);
	}
}

//마름모 그려주는 함수
void isoMetricScene::drawRhombus(int left, int top)
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

	Polygon(IMAGEMANAGER->findImage("background")->getMemDC(), p, 4);

}

void isoMetricScene::rhombusIn()
{
	

	if (_isShift)
	{
		RECT rc2;
		if (_savePoint.x <= _ptMouse.x && _savePoint.y <= _ptMouse.y)
		{
			rc2 = RectMake(_savePoint.x, _savePoint.y, _ptMouse.x, _ptMouse.y);
		}
		else if (_savePoint.x > _ptMouse.x && _savePoint.y <= _ptMouse.y)
		{
			rc2 = RectMake(_ptMouse.x, _savePoint.y, _savePoint.x, _ptMouse.y);
		}
		else if (_savePoint.x <= _ptMouse.x && _savePoint.y > _ptMouse.y)
		{
			rc2 = RectMake(_savePoint.x, _ptMouse.y, _ptMouse.x, _savePoint.y);
		}
		else if (_savePoint.x > _ptMouse.x && _savePoint.y > _ptMouse.y)
		{
			rc2 = RectMake(_ptMouse.x, _ptMouse.y, _savePoint.x, _savePoint.y);
		}

		POINT _cameraTum;
		_cameraTum.x = _camera->getCameraX() - _saveCamera.x;
		_cameraTum.y = _camera->getCameraY() - _saveCamera.y;


		rc2 = { _savePoint.x - _cameraTum.x, _savePoint.y - _cameraTum.y , _ptMouse.x , _ptMouse.y };

		HPEN myPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
		HPEN oldPen = (HPEN)SelectObject(IMAGEMANAGER->findImage("background")->getMemDC(), myPen);
		//Rectangle(IMAGEMANAGER->findImage("background")->getMemDC(), rc.left,rc.top,rc.right,rc.bottom);

		MoveToEx(IMAGEMANAGER->findImage("background")->getMemDC(), rc2.left, rc2.top, NULL);

		LineTo(IMAGEMANAGER->findImage("background")->getMemDC(), rc2.right, rc2.top);
		LineTo(IMAGEMANAGER->findImage("background")->getMemDC(), rc2.right, rc2.bottom);
		LineTo(IMAGEMANAGER->findImage("background")->getMemDC(), rc2.left, rc2.bottom);
		LineTo(IMAGEMANAGER->findImage("background")->getMemDC(), rc2.left, rc2.top);

		DeleteObject(SelectObject(IMAGEMANAGER->findImage("background")->getMemDC(), oldPen));
	}
}

void isoMetricScene::setMap()
{
	Click = CTRL_TERRAINDRAW;

	if ((_ptMouse.x <= 1000) && tileXNum < TILEX && tileYNum < TILEY)
	{

		Tile* pTile = _isoMap[tileYNum][tileXNum];
		
		if (!_isShift)
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				ClickMouse = true;
				if (Click == CTRL_TERRAINDRAW && ClickMouse == true)
				{
					
					pTile->setFrameX(_isoBox.x);
					pTile->setFrameY(_isoBox.y);
					pTile->setSelectTile(tilenum);
					pTile->setTerrain(terrainSelect(_isoBox.x, _isoBox.y));
					saveNumX = tileXNum;
					saveNumY = tileYNum;
					
					//pTile->setsaveNumX(tileXNum);
					//pTile->setsaveNumY(tileYNum);

					
				}
				else if (Click == CTRL_OBJDRAW)
				{
					
				}

				else if (Click == CTRL_ERASER)
				{
					//pTile->objFrameX = NULL;
					//pTile->objFrameY = NULL;
					//pTile->obj = OBJ_NONE;
				}
				InvalidateRect(_hWnd, NULL, false);
				//break;	
			}
		}
	}
}

void isoMetricScene::viewMove()
{
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (view.y > 0)
		{
			view.y -= 20;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		view.y += 20;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		view.x += 20;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (view.x > 0)
		{
			view.x -= 20;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		for (int i = 0; i < TrTileX * TrTileY; ++i)
		{
			if (PtInRect(&_isoSetting[i].isoRc, _ptMouse))
			{
				_isoBox.x = _isoSetting[i].isoX;
				_isoBox.y = _isoSetting[i].isoY;
			}
		}
	}

	
}

void isoMetricScene::mapSize()
{
	//사이즈 줄이기  

	if (KEYMANAGER->isOnceKeyDown('Q') && TILEX > 1)
	{
		//saveNumY, saveNumX = 0;

		for (int i = 0; i < TILEY; i++)
		{
			Tile* map = _isoMap[i].back();

			_isoMap[i].pop_back();
			
			//SAFE_DELETE(map);
		}
		TILEX--;
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		//사이즈 늘이기
	
		for (int i = 0; i < TILEY; ++i)
		{
			Tile* _tile = new Tile;
			_tile->setSelectTile(0);
			_tile->setFrameX(0);
			_tile->setFrameY(5);
			_tile->setTerrain(terrainSelect(_tile->getFrameX(), _tile->getFrameY()));
			//_tile->setPos({ centerX,centerY });
			_tile->setPosX(centerX);
			_tile->setPosY(centerY);
			_tile->setZlevel(0);
			//_tile->selectTile = 0;
			//_tile->FrameX = 0;
			//_tile->FrameY = 5;
			//_tile->objFrameX = 0;
			//_tile->objFrameY = 0;
			//_tile->terrain = terrainSelect(_tile->FrameX, _tile->FrameY);
			//_tile->obj = OBJ_NONE;
			//_tile->Pos.x = centerX;
			//_tile->Pos.y = centerY;
			//_tile->zLevel = 0;
			_isoMap[i].push_back(_tile);
		}
		TILEX++;
	
	}


	// 사이즈 줄이기
	if (KEYMANAGER->isOnceKeyDown('E') && TILEY > 1)
	{
	//	saveNumY, saveNumX = 0;

			for (int i = 0; i < TILEX; i++)
			{
				//	delete _vvMap.back()[i];
				_isoMap.back()[i] = nullptr;
			}
			_isoMap.pop_back();
			TILEY--;
		
	}
	// 사이즈 늘리기
	if(KEYMANAGER->isOnceKeyDown('R'))
	{
			vector<Tile*> vTile;
			for (int i = 0; i < TILEX; i++)
			{
				Tile* _tile = new Tile;

				_tile->setSelectTile(0);
				_tile->setFrameX(0);
				_tile->setFrameY(5);
				_tile->setTerrain(terrainSelect(_tile->getFrameX(), _tile->getFrameY()));
				//_tile->setPos({ centerX,centerY });
				_tile->setPosX(centerX);
				_tile->setPosY(centerY);
				_tile->setZlevel(0);
				
				//_tile->selectTile = 0;
				//_tile->FrameX = 0;
				//_tile->FrameY = 5;
				//_tile->objFrameX = 0;
				//_tile->objFrameY = 0;
				//_tile->terrain = terrainSelect(_tile->FrameX, _tile->FrameY);
				//_tile->obj = OBJ_NONE;
				//_tile->Pos.x = centerX;
				//_tile->Pos.y = centerY;
				//_tile->zLevel = 0;
				vTile.push_back(_tile);
			}
			_isoMap.push_back(vTile);
			TILEY++;
		
	}
	
}

void isoMetricScene::save()
{
	HANDLE file2;
	DWORD save2;
	char mapSize[128];
	sprintf_s(mapSize, "%d,%d", TILEX, TILEY);
	file2 = CreateFile("saveFile\\luminous1Size.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file2, mapSize, strlen(mapSize), &save2, NULL);

	CloseHandle(file2);

	Tile* _tiles = new Tile[TILEX * TILEY];
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[j + i * TILEX] = *_isoMap[i][j];
		}
	}

	HANDLE file;
	DWORD save;

	file = CreateFile("saveFile\\luminous1Save.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(Tile) * TILEX * TILEY, &save, NULL);

	CloseHandle(file);

	//delete[] _tiles;
}

void isoMetricScene::load()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//SAFE_DELETE(_vvMap[i][j]);
		}
		_isoMap[i].clear();
	}
	_isoMap.clear();

	HANDLE file2;
	DWORD read2;
	char mapSize[128];

	file2 = CreateFile("saveFile\\luminous1Size.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file2, mapSize, 128, &read2, NULL);
	CloseHandle(file2);

	string sizeX, sizeY;
	bool x = true;
	for (int i = 0; i < strlen(mapSize); i++)
	{
		if (mapSize[i] == ',')
		{
			x = false;
			continue;
		}
		if (mapSize[i] == NULL) break;
		if (x)
		{
			sizeX += mapSize[i];
		}
		else
		{
			sizeY += mapSize[i];
		}
	}


	TILEX = stoi(sizeX);
	TILEY = stoi(sizeY);
	_isoMap.resize(TILEY);



	for (int i = 0; i < TILEY; i++)
	{
		_isoMap[i].resize(TILEX);
	}



	Tile* _tiles = new Tile[TILEX * TILEY];
	HANDLE file;
	DWORD read;

	file = CreateFile("saveFile\\luminous1Save.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(Tile) * TILEX * TILEY, &read, NULL);


	CloseHandle(file);

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_isoMap[i][j] = &_tiles[j + i * TILEX];		
		}
	}

}

void isoMetricScene::classSave()
{
	HANDLE file;
	DWORD write;

	char fileName[50] = "saveFile\\luminous2Size";

	strcat_s(fileName, sizeof(fileName), saveNum);
	strcat_s(fileName, sizeof(fileName), ".map");

	char save[500000] = {};
	char tmp[1000] = {};
	char token[10000] = {};

	itoa(TILEX, tmp, 10);
	strcat_s(save, sizeof(save), tmp);
	strcat_s(save, sizeof(save), "]");

	itoa(TILEY, tmp, 10);
	strcat_s(save, sizeof(save), tmp);
	strcat_s(save, sizeof(save), "]");

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//프레임x번호
			itoa(_isoMap[i][j]->getFrameX(), tmp, 10);
			strcat_s(token, sizeof(token), tmp);
			strcat_s(token, sizeof(token), "/");	

			//프레임y번호
			itoa(_isoMap[i][j]->getFrameY(), tmp, 10);
			strcat_s(token, sizeof(token), tmp);
			strcat_s(token, sizeof(token), "/");

			//z축 레벨
			itoa(_isoMap[i][j]->getZlevel(), tmp, 10);
			strcat_s(token, sizeof(token), tmp);
			strcat_s(token, sizeof(token), "/");	
			
			//포인트 x
			itoa(_isoMap[i][j]->getPosX().x, tmp, 10);
			strcat_s(token, sizeof(token), tmp);
			strcat_s(token, sizeof(token), "/");	
			//포인트 y
			itoa(_isoMap[i][j]->getPosX().y, tmp, 10);
			strcat_s(token, sizeof(token), tmp);
			strcat_s(token, sizeof(token), "/");	

			//포인트 x(int형)
			itoa(_isoMap[i][j]->getPos(), tmp, 10);
			strcat_s(token, sizeof(token), tmp);
			strcat_s(token, sizeof(token), "/");

			//포인트 y(int형)
			itoa(_isoMap[i][j]->getPosY(), tmp, 10);
			strcat_s(token, sizeof(token), tmp);
			strcat_s(token, sizeof(token), "/");

			////지형
			itoa(_isoMap[i][j]->getTerrain(), tmp, 10);
			strcat_s(token, sizeof(token), tmp);
			strcat_s(token, sizeof(token), "/");	
			//선택타일지형
			itoa(_isoMap[i][j]->getSelectTile(), tmp, 10);
			strcat_s(token, sizeof(token), tmp);
			strcat_s(token, sizeof(token), "/");	

			strcat_s(save, sizeof(save), token);

			for (int i = 0; i < 10000; i++)
			{
				token[i] = '\0';
			}
		}
	}

	file = CreateFile(fileName, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, save, sizeof(save), &write, NULL);
	CloseHandle(file);
}

void isoMetricScene::classLoad()
{
	for (int i = 0; i < TILEY; i++)
	{
		_isoMap[i].clear();
		for (int j = 0; j < TILEX; j++)
		{
			//delete _isoMap[i][j];
			//_isoMap[i][j] = nullptr;
		}
	}
	_isoMap.clear();

	HANDLE file;
	DWORD read;

	char load[5000000] = {};
	char fileName[50] = "saveFile\\luminous2Size";
	char* token;			
	char* context;			
	const char* seperator = "/";	
	int tmpInt;

	strcat_s(fileName, sizeof(fileName), saveNum);
	strcat_s(fileName, sizeof(fileName), ".map");

	file = CreateFile(fileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, load, sizeof(load), &read, NULL);
	CloseHandle(file);

	token = strtok_s(load, "]", &context);
	tmpInt = atoi(token);
	TILEX = tmpInt;
	token = strtok_s(NULL, "]", &context);
	tmpInt = atoi(token);
	TILEY = tmpInt;

	

	_isoMap.resize(TILEY);

	for (int i = 0; i < TILEY; ++i)
	{
		_isoMap[i].resize(TILEX);
	}

//=========여기까지 사이즈 불러오기================//


//======= 저장내용 불러오기============================//

	

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			Tile* tmpTile = new Tile;
			
			tmpTile->setimage(_image);
	
			int FrameX;
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			FrameX = tmpInt;
			tmpTile->setFrameX(FrameX);

			int FrameY;
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			FrameY = tmpInt;
			tmpTile->setFrameY(FrameY);
		
			int ZLevel;
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			ZLevel = tmpInt;
			tmpTile->setZlevel(ZLevel);

			POINTFLOAT pos;
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			pos.x = tmpInt;
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			pos.y = tmpInt;
			tmpTile->setPos({ pos.x,pos.y });

			int PosX;
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			PosX = tmpInt;
			tmpTile->setPosX(PosX);

			int PosY;
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			PosY = tmpInt;
			tmpTile->setPosY(PosY);

			int Terrain;
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			Terrain = tmpInt;
			tmpTile->setTerrain(terrainSelect(tmpTile->getFrameX(),tmpTile->getFrameY()));

			int selectTile;
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			selectTile = tmpInt;
			tmpTile->setSelectTile(selectTile);

			_isoMap[i][j] = tmpTile;
		}
		
	}
}

TERRAIN_ARRAY_NUM1 isoMetricScene::terrainSelect(int frameX, int frameY)
{
	return TERRAIN_ARRAY_NUM1();
}

OBJECT isoMetricScene::objSelect(int frameX, int frameY)
{
	return OBJECT();
}


void isoMetricScene::mapZtile()
{
	for (int i = 0; i < _isoMap.size(); i++)
	{
		for (int j = 0; j < _isoMap[i].size(); j++)
		{
			left = INIT_X + (j * RADIUS_WIDTH) - (i * RADIUS_WIDTH) - 64;
			top = INIT_Y + (j * RADIUS_HEIGHT) + (i * RADIUS_HEIGHT);

			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;

			//_isoMap[i][j]->setPos({ centerX,centerY });


			_isoMap[i][j]->setPosX(centerX);
			_isoMap[i][j]->setPosY(centerY);


			//_isoMap[i][j]->Pos.x = centerX;
			//_isoMap[i][j]->Pos.y = centerY;

			if (left - _camera->getCameraX() + 128 < 0) continue;
			if (left - _camera->getCameraX() > 800) continue;
			if (top - _camera->getCameraY() + 64 < 0) continue;
			if (top - _camera->getCameraY() > 800) continue;

			drawRhombus(left, top);


//====================================== 높이 올리기 ========================================//
			if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 0)
			{
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
			}
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 1)
			{
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32  + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 2);
			}	
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 2)
			{
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32  - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 2);
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 3);
			}	
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 3)
			{
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 2);
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 2) * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 3);
			}
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 4)
			{
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 2);
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 2) * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 3) * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 3);
			}
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 5)
			{
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 2);
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 2) * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 3) * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 4) * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 3);
			}

			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 6)
			{
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 2);
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 2) * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 3) * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 4) * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 5) * 32) + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), 3);
			}
			
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 7)
			{
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 2);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 2) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 3) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 4) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 5) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 6) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			}
			
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 8)
			{
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 2);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 2) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 3) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 4) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 5) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 6) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 7) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			}
			
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 9)
			{
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 2);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 2) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 3) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 4) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 5) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 6) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 7) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 8) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			}
			
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 10)
			{
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 2);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 2) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 3) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 4) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 5) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 6) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 7) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 8) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 9) * 32) + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			IMAGEMANAGER->frameRender("isoZtile", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
				(i + j) * 32 + INIT_Y - _camera->getCameraY(),
				_isoMap[i][j]->getFrameX(), 3);
			}
			
			
			else if (_isoMap[i][j]->getSelectTile() == 1 && _isoMap[i][j]->getZlevel() == 0)
			{
				IMAGEMANAGER->frameRender("isoZtile1", IMAGEMANAGER->findImage("background")->getMemDC(), (j - i) * 64 + INIT_X - 64 - _camera->getCameraX(),
					(i + j) * 32 + INIT_Y - _camera->getCameraY(),
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
			}
		}
	}

}

bool isoMetricScene::tileIndexInCheck(int x, int y)
{
	if (x >= TILEY || y >= TILEX || x < 0 || y < 0) return false;
	else return true;
}
