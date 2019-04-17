#include "stdafx.h"
#include "image.h"

//�����Ϸ� ���ñ� (�� ���̺귯�� ������ msImg32 ���̺귯��)
#pragma comment(lib, "msimg32.lib")

image::image()
	: _imageInfo(NULL), _fileName(NULL),
	_trans(FALSE), _transColor(RGB(0, 0, 0))
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ĺ��� ������.
	//���� + ġ���̴� �����ؼ� ����
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;	//<-- �̰� �� �� �����غ����� ������

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;



	if (_imageInfo->hBit == 0)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const DWORD resID, int width, int height, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ĺ��� ������.
	//���� + ġ���̴� �����ؼ� ����
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;	//<-- �̰� �� �� �����غ����� ������

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == 0)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	//�����̸��� ������ ������  �����
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �ʱ�ȭ �Ǿ����� ������ �����ض�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC������ �ϳ� ��������
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	//���ϰ�� �� �̸��� �޾ƿ´�
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//Ư��Į�� ���ܿ��θ� ����.
	_trans = trans;
	_transColor = transColor;

	//���ĺ��� ������.
	//���� + ġ���̴� �����ؼ� ����
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;	//<-- �̰� �� �� �����غ����� ������

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	//�����̸��� ������ ������  �����
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �ʱ�ȭ �Ǿ����� ������ �����ض�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC������ �ϳ� ��������
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	//���ϰ�� �� �̸��� �޾ƿ´�
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//Ư��Į�� ���ܿ��θ� ����.
	_trans = trans;
	_transColor = transColor;

	//���ĺ��� ������.
	//���� + ġ���̴� �����ؼ� ����
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;	//<-- �̰� �� �� �����غ����� ������

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//�����̸��� ������ ������  �����
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �ʱ�ȭ �Ǿ����� ������ �����ض�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC������ �ϳ� ��������
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	//���ϰ�� �� �̸��� �޾ƿ´�
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//Ư��Į�� ���ܿ��θ� ����.
	_trans = trans;
	_transColor = transColor;

	//���ĺ��� ������.
	//���� + ġ���̴� �����ؼ� ����
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;	//<-- �̰� �� �� �����غ����� ������

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//�����̸��� ������ ������  �����
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �ʱ�ȭ �Ǿ����� ������ �����ض�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC������ �ϳ� ��������
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	//���ϰ�� �� �̸��� �޾ƿ´�
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//Ư��Į�� ���ܿ��θ� ����.
	_trans = trans;
	_transColor = transColor;

	//���ĺ��� ������.
	//���� + ġ���̴� �����ؼ� ����
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;	//<-- �̰� �� �� �����غ����� ������

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::rotateInit(const char * fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;


	//���ĺ��� ����
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;
	//rotate

	int size;
	(width > height ? size = width : size = height);
	_rotateImage = new IMAGE_INFO;
	_rotateImage->loadType = LOAD_EMPTY;
	_rotateImage->resID = 0;
	_rotateImage->hMemDC = CreateCompatibleDC(hdc);
	_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
	_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
	_rotateImage->width = size;
	_rotateImage->height = size;

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(_hWnd, hdc);



	return S_OK;
}

