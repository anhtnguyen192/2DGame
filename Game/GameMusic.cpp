#include "GameMusic.h"



GameMusic::GameMusic()
{
	m_volume = 50;
}


GameMusic::~GameMusic()
{
}

void GameMusic::Init(char* pathFileMusic)
{
	if (!m_music.openFromFile(pathFileMusic))
	{
		std::cout << "Can't load file " << pathFileMusic << endl;
	}
	m_music.setVolume(m_volume);
	m_music.setLoop(true);
}


void GameMusic::Play()
{
	//m_music.setPlayingOffset(sf::seconds(n_sec));
	m_music.play();
}

void GameMusic::Pause()
{
	//m_curTimePlaying = m_music.getPlayingOffset();
	m_music.pause();
}

void GameMusic::Resume()
{
	//m_music.setPlayingOffset(m_curTimePlaying);
	m_music.play();
}

void GameMusic::Stop()
{
	m_music.stop();
}

void GameMusic::SetVolume(float volume)
{
	//m_volume = volume;
	m_music.setVolume(m_volume*volume*0.01);
}

void GameMusic::SetLoop(bool isLoop = true)
{
	m_music.setLoop(isLoop);
}

void GameMusic::SetPitch(float pitch)
{
	m_music.setPitch(pitch);
}
