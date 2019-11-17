#include "stdafx.h"
#include "Testbed\Tests\AddPair.h"
#include "Main.h"
#include <iostream>
#include<conio.h>
#include <SFML/Audio.hpp>
#include"Game.h"


//int main() 
//{
//	//sf::Music music;
//	//if (!music.openFromFile("ADAMAS.wav"))
//	//	return -1; // error
//	//music.play();
//	//getchar();
//	return 0;
//}

//Game* m_game;

int m_iCurrentMouseX;
int m_iCurrentMouseY;
void Change(int &x, int &y)
{
	x = x;
	y = Globals::screenHeight - y;
}

//int Init(ESContext *esContext)
//{
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//	ResourcesManager::GetInstance()->Init("../Resources/ResourcesManeger.txt");
//	SceneManager::GetInstance()->Init("../Resources/SceneManager.txt");
//	TextManager::GetInstance()->Init("../Resources/TextManager.txt");
//	SoundManager::GetInstance()->Init("../Resources/SoundManager.txt");
//	SoundManager::GetInstance()->m_aMusic[0]->Play();
//	SceneManager::GetInstance()->LinkObjects();
//	return 0;
//}

void Draw(ESContext *esContext)
{
	/*glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SceneManager::GetInstance()->Render();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);*/
	Game::GetInstance()->Render(esContext);
}

void Update(ESContext *esContext, float deltaTime)
{
	/*SceneManager::GetInstance()->Update(deltaTime);*/
	Game::GetInstance()->Update(esContext, deltaTime);
}

void Key(ESContext *esContext, unsigned char key, bool bIsPressed)
{
	//SceneManager::GetInstance()->CheckKey(key, bIsPressed);
	//printf("%c %x\n", key,key);
	Game::GetInstance()->Key(esContext, key, bIsPressed);
}


void CleanUp()
{
	Game::GetInstance()->Release();
	Game::GetInstance()->DestroyInstance();
	/*ResourcesManager::GetInstance()->DestroyInstance();
	SceneManager::GetInstance()->DestroyInstance();
	TextManager::GetInstance()->DestroyInstance();
	SoundManager::GetInstance()->DestroyInstance();
	Camera::GetInstance()->DestroyInstance();*/
}

void TouchActionDown(ESContext *esContext, int x, int y)
{
	Game::GetInstance()->TouchActionDown(esContext, x, y);
	//// Mouse down
	//Change(x, y);
	//m_iCurrentMouseX = x;
	//m_iCurrentMouseY = y;
	////SceneManager::GetInstance()->ChangeDown(x, y);
	//printf("%d, %d\n", x, y);
	
}

void TouchActionUp(ESContext *esContext, int x, int y)
{
	Game::GetInstance()->TouchActionUp(esContext, x, y);
	// Mouse up
	/*SceneManager::GetInstance()->ChangeUp(x, y);*/
	//sceneManager->MakeIsChosenFalse();
	/*Change(x, y);
	printf("%d, %d\n", x, y);*/
}

void TouchActionMove(ESContext *esContext, int x, int y)
{
	Game::GetInstance()->TouchActionMove(esContext, x, y);
	//// Mouse move
	////SceneManager::GetInstance()->SetCanBeMove();
	//Change(x, y);
	//float fMoveVectorX = x - m_iCurrentMouseX;
	//float fMoveVectorY = y - m_iCurrentMouseY;
	//printf("%d, %d\n", x, y);
	////SceneManager::GetInstance()->ChangeMove(a, b);
	//m_iCurrentMouseX = x;
	//m_iCurrentMouseY = y;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//AddPair::Create();
	//AddPair::GetInstance()->Create();
	ESContext esContext ;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Game", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	/*if (Init(&esContext) != 0)
		return 0;*/
	//m_game = Game::GetInstance();
	Game::GetInstance()->m_esContext = &esContext;

	//Camera::GetInstance()->ShowShotcutKey();
	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);
	esRegisterMouseDownFunc(&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);
	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	/*b2Vec2 gravity(0, 0);
	b2World world(gravity);*/
	
	return 0;
}