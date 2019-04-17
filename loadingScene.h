#pragma once
#include "gameNode.h"

#define LOADINGMAX 30000

class progressBar;

class loadingScene : public gameNode
{
private:
	progressBar* _loadingBar;
	image* _background;

	
public:
	loadingScene();
	~loadingScene();

	int _currentCount;	//�ܺο��� �����Ҽ��ְ� �صд�

	HRESULT init();
	void release();
	void update();
	void render();
	
};

static DWORD CALLBACK ThreadFunction(LPVOID lpParameter);
