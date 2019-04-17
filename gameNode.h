#pragma once
#include "image.h"

//백버퍼 전역 선언
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

static image* _backBuffer1 = IMAGEMANAGER->addImage("background", 800, WINSIZEY);


static image* _backBuffer2 = IMAGEMANAGER->addImage("Gameground", 768, 768);

class gameNode
{
protected:
	int ZorderY;

private:
	HDC _hdc;
	//매니저를 이닛할껀지 여부
	bool _managerInit;



public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(float cameraX, float cameraY);

	void setWindowsSize(int x, int y, int width, int height);
	void fileDelete();
	void deleteFile(const char* fileAddress);
	void fileReset();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	
	image* getBackBuffer() { return _backBuffer; }
	image* getBackBuffer1() { return _backBuffer1; }
	image* getBackBuffer2() { return _backBuffer2; }


	//DC 접근자
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	int getZorderY() { return ZorderY; }
	void setZorderY(int z) { ZorderY = z; }
};

