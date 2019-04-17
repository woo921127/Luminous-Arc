#pragma once
#include "gameNode.h"
#include "Alph.h"
#include "camera.h"
#include "Lucia.h"

class playerManager : public gameNode
{
private:

	float CameraX;
	float CameraY;


	Alph* _alph;
	Lucia* _lucia;



public:
	playerManager();
	~playerManager();

	HRESULT init(int alphX, int alphY, int luciaX, int luciaY);
	void release();
	void update(int alphX, int alphY, int luciaX, int luciaY);
	void render(float cameraX, float cameraY);

//	void setBattleManagerAddressLink(battleMap* battle) { _battle = battle; }



};

