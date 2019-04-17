#pragma once
#include "singletonBase.h"
#include <time.h>
#include <random>

class randomFunction : public singletonBase<randomFunction>
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction()
	{}

	//int�� �������� �̾ƺ���
	inline int getInt(int num) { return rand() % num; }


	//������ ���ؼ� ������ �̾ƺ���
	                      //    5            10
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum) + fromNum;
	}

	inline float getFloat() { return (float)rand() / (float)RAND_MAX; }

	inline float getFloat(float num) { return ((float)rand() / (float)RAND_MAX) * num; }

	//������ �Ҽ��� �޾ƿ��� �Լ�
	inline float getFromFloatTo(float fromFloat, float toFloat)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toFloat - fromFloat) + fromFloat);
	}

	//�޸��� ���� ���� ���� (min ~ max) �� ���� ����
	int getRandomInt(int min, int max)
	{
		random_device rd;
		mt19937 rEngine(rd());
		uniform_int_distribution<> dist(min, max);
		return static_cast<int>(dist(rEngine));
	}
	//�޸��� ���� �Ǽ� ���� (min ~ max) �� ���� ����
	float getRandomFloat(float min, float max)
	{
		random_device rd;
		mt19937 rEngine(rd());
		uniform_real_distribution<> dist(min, max);
		return static_cast<float>(dist(rEngine));
	}
};