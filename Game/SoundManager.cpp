#include "SoundManager.h"

SoundManager* SoundManager::m_pInstance = nullptr;

SoundManager::SoundManager()
{
	m_volumeMusic = 60;
	m_volumeSound = 60;
}


SoundManager::~SoundManager()
{
	for (int i = 0; i < m_aMusic.size(); i++)
	{
		delete m_aMusic[i];
	}
	m_aMusic.clear();

	for (int i = 0; i < m_aSound.size(); i++)
	{
		delete m_aSound[i];
	}
	m_aSound.clear();

}


SoundManager* SoundManager::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new SoundManager;
	}
	return m_pInstance;
}

void SoundManager::DestroyInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void SoundManager::Init(char* pathFile)
{
	FILE* f = fopen(pathFile, "r");
	if (!f)
	{
		cout << "Can't read sound manager file!" << endl;
	}
	
	int count = 0;
	int id;
	float volume;
	char buffer[1024];
	fscanf(f, "#MUSIC %d\n", &count);
	for (int i = 0; i < count; i++)
	{
		fscanf(f, "ID %d\n", &id);
		memset(buffer, 0, 1024);
		fscanf(f, "FILE %s\n", buffer);
		fscanf(f, "VOLUME %f\n", &volume);

		GameMusic* music = new GameMusic;
		music->Init(buffer);
		music->SetLocalVolume(volume);
		music->SetVolume(volume*m_volumeMusic*0.01);
		m_aMusic.push_back(music);
	}

	fscanf(f, "\n#SOUND %d\n", &count);
	for (int i = 0; i < count; i++)
	{
		fscanf(f, "ID %d\n", &id);
		memset(buffer, 0, 1024);
		fscanf(f, "FILE %s\n", buffer);
		fscanf(f, "VOLUME %f\n", &volume);

		GameSound* sound = new GameSound;
		sound->Init(buffer);
		sound->SetLocalVolume(volume);
		sound->SetVolume(volume*m_volumeSound*0.01);
		m_aSound.push_back(sound);
	}

}

void SoundManager::Update()
{
	for (int i = 0; i < m_aMusic.size(); i++)
	{
		m_aMusic[i]->SetVolume(m_volumeMusic);
	}

	for (int i = 0; i < m_aSound.size(); i++)
	{
		m_aSound[i]->SetVolume(m_volumeSound);
	}
}
