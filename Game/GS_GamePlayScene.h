#pragma once
#include"GameState.h"
#include"Main.h"
#include"CButton.h"
#include"CButtonCircle.h"
#include"CButtonRectangle.h"
#include<math.h>
class GS_GamePlayScene : public GameState
{
public:
	GS_GamePlayScene();
	~GS_GamePlayScene();
	GS_GamePlayScene(ESContext *esContext);

	//load file 
	bool LoadResouces();
	void Render(ESContext *esContext);
	void Update(ESContext * esContext, float deltaTime);
	GS_TYPE OnEvent(Event * _event);


	virtual void Create();
	virtual void Release();
	float ChangeSizefromBox2DtoGraphic(float x);
	int ChangeXfromBox2DtoGraphic(float x);
	int ChangeYfromBox2DtoGraphic(float y);
	virtual void TouchActionDown(int x, int y);
	virtual void TouchActionUp(int x, int y);
	virtual void TouchActionMove(int x, int y, int currentX, int currentY);
	

	int Match2DObjectListToObjectRender(int id);


	CButton *m_buttonPause;


	OBJ_Background *m_OBJ_background;
	Event* m_endGame;
	vector<Sprite* > m_ObjectsRender;
	Sprite * m_Objengine;
	float m_TimeLoading;
	static bool m_isNeedLoaded;
	void SetIsLoaded(bool i);
	bool GetIsLoaded();
	float timecount;
	float timeBase;
	bool m_isLoaded;
	bool m_isRender;
	float timeChangeMusic;
};


