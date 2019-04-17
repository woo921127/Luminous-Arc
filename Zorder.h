#pragma once
#include "singletonBase.h"

class gameNode;

class Zorder :public singletonBase<Zorder>
{
private:

	vector<gameNode*> vZer;
	vector<gameNode*>::iterator viZer;


public:
	Zorder();
	~Zorder();


	HRESULT init();
	void render(float cameraX, float cameraY);
	void update();
	void Release();

	void InPutObj(gameNode* obj);
	
	int getZOrderSize() { return vZer.size(); }


	vector<gameNode*> getZsize() { return vZer;}

};

