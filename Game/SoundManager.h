#pragma once
#include"GameMusic.h"
#include"GameSound.h"
class SoundManager
{
private:
	SoundManager();
	~SoundManager();

public:
	static SoundManager* GetInstance();
	static void DestroyInstance();
	void Init(char* pathFile);
	void Update();
	void SetVolumeMusic(float volume) { m_volumeMusic = volume; }
	float GetVolumeMusic() { return m_volumeMusic; }
	void VolumeMusicUp() { m_volumeMusic += 4; if (m_volumeMusic > 100) m_volumeMusic = 100; }
	void VolumeMusicDow() { m_volumeMusic -= 4; if (m_volumeMusic < 0) m_volumeMusic = 0;}
	void SetVolumeSound(float volume) { m_volumeSound = volume; }
	float GetVolumeSound() { return m_volumeSound; }
	void VolumeSoundUp() { m_volumeSound += 4; if (m_volumeSound > 100) m_volumeSound = 100; }
	void VolumeSoundDow() { m_volumeSound -= 4; if (m_volumeSound < 0) m_volumeSound = 0; }

	static SoundManager* m_pInstance;
	vector<GameMusic*> m_aMusic;
	vector<GameSound*> m_aSound;
private:
	float m_volumeMusic;
	float m_volumeSound;
};

