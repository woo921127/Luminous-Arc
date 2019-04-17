#include "stdafx.h"
#include "playGround.h"
#pragma warning(disable:4996)

playGround::playGround()
{
}


playGround::~playGround()
{
}


HRESULT playGround::init()
{
	gameNode::init(true);
	
	//=====================맵툴쪽 이미지===========================//
	IMAGEMANAGER->addImage("back", "image\\toolBack.bmp", 1800, 800, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("isoZtile", "isotile\\isotile.bmp", 768, 256, 6, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("isoZtile1", "isotile\\Ztile1.bmp", 768, 384, 6, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("checkPoint", "image\\checkPoint.bmp", 1536, 64, 12, 1,true,MAGENTA);
	IMAGEMANAGER->addImage("save", "isotile\\save.bmp", 119, 49, true, MAGENTA);
	IMAGEMANAGER->addImage("load", "isotile\\load.bmp", 119, 49, true, MAGENTA);
	//=====================플레이어 이미지============================//
	IMAGEMANAGER->addFrameImage("alph", "image\\Alph.bmp", 1536, 440, 24, 5, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("lucia", "image\\Lucia.bmp", 1800, 500, 18, 5, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("alph2", "image\\Alph2.bmp", 2400, 540, 24, 6, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("lucia2", "image\\Lucia2.bmp", 1800, 880, 18, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Iris", "image\\Iris.bmp", 2160, 600, 24, 6, true, MAGENTA);
	//=====================게임 이미지=================================//
	IMAGEMANAGER->addImage("move", "image\\move.bmp", 200, 50, true, MAGENTA);
	IMAGEMANAGER->addImage("move2", "image\\move2.bmp", 200, 50, true, MAGENTA);
	IMAGEMANAGER->addImage("action", "image\\action.bmp", 200, 50, true, MAGENTA);
	IMAGEMANAGER->addImage("action2", "image\\action2.bmp", 200, 50, true, MAGENTA);
	IMAGEMANAGER->addImage("attack", "image\\attack.bmp", 200, 50, true, MAGENTA);
	IMAGEMANAGER->addImage("attack2", "image\\attack2.bmp", 200, 50, true, MAGENTA);
	IMAGEMANAGER->addImage("magic", "image\\magic.bmp", 200, 50, true, MAGENTA);
	IMAGEMANAGER->addImage("magic2", "image\\magic2.bmp", 200, 50, true, MAGENTA);
	IMAGEMANAGER->addImage("synergy", "image\\synergy.bmp", 200, 50, true, MAGENTA);
	IMAGEMANAGER->addImage("synergy2", "image\\synergy2.bmp", 200, 50, true, MAGENTA);
	IMAGEMANAGER->addImage("wait", "image\\wait.bmp", 200, 50, true, MAGENTA);
	IMAGEMANAGER->addImage("wait2", "image\\wait2.bmp", 200, 50, true, MAGENTA);


	//======================이펙트 이미지================================//
	
	IMAGEMANAGER->addFrameImage("fire2", "effectImage\\fire2.bmp", 5000, 109, 26, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("fireBomb", "effectImage\\effect.bmp", 600, 161, 4, 1, true, MAGENTA);
	IMAGEMANAGER->addImage("Synerge", "effectImage\\Synerge.bmp", 1036, 768, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Syattack", "effectImage\\SynergeAttack.bmp", 29008, 768, 28, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Syattack2", "effectImage\\SynergeAttack2.bmp", 29008, 768, 28, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Syattack3", "effectImage\\SynergeAttack3.bmp", 29008, 768, 28, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Syattack4", "effectImage\\SynergeAttack4.bmp", 29008, 768, 28, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Syattack5", "effectImage\\SynergeAttack5.bmp", 14504, 768, 14, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("puple2", "effectImage\\puple2.bmp", 700, 100, 7, 1, true, MAGENTA);
	//======================스테이터스 이미지==============================//

	IMAGEMANAGER->addImage("state", "StateImage\\StateImage2.bmp", 768, 500, true, MAGENTA);
	IMAGEMANAGER->addImage("alphLog", "StateImage\\alphLog.bmp", 139, 156, true, MAGENTA);
	IMAGEMANAGER->addImage("luciaLog", "StateImage\\luciaLog.bmp", 139, 156, true, MAGENTA);
	IMAGEMANAGER->addImage("edge", "StateImage\\edge.bmp", 139, 156, true, MAGENTA);
	IMAGEMANAGER->addImage("irisLog", "StateImage\\irisLog.bmp", 139, 156, true, MAGENTA);
	IMAGEMANAGER->addImage("Hpbar", "StateImage\\HpBar.bmp", 242, 26, true, MAGENTA);
	IMAGEMANAGER->addImage("Mpbar", "StateImage\\MpBar.bmp", 242, 26, true, MAGENTA);
	IMAGEMANAGER->addImage("Fpbar", "StateImage\\FpBar.bmp", 242, 26, true, MAGENTA);
	IMAGEMANAGER->addImage("alphName", "StateImage\\alph.bmp", 100, 40, true, MAGENTA);
	IMAGEMANAGER->addImage("luciaName", "StateImage\\lucia.bmp", 100, 40, true, MAGENTA);
	IMAGEMANAGER->addImage("irisName", "StateImage\\iris.bmp", 100, 40, true, MAGENTA);
	IMAGEMANAGER->addImage("human", "StateImage\\human.bmp", 100, 40, true, MAGENTA);
	IMAGEMANAGER->addImage("witch", "StateImage\\witch.bmp", 100, 40, true, MAGENTA);
	IMAGEMANAGER->addImage("Notice", "StateImage\\statenotice.bmp", 768, 268, true, MAGENTA);
	IMAGEMANAGER->addImage("slash", "StateImage\\slash.bmp", 20, 20, true, MAGENTA);
	IMAGEMANAGER->addImage("level", "StateImage\\Level.bmp", 71, 31, true, MAGENTA);
	IMAGEMANAGER->addImage("hp", "StateImage\\Hp.bmp", 242, 52, true, MAGENTA);
	IMAGEMANAGER->addImage("mp", "StateImage\\Mp.bmp", 242, 52, true, MAGENTA);
	IMAGEMANAGER->addImage("fp", "StateImage\\Fp.bmp", 242, 52, true, MAGENTA);
	IMAGEMANAGER->addImage("atkDef", "StateImage\\AtkDef.bmp", 41, 51, true, MAGENTA);
	IMAGEMANAGER->addImage("mgcDef", "StateImage\\MgcDef.bmp", 41, 51, true, MAGENTA);
	IMAGEMANAGER->addImage("equl", "StateImage\\equl.bmp", 17, 28, true, MAGENTA);

	//-----------------------------숫자-------------------------------------//

	IMAGEMANAGER->addImage("zero", "StateImage\\zero.bmp", 25, 25, true, MAGENTA);
	IMAGEMANAGER->addImage("one", "StateImage\\one.bmp", 25, 25, true, MAGENTA);
	IMAGEMANAGER->addImage("two", "StateImage\\two.bmp", 25, 25, true, MAGENTA);
	IMAGEMANAGER->addImage("three", "StateImage\\three.bmp", 25, 25, true, MAGENTA);
	IMAGEMANAGER->addImage("four", "StateImage\\four.bmp", 25, 25, true, MAGENTA);
	IMAGEMANAGER->addImage("five", "StateImage\\five.bmp", 25, 25, true, MAGENTA);
	IMAGEMANAGER->addImage("six", "StateImage\\six.bmp", 25, 25, true, MAGENTA);
	IMAGEMANAGER->addImage("seven", "StateImage\\seven.bmp", 25, 25, true, MAGENTA);
	IMAGEMANAGER->addImage("eight", "StateImage\\eight.bmp", 25, 25, true, MAGENTA);
	IMAGEMANAGER->addImage("nine", "StateImage\\nine.bmp", 25, 25, true, MAGENTA);


	IMAGEMANAGER->addImage("semizero", "StateImage\\semizero.bmp", 15, 15, true, MAGENTA);
	IMAGEMANAGER->addImage("semione", "StateImage\\semione.bmp", 15, 15, true, MAGENTA);
	IMAGEMANAGER->addImage("semitwo", "StateImage\\semitwo.bmp", 15, 15, true, MAGENTA);
	IMAGEMANAGER->addImage("semithree", "StateImage\\semithree.bmp", 15, 15, true, MAGENTA);
	IMAGEMANAGER->addImage("semifour", "StateImage\\semifour.bmp", 15, 15, true, MAGENTA);
	IMAGEMANAGER->addImage("semifive", "StateImage\\semifive.bmp", 15, 15, true, MAGENTA);
	IMAGEMANAGER->addImage("semisix", "StateImage\\semisix.bmp", 15, 15, true, MAGENTA);
	IMAGEMANAGER->addImage("semiseven", "StateImage\\semiseven.bmp", 15, 15, true, MAGENTA);
	IMAGEMANAGER->addImage("semieight", "StateImage\\semieight.bmp", 15, 15, true, MAGENTA);
	IMAGEMANAGER->addImage("seminine", "StateImage\\seminine.bmp", 15, 15, true, MAGENTA);


	IMAGEMANAGER->addFrameImage("number", "StateImage\\Number.bmp", 150, 15, 10, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("number2", "StateImage\\Number2.bmp", 250, 25, 10, 1, true, MAGENTA);

	//========================게임 백그라운드 이미지======================//
	
	IMAGEMANAGER->addImage("gameBack", "StateImage\\Gameback.bmp", 1030, 768, true, MAGENTA);

	//====================================================================//
	//타이틀 이미지

	IMAGEMANAGER->addImage("Title", "TitleImage\\Title.bmp", 1024, 768, true, MAGENTA);
	IMAGEMANAGER->addImage("Logo", "TitleImage\\logo.bmp", 600, 300, true, MAGENTA);
	IMAGEMANAGER->addImage("Start", "TitleImage\\Start.bmp", 300, 100, true, MAGENTA);
	IMAGEMANAGER->addImage("Start2", "TitleImage\\Start2.bmp", 300, 100, true, MAGENTA);
	IMAGEMANAGER->addImage("Maptool", "TitleImage\\Maptool.bmp", 300, 100, true, MAGENTA);
	IMAGEMANAGER->addImage("Maptool2", "TitleImage\\Maptool2.bmp", 300, 100, true, MAGENTA);
	IMAGEMANAGER->addImage("Option", "TitleImage\\Option.bmp", 300, 100, true, MAGENTA);
	IMAGEMANAGER->addImage("Option2", "TitleImage\\Option2.bmp", 300, 100, true, MAGENTA);
	IMAGEMANAGER->addImage("BGM", "TitleImage\\BGM.bmp", 200, 30, true, MAGENTA);
	IMAGEMANAGER->addImage("BGM2", "TitleImage\\BGM2.bmp", 200, 30, true, MAGENTA);
	IMAGEMANAGER->addImage("Effect", "TitleImage\\Effect.bmp", 200, 30, true, MAGENTA);
	IMAGEMANAGER->addImage("Effect2", "TitleImage\\Effect2.bmp", 200, 30, true, MAGENTA);
	IMAGEMANAGER->addImage("Edge2", "TitleImage\\Edge2.bmp", 400, 400, true, MAGENTA);

	//======================================================================//



	//==============================사운드======================================//
	SOUNDMANAGER->addSound("TitleBGM", "Sound/Title.mp3", true, true);
	SOUNDMANAGER->addSound("BattleBGM", "Sound/Battle.mp3", true, true);
	SOUNDMANAGER->addSound("MapToolBGM", "Sound/mapTool.mp3", true, true);
	SOUNDMANAGER->addSound("Synerge", "Sound/Synerge.mp3", true, false);
	SOUNDMANAGER->addSound("choice", "Sound/choice.mp3", true, false);
	SOUNDMANAGER->addSound("back", "Sound/back.mp3", true, false);
	SOUNDMANAGER->addSound("move", "Sound/move.mp3", true, false);
	SOUNDMANAGER->addSound("Sword", "Sound/Sword.mp3", true, false);
	SOUNDMANAGER->addSound("spear", "Sound/spear.mp3", true, false);
	SOUNDMANAGER->addSound("bomb", "Sound/bomb.mp3", true, false);
	SOUNDMANAGER->addSound("fire", "Sound/fire.mp3", true, false);
	SOUNDMANAGER->addSound("magic", "Sound/magic.mp3", true, false);
	//========================================================================//
	SCENEMANAGER->addScene("메트릭스", new isoMetricScene);
	SCENEMANAGER->addScene("맵툴", new mapTool);
	SCENEMANAGER->addScene("배틀", new battleScene);
	SCENEMANAGER->addScene("타이틀", new TitleScene);
	SCENEMANAGER->addScene("옵션", new OptionScene);

	SCENEMANAGER->changeScene("타이틀");

	return S_OK;
}


void playGround::release()
{
	gameNode::release();

}


void playGround::update()
{
	gameNode::update();

	KEYANIMANAGER->update();
	SCENEMANAGER->update();


	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("맵툴");
	}

}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===========================================================

	SCENEMANAGER->render();
	KEYANIMANAGER->render();

	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TIMEMANAGER->render(getMemDC());
	//===========================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

