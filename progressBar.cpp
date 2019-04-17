#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	{
		string imgName = AppendInt("frontBar", width);
		string fileName = MakeImageName("hpBarTop");
		_topImgName = imgName;
		_progressBarTop = IMAGEMANAGER->addImage(imgName, fileName.c_str(), x, y, width, height, true, RGB(255, 0, 255));
	}

	{
		string imgName = AppendInt("backBar", width);
		string fileName = MakeImageName("hpBarBottom");
		_backImgName = imgName;
		_progressBarBottom = IMAGEMANAGER->addImage(imgName, fileName.c_str(), x, y, width, height, true, RGB(255, 0, 255));
	}

	//���α׷��� �� �̹����� ũ�Ⱑ ����ũ�Ⱑ �ȴ�.
	_width = _progressBarBottom->GetWidth();

	return S_OK;
}

HRESULT progressBar::init(const char* backImgName, const char* frontImgName, int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	{
		string imgName = AppendInt(frontImgName, width);
		string fileName = MakeImageName(frontImgName);
		_topImgName = imgName;
		_progressBarTop = IMAGEMANAGER->addImage(imgName, fileName.c_str(), x, y, width, height, true, RGB(255, 0, 255));

	}

	{
		string imgName = AppendInt(backImgName, width);
		string fileName = MakeImageName(backImgName);
		_backImgName = imgName;
		_progressBarBottom = IMAGEMANAGER->addImage(imgName, fileName.c_str(), x, y, width, height, true, RGB(255, 0, 255));
	}

	//���α׷��� �� �̹����� ũ�Ⱑ ����ũ�Ⱑ �ȴ�.
	_width = _progressBarBottom->GetWidth();

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarTop->GetWidth(), _progressBarTop->GetHeight());
}

void progressBar::render()
{
	//������ �׷��ִ� ���� ������ �޴´�. �׷����� ������� ������ ���´�
	IMAGEMANAGER->render(_backImgName, getMemDC()
		, _rcProgress.left + _progressBarBottom->GetWidth() / 2
		, _y + _progressBarBottom->GetHeight() / 2
		, 0, 0
		, _progressBarBottom->GetWidth()
		, _progressBarBottom->GetHeight());

	//�տ� �׷����� �������� ����ũ�⸦ �����Ѵ�.
	IMAGEMANAGER->render(_topImgName, getMemDC()
		, _rcProgress.left + _progressBarBottom->GetWidth() / 2
		, _y + _progressBarBottom->GetHeight() / 2
		, 0, 0
		, _width, _progressBarBottom->GetHeight());

	Rectangle(getMemDC(), _rcProgress);

}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	//��ġ�� ������ ������ش�.
	_width = (currentGauge / maxGauge) * _progressBarBottom->GetWidth();
}
