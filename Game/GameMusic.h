#pragma once
#include<iostream>
#include<vector>
#include <SFML/Audio.hpp>

using namespace std;
class GameMusic
{
public:
	GameMusic();
	~GameMusic();
	void Init(char* pathFileMusic);
	void Play();
	void SetVolume(float volume);
	void Pause();
	void Resume();
	void Stop();
	void SetLoop(bool isLoop);
	void SetPitch(float pitch);
	float getVolume() { return m_volume; }
	void SetLocalVolume(float volume) { m_volume = volume; }
private:
	sf::Music m_music;
	//sf::Time m_curTimePlaying;
	float m_volume;
};

