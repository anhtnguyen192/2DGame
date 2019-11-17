#include "GameSound.h"


GameSound::GameSound()
{
	m_volume = 50;
}


GameSound::~GameSound()
{

}

void GameSound::Init(char* pathFileSound)
{
	if (!m_buffer.loadFromFile(pathFileSound))
	{
		std::cout << "Can't load file " << pathFileSound << endl;
	}
	m_sound.setBuffer(m_buffer);
	m_sound.setVolume(m_volume);
	m_sound.setLoop(false);
}

void GameSound::Play()
{
	//m_sound.setPlayingOffset(sf::milliseconds(n_milliSec));
	m_sound.play();
}


void GameSound::Stop()
{
	m_sound.stop();
}

void GameSound::SetVolume(float volume)
{
	//m_volume = volume;
	m_sound.setVolume(m_volume*volume*0.01);
}

void GameSound::SetLoop(bool isLoop = true)
{
	m_sound.setLoop(isLoop);
}

void GameSound::SetPitch(float pitch)
{
	m_sound.setPitch(pitch);
}
