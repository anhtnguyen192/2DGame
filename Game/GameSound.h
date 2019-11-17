#pragma once
#include<iostream>
#include<vector>
#include <SFML/Audio.hpp>

using namespace std;
class GameSound
{
public:
	GameSound();
	~GameSound();
	void Init(char* pathFileSound);
	void Play();
	void SetVolume(float volume);
	void Stop();
	void SetLoop(bool isLoop);
	void SetPitch(float pitch);
	float getVolume() { return m_volume; }
	void SetLocalVolume(float volume) { m_volume = volume; }
private:
	sf::Sound m_sound;
	sf::SoundBuffer m_buffer;
	float m_volume;
};

