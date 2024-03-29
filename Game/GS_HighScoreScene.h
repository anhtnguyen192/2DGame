#pragma once
#include"GameState.h"
#include"Main.h"
#include"CButton.h"
#include"CButtonCircle.h"
#include"CButtonRectangle.h"
#include"UserDataManager.h"
class GS_HighScoreScene : public GameState
{
public:
	GS_HighScoreScene();
	~GS_HighScoreScene();
	GS_HighScoreScene(ESContext *esContext);

	//load file 
	bool LoadResouces();
	void Render(ESContext *esContext);
	void Update(ESContext * esContext, float deltaTime);
	GS_TYPE OnEvent(Event * _event);


	virtual void Create();
	virtual void Release();

	virtual void TouchActionDown(int x, int y);
	virtual void TouchActionUp(int x, int y);
	virtual void TouchActionMove(int x, int y, int currentX, int currentY);
	//virtual void Key(unsigned char key, bool bIsPressed);
	CButton *m_buttonBack;


	OBJ_Background *m_OBJ_background;

	float m_TimeLoading;
	static bool m_isNeedLoaded;
	void SetIsLoaded(bool i);
	bool GetIsLoaded();

	bool m_isLoaded;
};


