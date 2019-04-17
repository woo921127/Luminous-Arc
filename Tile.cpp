#include "stdafx.h"
#include "Tile.h"


Tile::Tile()
{
}


Tile::~Tile()
{
}

HRESULT Tile::init()
{
	return S_OK;
}

void Tile::render(float cameraX, float cameraY)
{
	if (zLevel == 0)
	{
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 - cameraY, imageNum.x, 0);
	}
	else if (zLevel == 1)
	{
	terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 - cameraY, imageNum.x, 3);
	terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 2 - cameraY, imageNum.x, 0);
	}
	else if (zLevel == 2)
	{
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 2 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 3 - cameraY, imageNum.x, 0);
	
	}
	else if (zLevel == 3)
	{
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 2 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 3- cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 4 - cameraY, imageNum.x, 0);
	}
	else if (zLevel == 4)
	{
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 2 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 3 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 4 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 5 - cameraY, imageNum.x, 0);

	}
	else if (zLevel == 5)
	{
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 2 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 3 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 4 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 5 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 6 - cameraY, imageNum.x, 0);
	}
	else if (zLevel == 6)
	{
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 2 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 3 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 4 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 5 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 6 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 7 - cameraY, imageNum.x, 0);
	}
	else if (zLevel == 7)
	{
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 2 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 3 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 4 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 5 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 6 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 7 - cameraY, imageNum.x, 3);
		terrainImage->frameRender(getMemDC(), posX - 64 - cameraX, posY - 32 * 8 - cameraY, imageNum.x, 0);
	}
	
}

void Tile::update()
{
}

void Tile::setPosidx(POINTFLOAT a)
{
	//Posidx = a;
	//
	//posX = Posidx.x * CELL_WIDTH;
	//posY = Posidx.y * CELL_HEIGHT;

}

void Tile::setTileCheck(int a)
{
	//TileCheck = a;
	//
	//if (TileCheck == 1)
	//{
	//	terrainImage = IMAGEMANAGER->findImage("isoZtile");
	//}
}
