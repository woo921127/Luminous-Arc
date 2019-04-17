#pragma once
#include "gameNode.h"
#include "MapNode.h"
//Ÿ�� �Ӽ�
enum ATTRIBUTE
{
	ATTR_NONE = 0x00000000UL,
	ATTR_NOMOVE = 0x00000001UL
};

//���� �̹��� Ű�� �迭 ��ȣ
typedef enum TERRAIN_ARRAY_NUM
{
	TERNUM_NONE,
	TERNUM_TILE1,
	TERNUM_COUNT


}TERNUM;
//���� �̹��� Ű��
static string _terrainImageKey[TERNUM_COUNT] = { "none","tile1" };


//������Ʈ �̹��� Ű�� �迭 ��ȣ
typedef enum OBJECT_ARRAY_NUM
{
	OBJNUM_NONE,
	OBJNUM_OBJ1,
	OBJNUM_COUNT


}OBJNUM;
//������Ʈ �̹��� Ű��
static string _objectImageKey[OBJNUM_COUNT] = { "none","obj1" };

typedef class astarTileNum
{
public:
	enum ASTAR_NODE_TYPE
	{
		EMPTY = 0,
		BLOCK,
		START,
		DEST
	};

	int index = -1;
	int	row = -1;
	int	col = -1;
	int parentIndex = -1;
	int zLevel = 0;

	float f = 0.0f;
	float g = 0.0f;
	float h = 0.0f;

	ASTAR_NODE_TYPE nodeType = EMPTY;

}ASTARTILENUM;


typedef class tileNode : public gameNode
{
private:
	image* terrainImage;		//���� �̹���
	TERNUM terrainArrayNum;		//���� �̹��� Ű�� �迭 ��ȣ
	int FrameX;			//���� ������ X
	int FrameY;			//���� ������ Y
	image* objectImage;			//������Ʈ �̹���
	OBJNUM objectArrayNum;		//������Ʈ �̹��� Ű�� �迭 ��ȣ
	int objectFrameX;			//������Ʈ ������ X
	int objectFrameY;			//������Ʈ ������ Y
	DWORD attribute;			//Ÿ�� �Ӽ�
	int zLevel;					//Z���� ũ��
	POINTFLOAT Pos;
	int selectTile;
	int saveNumX, saveNumY;
	int tileXNum, tileYNum;

public:
	//������
	tileNode() :
		terrainImage(nullptr),
		terrainArrayNum(TERNUM_NONE), FrameX(NULL), FrameY(NULL),
		objectImage(nullptr),
		objectArrayNum(OBJNUM_NONE), objectFrameX(NULL), objectFrameY(NULL),
		attribute(ATTR_NONE),
		zLevel(NULL) {};
	tileNode(const tileNode& tile) :
		terrainImage(tile.terrainImage),
		terrainArrayNum(tile.terrainArrayNum), FrameX(tile.FrameX), FrameY(tile.FrameY),
		objectImage(tile.objectImage),
		objectArrayNum(tile.objectArrayNum), objectFrameX(tile.objectFrameX), objectFrameY(tile.objectFrameY),
		attribute(tile.attribute),
		zLevel(NULL) {};
	~tileNode() {};
//========= Ÿ�� ������ ���� ============//

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

	int getSelectTile() { return selectTile; }
	void setSelectTile(int z) { selectTile = z; }

	TERNUM getTerrain() { return terrainArrayNum; }
	void setTerrain(TERNUM z) { terrainArrayNum = z; }

	int getsaveNumX() { return saveNumX; }
	void setsaveNumX(int z) { saveNumX = z; }

	int getsaveNumY() { return saveNumY; }
	void setsaveNumY(int z) { saveNumY = z; }

	int gettileXNum() { return tileXNum; }
	void settileXNum(int z) { tileXNum = z; }

	int gettileYNum() { return tileYNum; }
	void settileYNum(int z) { tileYNum = z; }

	//�ʱ�ȭ
	HRESULT init()
	{
		terrainImage = nullptr;
		terrainArrayNum = TERNUM_NONE;
		FrameX = NULL;
		FrameY = NULL;
		objectImage = nullptr;
		objectArrayNum = OBJNUM_NONE;
		objectFrameX = NULL;
		objectFrameY = NULL;
		attribute = ATTR_NONE;
		zLevel = NULL;
		selectTile = NULL;
		return S_OK;
	}

	void rende1r();

	void render()
	{
		terrainImage->frameRender(getMemDC(), 100, 100, 16, 1);
		Rectangle(getMemDC(), 1300, 300, 500, 500);
	}
	//----------------------------------------------------
	//------------------O P E R A T O R-------------------
	//----------------------------------------------------
	tileNode& operator = (const tileNode& tile)
	{
		this->terrainImage = tile.terrainImage;
		this->terrainArrayNum = tile.terrainArrayNum;
		this->FrameX = tile.FrameX;
		this->FrameY = tile.FrameY;
		this->objectImage = tile.objectImage;
		this->objectArrayNum = tile.objectArrayNum;
		this->objectFrameX = tile.objectFrameX;
		this->objectFrameY = tile.objectFrameY;
		this->attribute = tile.attribute;
		return *this;
	}
	bool operator == (const tileNode& tile)
	{
		if (this->terrainImage == tile.terrainImage			&&
			this->terrainArrayNum == tile.terrainArrayNum	&&
			this->FrameX == tile.FrameX		&&
			this->FrameY == tile.FrameY		&&
			this->objectImage == tile.objectImage			&&
			this->objectArrayNum == tile.objectArrayNum		&&
			this->objectFrameX == tile.objectFrameX			&&
			this->objectFrameY == tile.objectFrameY			&&
			this->attribute == tile.attribute)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator != (const tileNode& tile)
	{
		if (this->terrainImage == tile.terrainImage			&&
			this->terrainArrayNum == tile.terrainArrayNum	&&
			this->FrameX == tile.FrameX		&&
			this->FrameY == tile.FrameY		&&
			this->objectImage == tile.objectImage			&&
			this->objectArrayNum == tile.objectArrayNum		&&
			this->objectFrameX == tile.objectFrameX			&&
			this->objectFrameY == tile.objectFrameY			&&
			this->attribute == tile.attribute)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}ISOTILE;