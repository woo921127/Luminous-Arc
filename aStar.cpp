#include "stdafx.h"
#include "aStar.h"


aStar::aStar()
{
}


aStar::~aStar()
{
}

HRESULT aStar::init()
{

	volume = 1.0f;
	effectVolume = 1.0f;
	return S_OK;
}

void aStar::release()
{
}

void aStar::update()
{
}

void aStar::render()
{
}

vector<POINT> aStar::getLoad(POINT start, POINT end, POINT tileNum)
{
	_load.clear();
	_vvMap.clear();
	_OpenTile.clear();
	_CloseTile.clear();

	//초기화
	for (int i = 0; i < tileNum.y; i++)
	{
		vector<aStarTile*> tempTileY;
		tempTileY.clear();
		for (int j = 0; j < tileNum.x; j++)
		{
			aStarTile* tempTile = new aStarTile;
			tempTile->idx.x = j;
			tempTile->idx.y = i;

			for (int k = 0; k < _isWall.size(); k++)
			{
				if (_isWall[k].x == tempTile->idx.x && _isWall[k].y == tempTile->idx.y)
				{
					_CloseTile.push_back(tempTile);
				}
			}

			tempTile->H = (abs(end.x - j) + abs(end.y - i)) * 10;

			if (start.x == tempTile->idx.x && start.y == tempTile->idx.y)
			{
				tempTile->mom = NULL;
				tempTile->G = 0;
				_OpenTile.push_back(tempTile);
			}

			tempTileY.push_back(tempTile);
		}
		_vvMap.push_back(tempTileY);
	}

	//계산시작
	bool isCount = false;

	while (1)
	{
		int tempNum = 10000;
		aStarTile* saveTile;
		POINT currentIdx;

		//모든 F점수계산
		for (int i = 0; i < _OpenTile.size(); i++)
		{
			_OpenTile[i]->F = _OpenTile[i]->G + _OpenTile[i]->H;
		}

		//제일 F점수가 낮은 타일의 주소를 찾음
		for (int i = _OpenTile.size() - 1; i >= 0; i--)
		{
			if (_OpenTile[i]->F < tempNum)
			{
				tempNum = _OpenTile[i]->F;
				saveTile = _OpenTile[i];
				currentIdx.x = _OpenTile[i]->idx.x;
				currentIdx.y = _OpenTile[i]->idx.y;
			}
		}
		//제일 작은 타일 클로즈에 넣음
		for (int i = 0; i < _OpenTile.size(); i++)
		{
			if (_OpenTile[i]->idx.x == currentIdx.x &&
				_OpenTile[i]->idx.y == currentIdx.y)
			{
				_CloseTile.push_back(_OpenTile[i]);
				_OpenTile.erase(_OpenTile.begin() + i);
			}
		}

		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				bool isNoCount = false;
				if (currentIdx.x + j < 0)continue;
				if (currentIdx.y + i < 0)continue;
				if (currentIdx.x + j >= tileNum.x)continue;
				if (currentIdx.y + i >= tileNum.y)continue;
				if (i == 0 && j == 0)continue;

				int plusGScore;
				if (i == -1 && j == -1) continue;
				if (i == -1 && j == 0)plusGScore = 10;
				if (i == -1 && j == 1) continue;
				if (i == 0 && j == -1)plusGScore = 10;
				if (i == 0 && j == 1)plusGScore = 10;
				if (i == 1 && j == -1) continue;
				if (i == 1 && j == 0)plusGScore = 10;
				if (i == 1 && j == 1) continue;



				//닫힌타일 검사
				for (int k = 0; k < _CloseTile.size(); k++)
				{
					if (_CloseTile[k]->idx.x == _vvMap[currentIdx.y + i][currentIdx.x + j]->idx.x &&
						_CloseTile[k]->idx.y == _vvMap[currentIdx.y + i][currentIdx.x + j]->idx.y)
					{
						isNoCount = true;
					}
				}

				//열린타일 검사
				for (int k = 0; k < _OpenTile.size(); k++)
				{
					if (_OpenTile[k]->idx.x == _vvMap[currentIdx.y + i][currentIdx.x + j]->idx.x &&
						_OpenTile[k]->idx.y == _vvMap[currentIdx.y + i][currentIdx.x + j]->idx.y)
					{
						if (_vvMap[currentIdx.y + i][currentIdx.x + j]->G + plusGScore > _OpenTile[k]->G)
						{
							isNoCount = true;
						}
						else if (_vvMap[currentIdx.y + i][currentIdx.x + j]->G + plusGScore < _OpenTile[k]->G)
						{
							_OpenTile[k]->G = _vvMap[currentIdx.y][currentIdx.x]->G + plusGScore;
							_OpenTile[k]->mom = _vvMap[currentIdx.y][currentIdx.x];
							isNoCount = true;
						}
					}
				}

				if (isNoCount == false)
				{
					_vvMap[currentIdx.y + i][currentIdx.x + j]->G = _vvMap[currentIdx.y][currentIdx.x]->G + plusGScore;
					_vvMap[currentIdx.y + i][currentIdx.x + j]->mom = _vvMap[currentIdx.y][currentIdx.x];
					_OpenTile.push_back(_vvMap[currentIdx.y + i][currentIdx.x + j]);
				}
			}
		}

		//끝점이 들어왓는가?
		for (int i = 0; i < _OpenTile.size(); i++)
		{
			if (_OpenTile[i]->idx.x == end.x && _OpenTile[i]->idx.y == end.y)
			{
				isCount = true;
				loadIdx.x = end.x;
				loadIdx.y = end.y;
			}
		}

		if (isCount == true)
		{
			break;
		}

		if (_OpenTile.size() == 0)
		{
			loadIdx.x = currentIdx.x;
			loadIdx.y = currentIdx.y;
			break;
		}
	}

	while (1)
	{
		POINT tempLoad;
		tempLoad.x = loadIdx.x;
		tempLoad.y = loadIdx.y;

		_load.push_back(tempLoad);

		if (_vvMap[loadIdx.y][loadIdx.x]->mom != NULL)
		{
			loadIdx.x = _vvMap[tempLoad.y][tempLoad.x]->mom->idx.x;
			loadIdx.y = _vvMap[tempLoad.y][tempLoad.x]->mom->idx.y;
		}
		else
		{
			break;
		}
	}

	return _load;
}

void aStar::closeTile(POINT idx)
{
	bool isCheck = false;
	for (int i = 0; i < _isWall.size(); i++)
	{
		if (idx.x == _isWall[i].x && idx.y == _isWall[i].y)
		{
			isCheck = true;
		}
	}
	if (isCheck == false)
	{
		_isWall.push_back(idx);
	}
}

void aStar::openTile(POINT idx)
{
	for (int i = 0; i < _isWall.size(); i++)
	{
		if (idx.x == _isWall[i].x && idx.y == _isWall[i].y)
		{
			_isWall.erase(_isWall.begin() + i);
		}
	}
}