HRESULT image::rotateInit(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �����̶� ���������� ������
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int size;
	(width > height ? size = width : size = height);
	_rotateImage = new IMAGE_INFO;
	_rotateImage->loadType = LOAD_EMPTY;
	_rotateImage->resID = 0;
	_rotateImage->hMemDC = CreateCompatibleDC(hdc);
	_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
	_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
	_rotateImage->width = size;
	_rotateImage->height = size;

	//���ĺ��� ����
	_blendFunc.BlendFlags = 0;			//���ĺ��带 ����ϰڴٰ� �ʱ�ȭ
	_blendFunc.AlphaFormat = 0;			//���ĺ��忡 �ʿ��� �������� �ʱ�ȭ
	_blendFunc.BlendOp = AC_SRC_OVER;	//<-- �̰Ÿ��� ������� �����غ���

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	int len = strlen(fileName);

	//���ϰ�� �� �̸� �޾ƿ´�
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//Ư���÷� �������� ���� �� �÷� ��
	_trans = trans;
	_transColor = transColor;

	//�̹����� ����� �ҷ������� �ʾҴٸ�
	if (_imageInfo->hBit == NULL)
	{
		//�����ϰ� ������ �������
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//�� init�Լ��� ���ĺ��� ó���� �̹����� �Ҵ�ǰ� �ֱ� ������
		//���� ����������մϴ�!!!!!!!!!!!!!!!
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		SAFE_DELETE(_blendImage);

		_trans = false;
		_transColor = FALSE;
	}
}

void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void image::setAlpahBlend(BOOL alpha, BYTE alphaValue)
{
	_alpha = alpha;
	_alphaValue = alphaValue;

	HDC hdc = GetDC(_hWnd);

	//���ĺ��� ������.
	//���� + ġ���̴� �����ؼ� ����
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;	//<-- �̰� �� �� �����غ����� ������

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	ReleaseDC(_hWnd, hdc);
}

