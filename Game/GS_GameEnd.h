#pragma once
#include"GameState.h"
#include"Main.h"
#include"CButton.h"
#include"CButtonCircle.h"
#include"CButtonRectangle.h"

#include"UserDataManager.h"
#include "Testbed\Tests\AddPair.h"
class GS_GameEnd : public GameState
{
public:
	GS_GameEnd();
	~GS_GameEnd();
	GS_GameEnd(ESContext *esContext);

	//load file 
	bool LoadResouces();
	void Render(ESContext *esContext);
	void Update(ESContext * esContext, float deltaTime);
	GS_TYPE OnEvent(Event * _event);

	void GetScoreAndCheckNewHighscore();
	virtual void Create();
	virtual void Release();

	virtual void TouchActionDown(int x, int y);
	virtual void TouchActionUp(int x, int y);
	virtual void TouchActionMove(int x, int y, int currentX, int currentY);
	//virtual void Key(unsigned char key, bool bIsPressed);
	CButton *m_buttonEnd;


	OBJ_Background *m_OBJ_background;

	float m_TimeLoading;
	static bool m_isNeedLoaded;
	void SetIsLoaded(bool i);
	bool GetIsLoaded();
	int m_iScore;
	bool m_isLoaded;
	bool m_isNewHighScore;

};


