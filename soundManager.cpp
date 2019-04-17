#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
	:_system(NULL),
	_channel(NULL),
	_sound(NULL)
{
}


soundManager::~soundManager()
{

}

HRESULT soundManager::init()
{
	//FMOD ���� ������ ����ϰڴٰ� ����
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	memset(_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));



	return S_OK;
}

void soundManager::release()
{
	//���� ����
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}

			if (_sound != NULL)
			{
				if (_sound != NULL) _sound[i]->release();
			}
		}
	}

	//�޸� �����
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	//�ý��� �ݱ� 
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

void soundManager::update()
{
	//���� System ��������� ������Ʈ
	_system->update();

	//������ �ٲ�ų� 
	//����� ���� ���带 ä�ο��� �����µ��� �پ���
	//�۾��� �ڵ����� ���ش�
}


void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void soundManager::play(string keyName, float volume)// 0.0 ~ 1.0f -> 0 ~ 255
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			_channel[count]->setVolume(volume);
			break;
		}
	}
}

void soundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void soundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

void soundManager::mute(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{

			(_channel[count]->setVolume(volume));


			break;
		}
	}
}

void soundManager::remute(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			(_channel[count]->setVolume(volume));

			break;
		}
	}
}

void soundManager::volume(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			(_channel[count]->setVolume(volume));
			break;
		}
	}

}


bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}
	return isPause;
}

int soundManager::getLength(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	unsigned int Length = 0;
	unsigned int ms = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_sound[count]->getLength(&Length, FMOD_TIMEUNIT_MS);
			_channel[count]->getPosition(&ms, FMOD_TIMEUNIT_MS);
			break;
		}
	}

	return Length;
}

int soundManager::getMs(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	unsigned int Length = 0;
	unsigned int ms = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_sound[count]->getLength(&Length, FMOD_TIMEUNIT_MS);
			_channel[count]->getPosition(&ms, FMOD_TIMEUNIT_MS);
			break;
		}
	}

	return ms;
}

int soundManager::setMs(string keyName, int x)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPosition(x, FMOD_TIMEUNIT_MS);
			break;
		}
	}

	return x;

}