void image::render(HDC hdc)
{
	if (_trans)
	{
		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� DC
			0,					//�̹��� �׷��� ����X��ǥ(left)
			0,					//�̹��� �׷��� ����Y��ǥ(top)
			_imageInfo->width,		//����� ����ũ��
			_imageInfo->height,		//����� ����ũ��
			_imageInfo->hMemDC,
			0, 0,					//��������� XY��ǥ
			_imageInfo->width,		//������ ����/����ũ��
			_imageInfo->height,
			_transColor				//���綧 ������ Į��(�� Į��)
		);
	}
	else
	{
		BitBlt(hdc, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� DC
			destX,					//�̹��� �׷��� ����X��ǥ(left)
			destY,					//�̹��� �׷��� ����Y��ǥ(top)
			_imageInfo->width,		//����� ����ũ��
			_imageInfo->height,		//����� ����ũ��
			_imageInfo->hMemDC,
			0, 0,					//��������� XY��ǥ
			_imageInfo->width,		//������ ����/����ũ��
			_imageInfo->height,
			_transColor				//���綧 ������ Į��(�� Į��)
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� DC
			destX,					//�̹��� �׷��� ����X��ǥ(left)
			destY,					//�̹��� �׷��� ����Y��ǥ(top)
			sourWidth,				//����� ����ũ��
			sourHeight,				//����� ����ũ��
			_imageInfo->hMemDC,
			sourX, sourY,			//��������� XY��ǥ
			sourWidth,				//������ ����/����ũ��
			sourHeight,
			_transColor				//���綧 ������ Į��(�� Į��)
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� DC
			destX,					//�̹��� �׷��� ����X��ǥ(left)
			destY,					//�̹��� �׷��� ����Y��ǥ(top)
			_imageInfo->frameWidth,				//����� ����ũ��
			_imageInfo->frameHeight,				//����� ����ũ��
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//��������� XY��ǥ
			_imageInfo->frameWidth,				//������ ����/����ũ��
			_imageInfo->frameHeight,
			_transColor				//���綧 ������ Į��(�� Į��)
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� DC
			destX,					//�̹��� �׷��� ����X��ǥ(left)
			destY,					//�̹��� �׷��� ����Y��ǥ(top)
			_imageInfo->frameWidth,				//����� ����ũ��
			_imageInfo->frameHeight,				//����� ����ũ��
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//��������� XY��ǥ
			_imageInfo->frameWidth,				//������ ����/����ũ��
			_imageInfo->frameHeight,
			_transColor				//���綧 ������ Į��(�� Į��)
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	//ȭ�鿡 �����̹��� �׷��� ������ �����غ���
	int drawAreaX = drawArea->left;				//�׷��� ������ Left
	int drawAreaY = drawArea->top;				//�׷��� ������ top
	int drawAreaW = drawArea->right - drawAreaX; //�׷��� ������ ����ũ��
	int drawAreaH = drawArea->bottom - drawAreaY;//�׷��� ������ ����ũ��

	//���κ��� �غ��ô�
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//������ ������ ���ؼ� ��Ȯ�� ��ġ�� �˾ƿ´�
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		//�з��ö� ���� ���
		sourHeight = rcSour.bottom - rcSour.top;

		//ȭ������� �̹����� �����ٸ�
		if (y + sourHeight > drawAreaH)
		{
			//�׸�ŭ ��������� - ���궧���� ������ -���� ���� �ƴ϶� �����ΰ���
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//ȭ������� ���������� �ٽ� �о�ø���(�ٽ� �׷��ش�)
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//�Ͽ��̰� ���ϴ� X��
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//������ ������ ���� ���� ����
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}

}

//
void image::alphaRender(HDC hdc)
{
	alphaRender(hdc, _alphaValue);
}

//
void image::alphaRender(HDC hdc, BYTE alpha)
{
	//������ �����սô�
	//BYTE�� ���ĺ��� ��ġ���̴�. 0 ~ 255�� ������ ������
	//���� �������� ������ ����

	// ���� ���� ���ϸ� �Ϲ� ���� ���
	if (!_alpha)
	{
		render(hdc);
		return;
	}

	_alphaValue = alpha;

	//�̰��� �ؾ� ���İ��� �����!!!
	_blendFunc.SourceConstantAlpha = _alphaValue;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, SRCCOPY);

		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			_blendImage->hMemDC,	//����� DC
			0,						//�̹��� �׷��� ����X��ǥ(left)
			0,						//�̹��� �׷��� ����Y��ǥ(top)
			_imageInfo->width,		//����� ����ũ��
			_imageInfo->height,		//����� ����ũ��
			_imageInfo->hMemDC,
			0, 0,					//��������� XY��ǥ
			_imageInfo->width,		//������ ����/����ũ��
			_imageInfo->height,
			_transColor				//���綧 ������ Į��(�� Į��)
		);

		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY)
{
	//������ �����սô�
	//BYTE�� ���ĺ��� ��ġ���̴�. 0 ~ 255�� ������ ������
	//���� �������� ������ ����

	// ���� ���� ���ϸ� �Ϲ� ���� ���
	if (!_alpha)
	{
		render(hdc, destX, destY);
		return;
	}

	//�̰��� �ؾ� ���İ��� �����!!!
	_blendFunc.SourceConstantAlpha = _alphaValue;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			_blendImage->hMemDC,	//����� DC
			0,						//�̹��� �׷��� ����X��ǥ(left)
			0,						//�̹��� �׷��� ����Y��ǥ(top)
			_imageInfo->width,		//����� ����ũ��
			_imageInfo->height,		//����� ����ũ��
			_imageInfo->hMemDC,
			0, 0,					//��������� XY��ǥ
			_imageInfo->width,		//������ ����/����ũ��
			_imageInfo->height,
			_transColor				//���綧 ������ Į��(�� Į��)
		);

		AlphaBlend(hdc, destX, destY, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendFunc);
	}

}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_alphaValue = alpha;
	alphaRender(hdc, destX, destY);
}

