#include "stdafx.h"
#include "GameState.h"



GameState::GameState()
{
}

GameState::GameState(ESContext *esContext)
{
	m_esContext = esContext;
}





GameState::~GameState()
{
}

void GameState::Create()
{
}

void GameState::Release()
{

}

GS_TYPE GameState::OnEvent(Event *_event)
{
	return GS_NULL;
}

void GameState::TouchActionDown(int x, int y)
{
}

void GameState::TouchActionUp(int x, int y)
{
}

void GameState::TouchActionMove(int x, int y, int currentX, int currentY)
{
}

void GameState::Key(unsigned char key, bool bIsPressed)
{
	// do some thing to create event when touch key
}

int GameState::ChangeInMusicID(int id)
{
	return id % 8;
}



