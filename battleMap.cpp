#include "stdafx.h"
#include "battleMap.h"
#include "Lucia.h"
#include "Alph.h"
#include "Enemy.h"
battleMap::battleMap()
{
}


battleMap::~battleMap()
{
}

HRESULT battleMap::init()
{
	_image = IMAGEMANAGER->findImage("isoZtile");
	IMAGEMANAGER->findImage("isoZtile1");
	//load();



	classLoad();
	return S_OK;
}

void battleMap::release()
{
}

void battleMap::update()
{

}

void battleMap::render(float cameraX, float cameraY)
{
	classZtile(cameraX, cameraY);
}

void battleMap::load()
{
	HANDLE file2;
	DWORD read2;
	char mapSize[128];

	file2 = CreateFile("saveFile\\luminousSize.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file2, mapSize, 128, &read2, NULL);


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
	_vvMap.resize(TILEY);


	for (int i = 0; i < TILEY; i++)
	{
		_vvMap[i].resize(TILEX);
	}

	iSoTile* _tiles = new iSoTile[TILEX * TILEY];
	HANDLE file;
	DWORD read;

	file = CreateFile("saveFile\\luminousSave.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(iSoTile) * TILEX * TILEY, &read, NULL);

	_attribute = new DWORD[TILEX * TILEY];

	memset(_attribute, 0, sizeof(DWORD)*TILEX*TILEY);

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_attribute[j + i * TILEX] = NULL;
			_vvMap[i][j] = &_tiles[j + i * TILEX];

			//if (_vvMap[i][j]->obj == OBJ_WALL) _attribute[j + i * TILEX] |= ATTR_UNMOVE;
			//if (_vvMap[i][j]->obj == OBJ_WATER) _attribute[j + i * TILEX] |= ATTR_UNMOVE;


		}
	}
	CloseHandle(file);
	CloseHandle(file2);

	
	
}

void battleMap::classLoad()
{
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
			tmpTile->setTerrain(terrainSelect(tmpTile->getFrameX(), tmpTile->getFrameY()));

			int selectTile;
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			selectTile = tmpInt;
			tmpTile->setSelectTile(selectTile);

			_isoMap[i][j] = tmpTile;
		
			if (_isoMap[i][j]->getZlevel() > 0)
			{
				ZORDER->InPutObj(_isoMap[i][j]);
				_isoMap[i][j]->setZorderY(_isoMap[i][j]->getPosY() - 32);
			}	
		}
	}
}

void battleMap::Ztile(float cameraX, float cameraY)
{
	for (int i = 0; i < _vvMap.size(); ++i)
	{
		for (int j = 0; j < _vvMap[i].size(); ++j)
		{

			left = INIT_X + (j * RADIUS_WIDTH) - (i * RADIUS_WIDTH) - 64;
			top = INIT_Y + (j * RADIUS_HEIGHT) + (i * RADIUS_HEIGHT);

			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;

			_vvMap[i][j]->Pos.x = centerX;
			_vvMap[i][j]->Pos.y = centerY;

			if (left - cameraX + 128 < 0) continue;
			if (left - cameraX > 1024) continue;
			if (top - cameraY + 64 < 0) continue;
			if (top - cameraY > 768 + 264) continue;
			
			{
				if (_vvMap[i][j]->selectTile == 0 && _vvMap[i][j]->zLevel == 0)
				{
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
				}
				else if (_vvMap[i][j]->selectTile == 0 && _vvMap[i][j]->zLevel == 1)
				{
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - (_vvMap[i][j]->zLevel * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 2);
				}
				else if (_vvMap[i][j]->selectTile == 0 && _vvMap[i][j]->zLevel == 2)
				{
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - (_vvMap[i][j]->zLevel * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 1) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 2);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
				}
				else if (_vvMap[i][j]->selectTile == 0 && _vvMap[i][j]->zLevel == 3)
				{
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - (_vvMap[i][j]->zLevel * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 1) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 2);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 2) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
				}
				else if (_vvMap[i][j]->selectTile == 0 && _vvMap[i][j]->zLevel == 4)
				{
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - (_vvMap[i][j]->zLevel * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 1) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 2);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 2) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 3) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
				}
				else if (_vvMap[i][j]->selectTile == 0 && _vvMap[i][j]->zLevel == 5)
				{
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - (_vvMap[i][j]->zLevel * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 1) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 2);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 2) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 3) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 4) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
				}

				else if (_vvMap[i][j]->selectTile == 0 && _vvMap[i][j]->zLevel == 6)
				{
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - (_vvMap[i][j]->zLevel * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 1) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 2);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 2) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 3) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 4) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 5) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
				}

				else if (_vvMap[i][j]->selectTile == 0 && _vvMap[i][j]->zLevel == 7)
				{
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - (_vvMap[i][j]->zLevel * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 1) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 2);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 2) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 3) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 4) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 5) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 6) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
				}

				else if (_vvMap[i][j]->selectTile == 0 && _vvMap[i][j]->zLevel == 8)
				{
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - (_vvMap[i][j]->zLevel * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 1) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 2);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 2) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 3) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 4) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 5) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 6) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 7) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
				}

				else if (_vvMap[i][j]->selectTile == 0 && _vvMap[i][j]->zLevel == 9)
				{
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - (_vvMap[i][j]->zLevel * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 1) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 2);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 2) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 3) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 4) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 5) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 6) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 7) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 8) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
				}

				else if (_vvMap[i][j]->selectTile == 0 && _vvMap[i][j]->zLevel == 10)
				{
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - (_vvMap[i][j]->zLevel * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 1) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 2);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 2) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 3) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 4) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 5) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 6) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 7) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 8) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 - ((_vvMap[i][j]->zLevel - 9) * 32) + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
					IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
						(i + j) * 32 + INIT_Y - cameraY,
						_vvMap[i][j]->FrameX, 3);
				}
			

			else if (_vvMap[i][j]->selectTile == 1 && _vvMap[i][j]->zLevel == 0)
			{
				IMAGEMANAGER->frameRender("isoZtile1", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 + INIT_Y - cameraY,
					_vvMap[i][j]->FrameX, _vvMap[i][j]->FrameY);
			}

		}


			//sprintf_s(str, "Z축 :%d", _vvMap[i][j]->zLevel);
			//TextOut(getMemDC(), centerX - 16 - cameraX, centerY - 16 - cameraY, str, strlen(str));
			//SetBkMode(getMemDC(), TRANSPARENT);
			//SetTextColor(getMemDC(), RGB(0, 0, 0));
		}
	}
}