void image::alphaFrameRender(HDC hdc, int destX, int destY)
{
	// ���� ���� ���ϸ� �Ϲ� ������ ���� ���
	if (!_alpha)
	{
		frameRender(hdc, destX, destY);
		return;
	}

	//�̰��� �ؾ� ���İ��� �����!!!
	_blendFunc.SourceConstantAlpha = _alphaValue;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC
			, 0, 0
			, _imageInfo->frameWidth, _imageInfo->frameHeight
			, hdc
			, destX, destY
			, SRCCOPY);

		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			_blendImage->hMemDC,								//����� DC
			0,												//�̹��� �׷��� ����X��ǥ(left)
			0,												//�̹��� �׷��� ����Y��ǥ(top)
			_imageInfo->frameWidth,								//����� ����ũ��
			_imageInfo->frameHeight,							//����� ����ũ��
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//��������� XY��ǥ
			_imageInfo->frameWidth,								//������ ����/����ũ��
			_imageInfo->frameHeight,
			_transColor											//���綧 ������ Į��(�� Į��)
		);

		AlphaBlend(hdc
			, destX, destY
			, _imageInfo->frameWidth, _imageInfo->frameHeight
			, _blendImage->hMemDC
			, 0, 0
			, _imageInfo->frameWidth, _imageInfo->frameHeight
			, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc
			, destX, destY
			, _imageInfo->frameWidth, _imageInfo->frameHeight
			, _blendImage->hMemDC
			, 0, 0
			, _imageInfo->frameWidth, _imageInfo->frameHeight
			, _blendFunc);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_alphaValue = alpha;
	alphaFrameRender(hdc, destX, destY);
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	alphaFrameRender(hdc, destX, destY);
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_alphaValue = alpha;
	alphaFrameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

void image::alphaAniRender(HDC hdc, int destX, int destY, animation * ani, BYTE alpha)
{
	// ���� ���� ���ϸ� �Ϲ� �ִ� ���� ���
	if (!_alpha)
	{
		render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
		return;
	}

	_alphaValue = alpha;

	//�̰��� �ؾ� ���İ��� �����!!!
	_blendFunc.SourceConstantAlpha = _alphaValue;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC
			, 0, 0
			, ani->getFrameWidth(), ani->getFrameHeight()
			, hdc
			, destX, destY
			, SRCCOPY);

		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			_blendImage->hMemDC,								//����� DC
			0,												//�̹��� �׷��� ����X��ǥ(left)
			0,												//�̹��� �׷��� ����Y��ǥ(top)
			ani->getFrameWidth(),							//����� ����ũ��
			ani->getFrameHeight(),							//����� ����ũ��
			_imageInfo->hMemDC,
			ani->getFramePos().x,
			ani->getFramePos().y,							//��������� XY��ǥ
			ani->getFrameWidth(),							//������ ����/����ũ��
			ani->getFrameHeight(),
			_transColor											//���綧 ������ Į��(�� Į��)
		);

		AlphaBlend(hdc
			, destX, destY
			, ani->getFrameWidth(), ani->getFrameHeight()
			, _blendImage->hMemDC
			, 0, 0
			, ani->getFrameWidth(), ani->getFrameHeight()
			, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc
			, destX, destY
			, ani->getFrameWidth(), ani->getFrameHeight()
			, _blendImage->hMemDC
			, 0, 0
			, ani->getFrameWidth(), ani->getFrameHeight()
			, _blendFunc);
	}
}

