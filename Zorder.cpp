#include "stdafx.h"
#include "Zorder.h"
#include "gameNode.h"

Zorder::Zorder()
{
}


Zorder::~Zorder()
{
}

HRESULT Zorder::init()
{
	return S_OK;

}

void Zorder::InPutObj(gameNode * obj)
{
	vZer.push_back(obj);
}

void Zorder::render(float cameraX, float cameraY)
{
	for (int i = 0; i < vZer.size(); ++i)
	{
		vZer[i]->render(cameraX,cameraY);
	}

}

void Zorder::update()
{
	for (int i = 0; i < vZer.size(); ++i)
	{
		if (i < vZer.size() - 1)
		{
			if (vZer[i]->getZorderY() > vZer[i + 1]->getZorderY())
			{
				gameNode* temp = vZer[i];
				vZer[i] = vZer[i + 1];
				vZer[i + 1] = temp;
			}

			if (vZer[i]->getZorderY() == vZer[i + 1]->getZorderY())
			{
			}
		}
	}
}

void Zorder::Release()
{
	vZer.clear();
}
