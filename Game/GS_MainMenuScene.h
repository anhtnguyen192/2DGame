
#pragma once
#include"GameState.h"
#include"Main.h"
#include"CButton.h"
#include"CButtonCircle.h"
#include"CButtonRectangle.h"
class GS_MainMenuScene : public GameState
{
public:
	GS_MainMenuScene();
	~GS_MainMenuScene();
	GS_MainMenuScene(ESContext *esContext);

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

	CButton *m_buttonPlay;
	//CButton *m_buttonQuit;
	CButton* m_buttonOption;
	CButton* m_butonCredit;
	//CButton* m_buttonPet;
	//CButton* m_buttonCharacter;
	CButton* m_buttonHighScore;
	
	OBJ_Background *m_OBJ_background;

	float m_TimeLoading;
	static bool m_isNeedLoaded;
	void SetIsLoaded(bool i);
	bool GetIsLoaded();

	bool m_isLoaded;
	float timeCount;
};

