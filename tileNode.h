#pragma once
#include "gameNode.h"
#include "MapNode.h"
//타일 속성
enum ATTRIBUTE
{
	ATTR_NONE = 0x00000000UL,
	ATTR_NOMOVE = 0x00000001UL
};

//지형 이미지 키값 배열 번호
typedef enum TERRAIN_ARRAY_NUM
{
	TERNUM_NONE,
	TERNUM_TILE1,
	TERNUM_COUNT


}TERNUM;
//지형 이미지 키값
static string _terrainImageKey[TERNUM_COUNT] = { "none","tile1" };


//오브젝트 이미지 키값 배열 번호
typedef enum OBJECT_ARRAY_NUM
{
	OBJNUM_NONE,
	OBJNUM_OBJ1,
	OBJNUM_COUNT


}OBJNUM;
//오브젝트 이미지 키값
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
	image* terrainImage;		//지형 이미지
	TERNUM terrainArrayNum;		//지형 이미지 키값 배열 번호
	int FrameX;			//지형 프레임 X
	int FrameY;			//지형 프레임 Y
	image* objectImage;			//오브젝트 이미지
	OBJNUM objectArrayNum;		//오브젝트 이미지 키값 배열 번호
	int objectFrameX;			//오브젝트 프레임 X
	int objectFrameY;			//오브젝트 프레임 Y
	DWORD attribute;			//타일 속성
	int zLevel;					//Z축의 크기
	POINTFLOAT Pos;
	int selectTile;
	int saveNumX, saveNumY;
	int tileXNum, tileYNum;

public:
	//생성자
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
//========= 타일 접근자 설정 ============//

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

	//초기화
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