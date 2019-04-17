#include "stdafx.h"
#include "aStarMove.h"


aStarMove::aStarMove()
{
}


aStarMove::~aStarMove()
{
}

HRESULT aStarMove::init()
{
	_battle = new battleMap;
	_battle->init();

	return S_OK;
}

void aStarMove::release()
{
}

void aStarMove::update()
{
	if (_isStart == true)
	{
		for (_iOpenTile = _OpenTile.begin(); _iOpenTile != _OpenTile.end(); _iOpenTile++)
		{
			(*_iOpenTile)->f = (*_iOpenTile)->h + (*_iOpenTile)->g;
		}

		for (_iOpenTile = _OpenTile.begin(); _iOpenTile != _OpenTile.end(); _iOpenTile++)
		{
			if (_compareInt > (*_iOpenTile)->f)
			{
				_compareInt = (*_iOpenTile)->f;
				_currentX = (*_iOpenTile)->index.x;
				_currentY = (*_iOpenTile)->index.y;
			}
		}

		if (_CloseTile.size() < (_battle->getTileX()*(_battle->getTileY())))
		{
			_CloseTile.push_back(_vvAStar[_currentY][_currentX]);
		}

		for (_iOpenTile = _OpenTile.begin(); _iOpenTile != _OpenTile.end();)
		{
			if ((*_iOpenTile)->index.x == _currentX && (*_iOpenTile)->index.y == _currentY)
			{
				_OpenTile.erase(_iOpenTile);
				break;
			}
			else
			{
				_iOpenTile++;
			}
		}

		//왼쪽
		if (_currentX > 0)
		{

			for (_iCloseTile = _CloseTile.begin(); _iCloseTile != _CloseTile.end(); _iCloseTile++)
			{
				if ((*_iCloseTile)->index.y == _currentY && (*_iCloseTile)->index.x == _currentX - 1)
				{
					_locCheck[0] = true;
				}
			}


			if (_vvAStar[_currentY][_currentX - 1]->isblock == true)
			{
				_locCheck[0] = true;
			}


			for (_iOpenTile = _OpenTile.begin(); _iOpenTile != _OpenTile.end(); _iOpenTile++)
			{
				if ((*_iOpenTile)->index.y == _currentY && (*_iOpenTile)->index.x == _currentX - 1)
				{

					if ((*_iOpenTile)->g > _vvAStar[_currentY][_currentX]->g + 10)
					{
						_vvAStar[_currentY][_currentX - 1]->aStar = _vvAStar[_currentY][_currentX];
						_vvAStar[_currentY][_currentX - 1]->g = _vvAStar[_currentY][_currentX]->g + 10;
						_locCheck[0] = true;
					}
					else
					{
						_locCheck[0] = true;
					}
				}
			}

			if (_locCheck[0] == false)
			{
				_vvAStar[_currentY][_currentX - 1]->aStar = _vvAStar[_currentY][_currentX];
				_vvAStar[_currentY][_currentX - 1]->g = _vvAStar[_currentY][_currentX]->g + 10;
				_OpenTile.push_front(_vvAStar[_currentY][_currentX - 1]);
			}
		}

		//오른쪽
		if (_currentX < (*_tileNum).x - 1)
		{

			for (_iCloseTile = _CloseTile.begin(); _iCloseTile != _CloseTile.end(); _iCloseTile++)
			{
				if ((*_iCloseTile)->index.y == _currentY && (*_iCloseTile)->index.x == _currentX + 1)
				{
					_locCheck[1] = true;
				}
			}


			if (_vvAStar[_currentY][_currentX + 1]->isblock == true)
			{
				_locCheck[1] = true;
			}


			for (_iOpenTile = _OpenTile.begin(); _iOpenTile != _OpenTile.end(); _iOpenTile++)
			{
				if ((*_iOpenTile)->index.y == _currentY && (*_iOpenTile)->index.x == _currentX + 1)
				{

					if ((*_iOpenTile)->g > _vvAStar[_currentY][_currentX]->g + 10)
					{
						_vvAStar[_currentY][_currentX + 1]->aStar = _vvAStar[_currentY][_currentX];
						_vvAStar[_currentY][_currentX + 1]->g = _vvAStar[_currentY][_currentX]->g + 10;
						_locCheck[1] = true;
					}
					else
					{
						_locCheck[1] = true;
					}
				}
			}

			if (_locCheck[1] == false)
			{
				_vvAStar[_currentY][_currentX + 1]->aStar = _vvAStar[_currentY][_currentX];
				_vvAStar[_currentY][_currentX + 1]->g = _vvAStar[_currentY][_currentX]->g + 10;
				_OpenTile.push_front(_vvAStar[_currentY][_currentX + 1]);
			}
		}

		if (_currentY > 0)
		{

			for (_iCloseTile = _CloseTile.begin(); _iCloseTile != _CloseTile.end(); _iCloseTile++)
			{
				if ((*_iCloseTile)->index.y == _currentY - 1 && (*_iCloseTile)->index.x == _currentX)
				{
					_locCheck[2] = true;
				}
			}


			if (_vvAStar[_currentY - 1][_currentX]->isblock == true)
			{
				_locCheck[2] = true;
			}


			for (_iOpenTile = _OpenTile.begin(); _iOpenTile != _OpenTile.end(); _iOpenTile++)
			{
				if ((*_iOpenTile)->index.y == _currentY - 1 && (*_iOpenTile)->index.x == _currentX)
				{

					if ((*_iOpenTile)->g > _vvAStar[_currentY][_currentX]->g + 10)
					{
						_vvAStar[_currentY - 1][_currentX]->aStar = _vvAStar[_currentY][_currentX];
						_vvAStar[_currentY - 1][_currentX]->g = _vvAStar[_currentY][_currentX]->g + 10;
						_locCheck[2] = true;
					}
					else
					{
						_locCheck[2] = true;
					}
				}
			}

			if (_locCheck[2] == false)
			{
				_vvAStar[_currentY - 1][_currentX]->aStar = _vvAStar[_currentY][_currentX];
				_vvAStar[_currentY - 1][_currentX]->g = _vvAStar[_currentY][_currentX]->g + 10;
				_OpenTile.push_front(_vvAStar[_currentY - 1][_currentX]);
			}
		}


		//아래
		if (_currentY < (*_tileNum).y - 1)
		{

			for (_iCloseTile = _CloseTile.begin(); _iCloseTile != _CloseTile.end(); _iCloseTile++)
			{
				if ((*_iCloseTile)->index.y == _currentY + 1 && (*_iCloseTile)->index.x == _currentX)
				{
					_locCheck[3] = true;
				}
			}


			if (_vvAStar[_currentY + 1][_currentX]->isblock == true)
			{
				_locCheck[3] = true;
			}


			for (_iOpenTile = _OpenTile.begin(); _iOpenTile != _OpenTile.end(); _iOpenTile++)
			{
				if ((*_iOpenTile)->index.y == _currentY + 1 && (*_iOpenTile)->index.x == _currentX)
				{

					if ((*_iOpenTile)->g > _vvAStar[_currentY][_currentX]->g + 10)
					{
						_vvAStar[_currentY + 1][_currentX]->aStar = _vvAStar[_currentY][_currentX];
						_vvAStar[_currentY + 1][_currentX]->g = _vvAStar[_currentY][_currentX]->g + 10;
						_locCheck[3] = true;
					}
					else
					{
						_locCheck[3] = true;
					}
				}
			}

			if (_locCheck[3] == false)
			{
				_vvAStar[_currentY + 1][_currentX]->aStar = _vvAStar[_currentY][_currentX];
				_vvAStar[_currentY + 1][_currentX]->g = _vvAStar[_currentY][_currentX]->g + 10;
				_OpenTile.push_front(_vvAStar[_currentY + 1][_currentX]);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			_locCheck[i] = false;
		}

		_compareInt = 5000;

		for (_iOpenTile = _OpenTile.begin(); _iOpenTile != _OpenTile.end(); _iOpenTile++)
		{
			if ((*_iOpenTile)->index.x == _endIdx.x && (*_iOpenTile)->index.y == _endIdx.y)
			{

				_isStart = false;
				_isStopEndG = true;
				_currentX = (*_iOpenTile)->index.x;
				_currentY = (*_iOpenTile)->index.y;
				_endG = ((*_iOpenTile)->g) / 10;
			}
		}

	}

	if (_isStopEndG == true)
	{
		for (int i = 0; i < _endG; i++)
		{
			if (_endG - 1 == i)
			{
				_giveIdx.x = _vvAStar[_currentY][_currentX]->index.x;
				_giveIdx.y = _vvAStar[_currentY][_currentX]->index.y;
			}

			_LoadTile.push_back({ _vvAStar[_currentY][_currentX]->index.x,_vvAStar[_currentY][_currentX]->index.y });
			playX = _vvAStar[_currentY][_currentX]->aStar->index.x;
			playY = _vvAStar[_currentY][_currentX]->aStar->index.y;

			_currentX = playX;
			_currentY = playY;
		}
		_isStopEndG = false;
	}
}

void aStarMove::render(float cameraX, float cameraY )
{
	char str[1000];

	if (_vvAStar.size() > 0)
	{
		for (int i = 0; i < _battle->getTileY(); i++)
		{
			for (int j = 0; j < _battle->getTileX(); j++)
			{
				//알프의 이동범위
				if (_alph->getASrender() == true)
				{
					if (_vvAStar[j][i]->f <= 30)
					{
						left = _battle->getclassTile(0, 0)->getPos() + (j * RADIUS_WIDTH) - (i * RADIUS_WIDTH) - 64;
						top = _battle->getclassTile(0, 0)->getPosY() - 32 + (j * RADIUS_HEIGHT) + (i * RADIUS_HEIGHT);
						if (_battle->getclassTile(j, i)->getZlevel() == 0)
						{
							HPEN myPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
							HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
							drawRhombus(left, top, cameraX, cameraY);
							DeleteObject(SelectObject(getMemDC(), oldPen));
						}
						else if (_battle->getclassTile(j, i)->getZlevel() > 0)
						{
							left = _battle->getclassTile(0, 0)->getPos() + (j * RADIUS_WIDTH) - (i * RADIUS_WIDTH) - 64;
							top = _battle->getclassTile(0, 0)->getPosY() + (j * RADIUS_HEIGHT) + (i * RADIUS_HEIGHT) - (_battle->getclassTile(j, i)->getZlevel() * 32) - 32;

							HPEN myPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
							HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
							drawRhombus(left, top, cameraX, cameraY);
							DeleteObject(SelectObject(getMemDC(), oldPen));
						}

						//sprintf_s(str, "%d %d %d", _vvAStar[j][i]->h, _vvAStar[j][i]->g, _vvAStar[j][i]->f);
						//TextOut(getMemDC(), _battle->getclassTile(j, i)->getPos() - cameraX - 16, _battle->getclassTile(j, i)->getPosY() - cameraY - 16, str, strlen(str));
					}
				}
				//알프의 기본공격범위
				if (_alph->getAtkRange() == true)
				{
					if (_vvAStar[j][i]->f == 10)
					{
						left = _battle->getclassTile(0, 0)->getPos() + (j * RADIUS_WIDTH) - (i * RADIUS_WIDTH) - 64;
						top = _battle->getclassTile(0, 0)->getPosY() - 32 + (j * RADIUS_HEIGHT) + (i * RADIUS_HEIGHT);
						
						if (_battle->getclassTile(j, i)->getZlevel() == 0)
						{
							HPEN myPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
							HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
							drawRhombus(left, top, cameraX, cameraY);
							DeleteObject(SelectObject(getMemDC(), oldPen));
						}
						else if (_battle->getclassTile(j, i)->getZlevel() > 0)
						{
							left = _battle->getclassTile(0, 0)->getPos() + (j * RADIUS_WIDTH) - (i * RADIUS_WIDTH) - 64;
							top = _battle->getclassTile(0, 0)->getPosY() + (j * RADIUS_HEIGHT) + (i * RADIUS_HEIGHT) - (_battle->getclassTile(j, i)->getZlevel() * 32) - 32;
				
							HPEN myPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
							HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
							drawRhombus(left, top, cameraX, cameraY);
							DeleteObject(SelectObject(getMemDC(), oldPen));
						}
					}
				}
				//알프의 마법공격범위
				if (_alph->getMgcRange() == true)
				{
					if (_vvAStar[j][i]->f == 20 || _vvAStar[j][i]->f == 30)
					{
						left = _battle->getclassTile(0, 0)->getPos() + (j * RADIUS_WIDTH) - (i * RADIUS_WIDTH) - 64;
						top = _battle->getclassTile(0, 0)->getPosY() - 32 + (j * RADIUS_HEIGHT) + (i * RADIUS_HEIGHT);

						if (_battle->getclassTile(j, i)->getZlevel() == 0)
						{
							HPEN myPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
							HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
							drawRhombus(left, top, cameraX, cameraY);
							DeleteObject(SelectObject(getMemDC(), oldPen));
						}
						else if (_battle->getclassTile(j, i)->getZlevel() > 0)
						{
							left = _battle->getclassTile(0, 0)->getPos() + (j * RADIUS_WIDTH) - (i * RADIUS_WIDTH) - 64;
							top = _battle->getclassTile(0, 0)->getPosY() + (j * RADIUS_HEIGHT) + (i * RADIUS_HEIGHT) - (_battle->getclassTile(j, i)->getZlevel() * 32) - 32;

							HPEN myPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
							HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
							drawRhombus(left, top, cameraX, cameraY);
							DeleteObject(SelectObject(getMemDC(), oldPen));
						}
					}
				}

				if (_alph->getsynergeRange() == true)
				{
					if (_vvAStar[j][i]->f <= 40)
					{
						left = _battle->getclassTile(0, 0)->getPos() + (j * RADIUS_WIDTH) - (i * RADIUS_WIDTH) - 64;
						top = _battle->getclassTile(0, 0)->getPosY() - 32 + (j * RADIUS_HEIGHT) + (i * RADIUS_HEIGHT);

						if (_battle->getclassTile(j, i)->getZlevel() == 0)
						{
							HPEN myPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
							HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
							drawRhombus(left, top, cameraX, cameraY);
							DeleteObject(SelectObject(getMemDC(), oldPen));
						}
						else if (_battle->getclassTile(j, i)->getZlevel() > 0)
						{
							left = _battle->getclassTile(0, 0)->getPos() + (j * RADIUS_WIDTH) - (i * RADIUS_WIDTH) - 64;
							top = _battle->getclassTile(0, 0)->getPosY() + (j * RADIUS_HEIGHT) + (i * RADIUS_HEIGHT) - (_battle->getclassTile(j, i)->getZlevel() * 32) - 32;

							HPEN myPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
							HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
							drawRhombus(left, top, cameraX, cameraY);
							DeleteObject(SelectObject(getMemDC(), oldPen));
						}
					}
				}
			}
		}
	}
}

void aStarMove::drawRhombus(int left, int top, float cameraX, float cameraY)
{
	centerX = left + RADIUS_WIDTH;
	centerY = top + RADIUS_HEIGHT;

	p[0].x = centerX - cameraX;
	p[0].y = centerY - RADIUS_HEIGHT - cameraY;
	p[1].x = centerX + RADIUS_WIDTH - cameraX;
	p[1].y = centerY - cameraY;
	p[2].x = centerX - cameraX;
	p[2].y = centerY + RADIUS_HEIGHT - cameraY;
	p[3].x = centerX - RADIUS_WIDTH - cameraX;
	p[3].y = centerY - cameraY;

	Polygon(getMemDC(), p, 4);
}

void aStarMove::setAstar()
{
	_vvAStar.clear();

	_compareInt = 5000;

	_OpenTile.clear();
	_CloseTile.clear();
	_LoadTile.clear();

	for (int i = 0; i < _battle->getTileY(); i++)
	{
		vector<aStarMoving*> _tempV;
		_tempV.clear();
		for (int j = 0; j < _battle->getTileX(); j++)
		{
			aStarMoving* _tempTile = new aStarMoving;
			_tempTile->h = (abs(j - _endIdx.x)) * 10 + (abs(i - _endIdx.y)) * 10;
			_tempTile->g = 0;
			_tempTile->f = _tempTile->h + _tempTile->g;
			_tempTile->index.x = j;
			_tempTile->index.y = i;

			if (_battle->getclassTile(_battle->getTileX() - 1, _battle->getTileY() - 1)->getZlevel() >= 0)
			{
				_tempTile->isblock = true;
			}
			if (_endIdx.x == j && _endIdx.y == i)
			{
				_tempTile->isEnd = true;
			}
			if (_startIdx.x == j && _startIdx.y == i)
			{
				_tempTile->isStart = true;
			}
			_tempV.push_back(_tempTile);
		}
		_vvAStar.push_back(_tempV);
	}

	_OpenTile.push_back(_vvAStar[_startIdx.y][_startIdx.x]);
	_isStart = true;
}
