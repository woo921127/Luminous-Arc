#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

HRESULT Player::init(string PlayerName, const char * imageName, int x, int y)
{
	_player.name = PlayerName;
	_player.image = IMAGEMANAGER->findImage(imageName);
	_player.x = x;
	_player.y = y;
	_player.isAttack = false;
	_player.isSkill = false;
	_player.isSynergySkill = false;
	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
}

void Player::render(float cameraX, float cameraY)
{

}

void Player::initState(int hp, int mp, int AtkDemage, int AtkDefence, int MgDemage, int MgDefence, int move, int jump, int speed, int Accuracy, int level, int exp)
{
	_player.currentHP = _player.MaxHp = hp;
	_player.currentMp = _player.MaxMp = mp;
	_player.AttackDemage = AtkDemage;
	_player.AttackDefence = AtkDefence;
	_player.MagicDemage = MgDemage;
	_player.MagicDefence = MgDefence;
	_player.Move = move;
	_player.jump = jump;
	_player.Speed = speed;
	_player.Accuracy = Accuracy;
	_player.Level = level;
	_player.Exp = exp;
}

