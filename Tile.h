#pragma once
#include "gameNode.h"
#include "MapNode.h"
#include "TileNode.h"
enum ATTRIBUTE1
{
	a,
	b
};


enum TERRAIN_ARRAY_NUM1
{
	c,
	d,
	e


};

enum OBJECT_ARRAY_NUM1
{
	f,
	g,
	h
};

class Tile : public gameNode
{
private:
	image* terrainImage;		//���� �̹���
	TERRAIN_ARRAY_NUM1 terrainArrayNum;		//���� �̹��� Ű�� �迭 ��ȣ
	int FrameX;			//���� ������ X
	int FrameY;			//���� ������ Y
	image* objectImage;			//������Ʈ �̹���
	OBJECT_ARRAY_NUM1 objectArrayNum;		//������Ʈ �̹��� Ű�� �迭 ��ȣ
	int objectFrameX;			//������Ʈ ������ X
	int objectFrameY;			//������Ʈ ������ Y
	DWORD attribute;			//Ÿ�� �Ӽ�
	int zLevel;					//Z���� ũ��
	POINTFLOAT Pos;
	POINTFLOAT Posidx;

	int posX;
	int posY;


	int selectTile;
	int saveNumX, saveNumY;
	int tileXNum, tileYNum;
	POINT imageNum;
	isoSetting _isoSetting[TrTileX * TrTileY];
	int TileCheck;

public:
	Tile();
	~Tile();


	HRESULT init();
	void render(float cameraX, float cameraY);
	void update();

	POINT getimgidx() { return imageNum; }
	void setimgidx(POINT a) { imageNum = a; }

	int getZlevel() { return zLevel; }
	void setZlevel(int z) { zLevel = z; }

	image* getimage() { return terrainImage; }
	void setimage(image* z) { terrainImage = z; }

	int getFrameX() { return FrameX; }
	void setFrameX(int z) { FrameX = z; }

	int getFrameY() { return FrameY; }
	void setFrameY(int z) { FrameY = z; }

	POINTFLOAT getPosX() { return Pos; }
	void setPos(POINTFLOAT a) { Pos = a; }

	POINTFLOAT getPosidx() { return Posidx; }
	void setPosidx(POINTFLOAT a);

	int getSelectTile() { return selectTile; }
	void setSelectTile(int z) { selectTile = z; }

	TERRAIN_ARRAY_NUM1 getTerrain() { return terrainArrayNum; }
	void setTerrain(TERRAIN_ARRAY_NUM1 z) { terrainArrayNum = z; }

	int getsaveNumX() { return saveNumX; }
	void setsaveNumX(int z) { saveNumX = z; }

	int getsaveNumY() { return saveNumY; }
	void setsaveNumY(int z) { saveNumY = z; }

	int gettileXNum() { return tileXNum; }
	void settileXNum(int z) { tileXNum = z; }

	int gettileYNum() { return tileYNum; }
	void settileYNum(int z) { tileYNum = z; }

	int getTileCheck() { return TileCheck; }
	void setTileCheck(int a);

	int getPos() { return posX; }
	void setPosX(int a) { posX = a; }

	int getPosY() { return posY; }
	void setPosY(int a) { posY = a; }

};