void battleMap::classZtile(float cameraX, float cameraY)
{
	for (int i = 0; i < _isoMap.size(); i++)
	{
		for (int j = 0; j < _isoMap[i].size(); j++)
		{
			left = INIT_X + (j * RADIUS_WIDTH) - (i * RADIUS_WIDTH) - 64;
			top = INIT_Y + (j * RADIUS_HEIGHT) + (i * RADIUS_HEIGHT);

			centerX = left + RADIUS_WIDTH;
			centerY = top + RADIUS_HEIGHT;


			if (left - cameraX + 128 < 0) continue;
			if (left - cameraX > 1800) continue;
			if (top - cameraY + 64 < 0) continue;
			if (top - cameraY > 768 + 264) continue;

		

			//====================================== 높이 올리기 ========================================//
			if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 0)
			{
				IMAGEMANAGER->frameRender("isoZtile", getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
			}
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 1)
			{
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 2);
			}
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 2)
			{
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 2);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
			}
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 3)
			{
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 2);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 2) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
			}
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 4)
			{
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 2);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 2) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 3) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
			}
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 5)
			{
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 2);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 2) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 3) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 4) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
			}
			
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 6)
			{
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 2);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 2) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 3) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 4) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 5) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
			}
			
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 7)
			{
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 2);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 2) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 3) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 4) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 5) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 6) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
			}
			
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 8)
			{
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 2);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 2) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 3) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 4) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 5) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 6) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 7) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
			}
			
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 9)
			{
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 2);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 2) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 3) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 4) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 5) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 6) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 7) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 8) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
			}
			
			else if (_isoMap[i][j]->getSelectTile() == 0 && _isoMap[i][j]->getZlevel() == 10)
			{
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - (_isoMap[i][j]->getZlevel() * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 1) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 2);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 2) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 3) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 4) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 5) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 6) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 7) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 8) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 - ((_isoMap[i][j]->getZlevel() - 9) * 32) + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
				IMAGEMANAGER->frameRender("isoZtile",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), 3);
			}
			
			
			else if (_isoMap[i][j]->getSelectTile() == 1 && _isoMap[i][j]->getZlevel() == 0)
			{
				IMAGEMANAGER->frameRender("isoZtile1",  getMemDC(), (j - i) * 64 + INIT_X - 64 - cameraX,
					(i + j) * 32 + INIT_Y -cameraY,
					_isoMap[i][j]->getFrameX(), _isoMap[i][j]->getFrameY());
			}
	
			//char str[128];
			//
			//sprintf_s(str, "%d  :%d", i,j);
			//TextOut(getMemDC(), centerX - 16 - cameraX,centerY - 16 - cameraY, str, strlen(str));

		}
	}
	char str[128];
	sprintf_s(str, "Z축 :%d", ZorderY);
	TextOut(getMemDC(), 200, 300, str, strlen(str));
}

TERRAIN_ARRAY_NUM1 battleMap::terrainSelect(int frameX, int frameY)
{
	return TERRAIN_ARRAY_NUM1();
}

OBJECT battleMap::objSelect(int frameX, int frameY)
{
	return OBJECT();
}



