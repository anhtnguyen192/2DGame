#pragma once
#include"GS_TYPE.h"
#include"Event.h"
#include"Main.h"
class GameState
{
public:
	GameState();
	GameState(ESContext *esContext);
	virtual ~GameState();
	virtual void Create();
	virtual void Release();
	virtual void Update(ESContext *esContext, float deltaTime) = 0;
	virtual void Render(ESContext *esContext) = 0;
	virtual GS_TYPE OnEvent(Event *_event);
	virtual void TouchActionDown(int x, int y);
	virtual void TouchActionUp(int x, int y);
	virtual void TouchActionMove(int x, int y, int currentX, int currentY);
	virtual void Key(unsigned char key, bool bIsPressed);
	GS_TYPE m_type;
	Event* m_event;
	ESContext *m_esContext;
	int m_MusicId;
	int ChangeInMusicID(int id);
};

