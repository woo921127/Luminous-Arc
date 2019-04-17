#include "stdafx.h"
#include "effect.h"
#include "animation.h"

effect::effect()
	: _effectImage(NULL), 
	_effectAnimation(NULL),
	_isRunning(false), 
	_x(0), _y(0)
{
}


effect::~effect()
{
}

HRESULT effect::init(image * effectImage, int frameW, int frameH, int fps, float elapsedTime)
{
	if (!effectImage) return E_FAIL;

	_isRunning = false;
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;


	if (!_effectAnimation) _effectAnimation = new animation;

	_effectAnimation->init(_effectImage->GetWidth(), _effectImage->GetHeight(), frameW, frameH);
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();

	return S_OK;
}

void effect::release()
{
	_effectImage = NULL;
	SAFE_DELETE(_effectAnimation);
}

void effect::update()
{

	//����Ʈ �ִϸ��̼� �������� �ƴϸ� ������������
	if (!_isRunning) return;

	_effectAnimation->frameUpdate(_elapsedTime);

	//�ִϸ��̼� �����ȣ��  false�� ����Ʈ�� ����
	if (!_effectAnimation->isPlay()) killEffect();


}

void effect::render()
{
	//�ִϸ��̼��� ������� �ƴ϶�� ������ ���� �ʴ´�
	if (!_isRunning) return;

	_effectImage->aniRender(getMemDC(), _x, _y, _effectAnimation);
}

void effect::startEffect(int x, int y)
{
	//����Ʈ�̹��� or ����Ʈ�ִϸ��̼� ������ �Ǿ����������� ����Ʈ ��������
	if (!_effectImage || !_effectAnimation) return;

	_x = x - (_effectAnimation->getFrameWidth() / 2);
	_y = y - (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;

	_effectAnimation->effectStart();
}

void effect::killEffect()
{
	_isRunning = false;
}