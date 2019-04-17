#include "stdafx.h"
#include "EnemyManager.h"


EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::init(string PlayerName, const char * imageName, int x, int y)
{

	_enemy.name = PlayerName;
	_enemy.image = IMAGEMANAGER->findImage(imageName);
	_enemy.x = x;
	_enemy.y = y;
	_enemy.isAttack = false;
	_enemy.isSkill = false;
	_enemy.isSynergySkill = false;

	return S_OK;
}

void EnemyManager::release()
{
}

void EnemyManager::update()
{
}

void EnemyManager::render(float cameraX, float cameraY)
{
}

void EnemyManager::initState(int hp, int mp, int AtkDemage, int AtkDefence, int MgDemage, int MgDefence, int move, int jump, int speed, int Accuracy, int level, int exp)
{
	_enemy.currentHP = _enemy.MaxHp = hp;
	_enemy.currentMp = _enemy.MaxMp = mp;
	_enemy.AttackDemage = AtkDemage;
	_enemy.AttackDefence = AtkDefence;
	_enemy.MagicDemage = MgDemage;
	_enemy.MagicDefence = MgDefence;
	_enemy.Move = move;
	_enemy.jump = jump;
	_enemy.Speed = speed;
	_enemy.Accuracy = Accuracy;
	_enemy.Level = level;
	_enemy.Exp = exp;
}
