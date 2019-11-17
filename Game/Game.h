#pragma once
#include"Main.h"

#include"GameState.h"
#include"GS_HighScoreScene.h"
#include"GS_CharacterMenuScene.h"
#include"GS_Credit.h"
#include"GS_GamePlayScene.h"
#include"GS_MainMenuScene.h"
#include"GS_OptionMenuScene.h"
#include"GS_PetMenuScene.h"
#include"GS_WelcomeScene.h"
#include"GS_GamePause.h"
#include"GS_GameEnd.h"
//#include"GS_GameEnd.h"

#include<iostream>
#include<stack>
#include<Box2D\Box2D.h>

#define LIMIT_FPS 60
using namespace std;

#include"../../GRAPHIC_ENGINE/Utilities/utilities.h"
#include"../../GRAPHIC_ENGINE/TrainingFramework/TrainingFramework.h"
class Game
{
public:
	static Game *GetInstance();
	virtual void Update(ESContext *esContext, float deltaTime);
	virtual void Render(ESContext *esContext);
	virtual void GoToGS(GS_TYPE _GS_type);
	virtual void OnEvent();
	virtual void DestroyInstance();
	virtual void Release();
	void Change(int &x, int &y);
	
	GameState* GetGameState();

	virtual void TouchActionDown(ESContext *esContext, int x, int y);
	virtual void TouchActionUp(ESContext *esContext, int x, int y);
	virtual void TouchActionMove(ESContext *esContext, int x, int y);
	virtual void Key(ESContext *esContext, unsigned char key, bool bIsPressed);
	void DeleteState(GameState*gs);
	GameState *m_state;
	ESContext *m_esContext;
	stack <GS_TYPE> m_stackGameState;
	//Event*m_Event;

	int m_iCurrentMouseX;
	int m_iCurrentMouseY;

	bool m_isTouchActionDown;
	bool m_isTouchActionUp;
	bool m_isTouchActionMove;
private:
	Game();
	virtual ~Game();

	static Game *s_Instance;
	
	GameState *m_GS_Welcome;
	GameState *m_GS_MainMenu;
	GameState *m_GS_OptionMenu;
	GameState *m_GS_Credit;
	GameState *m_GS_GamePlay;
	GameState *m_GS_HighScore;
	GameState *m_GS_GamePause;
	GameState *m_GS_GameEnd;
	//....

	
};


