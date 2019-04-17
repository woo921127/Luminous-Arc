#include "stdafx.h"
#include "gameNode.h"
#pragma warning(disable:4996)

gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TXTDATA->init();
		TIMEMANAGER->init();
		EFFECTMANAGER->init();
		SOUNDMANAGER->init();
		SCENEMANAGER->init();
		KEYANIMANAGER->init();
		INIDATA->init();
		ZORDER->init();
		ASTAR->init();
		
	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);

		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		TXTDATA->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		INIDATA->release();
		INIDATA->releaseSingleton();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		KEYANIMANAGER->release();
		KEYANIMANAGER->releaseSingleton();

		ZORDER->Release();
		ZORDER->releaseSingleton();

		ASTAR->release();
		ASTAR->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	KEYMANAGER->update();
	SOUNDMANAGER->update();
}

void gameNode::render()
{

}

void gameNode::render(float cameraX, float cameraY)
{
}

void gameNode::setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	//���������� Ŭ���̾�Ʈ ���� ũ�� ������ �Ѵ�
	SetWindowPos(_hWnd, NULL, x, y,
		(winRect.right - winRect.left),
		(winRect.bottom - winRect.top),
		SWP_NOZORDER | SWP_NOMOVE);
}

void gameNode::fileDelete()
{
	//deleteFile("saveFile/introDungeon.txt");
	deleteFile("saveFile/inventory.txt");
	deleteFile("saveFile/�÷��̾�.txt");
	deleteFile("saveFile/playerScene.txt");
	deleteFile("saveFile/UiSave.txt");
}

void gameNode::deleteFile(const char * fileAddress)
{
	HANDLE file;
	DWORD read;

	char str[128];
	file = CreateFile(fileAddress, GENERIC_WRITE, NULL, NULL,
		TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	CloseHandle(file);
}

void gameNode::fileReset()
{
	bool _twice;
	_twice = false;

	char temp[128];

	vector<string> vStr;

	vStr.push_back(itoa((int)_twice, temp, 10));

	TXTDATA->txtSave("saveFile/introDungeon.txt", vStr);
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;		
	HDC			hdc;	

	switch (iMessage)
	{
		case WM_CREATE:

		break;
		
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));
		break;

		case WM_DESTROY:
			fileDelete();
			fileReset();
			PostQuitMessage(0);
		return 0;
	}


	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
