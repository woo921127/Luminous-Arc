#include "stdafx.h"
#include "EnemyAstar.h"


EnemyAstar::EnemyAstar()
{
}


EnemyAstar::~EnemyAstar()
{
}

HRESULT EnemyAstar::init()
{

	_battle = new battleMap;
	_battle->init();

	return S_OK;
}

void EnemyAstar::release()
{
}

void EnemyAstar::update()
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
			_CloseTile.push_back(_EnemyAStar[_currentY][_currentX]);
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


			if (_EnemyAStar[_currentY][_currentX - 1]->isblock == true)
			{
				_locCheck[0] = true;
			}


			for (_iOpenTile = _OpenTile.begin(); _iOpenTile != _OpenTile.end(); _iOpenTile++)
			{
				if ((*_iOpenTile)->index.y == _currentY && (*_iOpenTile)->index.x == _currentX - 1)
				{

					if ((*_iOpenTile)->g > _EnemyAStar[_currentY][_currentX]->g + 10)
					{
						_EnemyAStar[_currentY][_currentX - 1]->EnemyStar = _EnemyAStar[_currentY][_currentX];
						_EnemyAStar[_currentY][_currentX - 1]->g = _EnemyAStar[_currentY][_currentX]->g + 10;
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
				_EnemyAStar[_currentY][_currentX - 1]->EnemyStar = _EnemyAStar[_currentY][_currentX];
				_EnemyAStar[_currentY][_currentX - 1]->g = _EnemyAStar[_currentY][_currentX]->g + 10;
				_OpenTile.push_front(_EnemyAStar[_currentY][_currentX - 1]);
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


			if (_EnemyAStar[_currentY][_currentX + 1]->isblock == true)
			{
				_locCheck[1] = true;
			}


			for (_iOpenTile = _OpenTile.begin(); _iOpenTile != _OpenTile.end(); _iOpenTile++)
			{
				if ((*_iOpenTile)->index.y == _currentY && (*_iOpenTile)->index.x == _currentX + 1)
				{

					if ((*_iOpenTile)->g > _EnemyAStar[_currentY][_currentX]->g + 10)
					{
						_EnemyAStar[_currentY][_currentX + 1]->EnemyStar = _EnemyAStar[_currentY][_currentX];
						_EnemyAStar[_currentY][_currentX + 1]->g = _EnemyAStar[_currentY][_currentX]->g + 10;
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
				_EnemyAStar[_currentY][_currentX + 1]->EnemyStar = _EnemyAStar[_currentY][_currentX];
				_EnemyAStar[_currentY][_currentX + 1]->g = _EnemyAStar[_currentY][_currentX]->g + 10;
				_OpenTile.push_front(_EnemyAStar[_currentY][_currentX + 1]);
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


			if (_EnemyAStar[_currentY - 1][_currentX]->isblock == true)
			{
				_locCheck[2] = true;
			}


			for (_iOpenTile = _OpenTile.begin(); _iOpenTile != _OpenTile.end(); _iOpenTile++)
			{
				if ((*_iOpenTile)->index.y == _currentY - 1 && (*_iOpenTile)->index.x == _currentX)
				{

					if ((*_iOpenTile)->g > _EnemyAStar[_currentY][_currentX]->g + 10)
					{
						_EnemyAStar[_currentY - 1][_currentX]->EnemyStar = _EnemyAStar[_currentY][_currentX];
						_EnemyAStar[_currentY - 1][_currentX]->g = _EnemyAStar[_currentY][_currentX]->g + 10;
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
				_EnemyAStar[_currentY - 1][_currentX]->EnemyStar = _EnemyAStar[_currentY][_currentX];
				_EnemyAStar[_currentY - 1][_currentX]->g = _EnemyAStar[_currentY][_currentX]->g + 10;
				_OpenTile.push_front(_EnemyAStar[_currentY - 1][_currentX]);
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


			if (_EnemyAStar[_currentY + 1][_currentX]->isblock == true)
			{
				_locCheck[3] = true;
			}


			for (_iOpenTile = _OpenTile.begin(); _iOpenTile != _OpenTile.end(); _iOpenTile++)
			{
				if ((*_iOpenTile)->index.y == _currentY + 1 && (*_iOpenTile)->index.x == _currentX)
				{

					if ((*_iOpenTile)->g > _EnemyAStar[_currentY][_currentX]->g + 10)
					{
						_EnemyAStar[_currentY + 1][_currentX]->EnemyStar = _EnemyAStar[_currentY][_currentX];
						_EnemyAStar[_currentY + 1][_currentX]->g = _EnemyAStar[_currentY][_currentX]->g + 10;
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
				_EnemyAStar[_currentY + 1][_currentX]->EnemyStar = _EnemyAStar[_currentY][_currentX];
				_EnemyAStar[_currentY + 1][_currentX]->g = _EnemyAStar[_currentY][_currentX]->g + 10;
				_OpenTile.push_front(_EnemyAStar[_currentY + 1][_currentX]);
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
				_giveIdx.x = _EnemyAStar[_currentY][_currentX]->index.x;
				_giveIdx.y = _EnemyAStar[_currentY][_currentX]->index.y;
			}

			_LoadTile.push_back({ _EnemyAStar[_currentY][_currentX]->index.x,_EnemyAStar[_currentY][_currentX]->index.y });
			playX = _EnemyAStar[_currentY][_currentX]->EnemyStar->index.x;
			playY = _EnemyAStar[_currentY][_currentX]->EnemyStar->index.y;

			_currentX = playX;
			_currentY = playY;
		}
		_isStopEndG = false;
	}
}

void EnemyAstar::render(float cameraX, float cameraY)
{
}

void EnemyAstar::drawRhombus(int left, int top, float cameraX, float cameraY)
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

void EnemyAstar::setAstar()
{
	_EnemyAStar.clear();

	_compareInt = 5000;

	_OpenTile.clear();
	_CloseTile.clear();
	_LoadTile.clear();

	for (int i = 0; i < _battle->getTileY(); i++)
	{
		vector<EnemyMoving*> _tempV;
		_tempV.clear();
		for (int j = 0; j < _battle->getTileX(); j++)
		{
			EnemyMoving* _tempTile = new EnemyMoving;
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
		_EnemyAStar.push_back(_tempV);
	}

	_OpenTile.push_back(_EnemyAStar[_startIdx.y][_startIdx.x]);
	_isStart = true;
}