void image::alphaAniRenderCenter(HDC hdc, int centerX, int centerY, animation * ani, BYTE alpha)
{
	// ���� ���� ���ϸ� �Ϲ� �ִ� ���� ���
	if (!_alpha)
	{
		render(hdc, centerX - ani->getFrameWidth() / 2, centerY - ani->getFrameHeight() / 2, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
		return;
	}

	_alphaValue = alpha;

	//�̰��� �ؾ� ���İ��� �����!!!
	_blendFunc.SourceConstantAlpha = _alphaValue;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC
			, 0, 0
			, ani->getFrameWidth(), ani->getFrameHeight()
			, hdc
			, centerX - ani->getFrameWidth() / 2, centerY - ani->getFrameHeight() / 2
			, SRCCOPY);

		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			_blendImage->hMemDC,								//����� DC
			0,												//�̹��� �׷��� ����X��ǥ(left)
			0,												//�̹��� �׷��� ����Y��ǥ(top)
			ani->getFrameWidth(),							//����� ����ũ��
			ani->getFrameHeight(),							//����� ����ũ��
			_imageInfo->hMemDC,
			ani->getFramePos().x,
			ani->getFramePos().y,							//��������� XY��ǥ
			ani->getFrameWidth(),							//������ ����/����ũ��
			ani->getFrameHeight(),
			_transColor											//���綧 ������ Į��(�� Į��)
		);

		AlphaBlend(hdc
			, centerX - ani->getFrameWidth() / 2, centerY - ani->getFrameHeight() / 2
			, ani->getFrameWidth(), ani->getFrameHeight()
			, _blendImage->hMemDC
			, 0, 0
			, ani->getFrameWidth(), ani->getFrameHeight()
			, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc
			, centerX - ani->getFrameWidth() / 2, centerY - ani->getFrameHeight() / 2
			, ani->getFrameWidth(), ani->getFrameHeight()
			, _blendImage->hMemDC
			, 0, 0
			, ani->getFrameWidth(), ani->getFrameHeight()
			, _blendFunc);
	}

}

void image::expandRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float sizeX, float sizeY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	SetStretchBltMode(hdc, COLORONCOLOR);

	TransparentBlt(hdc,
		destX,
		destY,
		_imageInfo->frameWidth * sizeX,
		_imageInfo->frameHeight * sizeY,
		_imageInfo->hMemDC,
		_imageInfo->currentFrameX * _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->frameWidth,
		_imageInfo->frameHeight,
		_transColor
	);
}

void image::expandRenderCenter(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float sizeX, float sizeY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	SetStretchBltMode(hdc, COLORONCOLOR);

	TransparentBlt(hdc,
		destX - (sizeX *_imageInfo->frameWidth) / 2,
		destY - (sizeY * _imageInfo->frameHeight) / 2,
		_imageInfo->frameWidth * sizeX,
		_imageInfo->frameHeight * sizeY,
		_imageInfo->hMemDC,
		_imageInfo->currentFrameX * _imageInfo->frameWidth,
		_imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->frameWidth,
		_imageInfo->frameHeight,
		_transColor
	);
}

void image::expandAniRender(HDC hdc, int destX, int destY, animation* ani, float sizeX, float sizeY)
{
	SetStretchBltMode(hdc, COLORONCOLOR);

	TransparentBlt(hdc,
		destX,
		destY,
		ani->getFrameWidth() * sizeX,
		ani->getFrameHeight() * sizeY,
		_imageInfo->hMemDC,
		ani->getFramePos().x,
		ani->getFramePos().y,
		ani->getFrameWidth(),
		ani->getFrameHeight(),
		_transColor
	);

}

void image::expandAniRenderCenter(HDC hdc, int destX, int destY, animation* ani, float sizeX, float sizeY)
{
	SetStretchBltMode(hdc, COLORONCOLOR);

	TransparentBlt(hdc,
		destX - (sizeX * ani->getFrameWidth()) / 2,
		destY - (sizeY * ani->getFrameHeight()) / 2,
		ani->getFrameWidth() * sizeX,
		ani->getFrameHeight() * sizeY,
		_imageInfo->hMemDC,
		ani->getFramePos().x,
		ani->getFramePos().y,
		ani->getFrameWidth(),
		ani->getFrameHeight(),
		_transColor
	);
}

void image::rotateRender(HDC hdc, float centerX, float centerY, float angle)
{
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2) * (_imageInfo->width / 2) + (_imageInfo->height / 2) * (_imageInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; ++i)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)* dist);
	}

	if (_trans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC,
			centerX, centerY,
			_imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}
}

void image::rotateFrameRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle)
{
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) * (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));

	for (int i = 0; i < 3; ++i)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)* dist);
	}

	if (_trans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);
		//
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);


		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);

		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, _imageInfo->currentFrameX, _imageInfo->currentFrameY, _imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}

