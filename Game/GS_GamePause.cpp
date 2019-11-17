#include "GS_GamePause.h"


bool GS_GamePause::m_isNeedLoaded = true;

GS_GamePause::GS_GamePause()
{
	m_type = GS_GAMEPAUSE;
}


GS_GamePause::~GS_GamePause()
{
	Release();
	// delete buttons
	delete m_buttonResume;
	m_buttonResume = nullptr;
	delete m_buttonExit;
	m_buttonExit = nullptr;
	delete m_buttonOption;
	m_buttonOption = nullptr;
}

GS_GamePause::GS_GamePause(ESContext *esContext)
{
	//m_isLoaded = false;       
	SetIsLoaded(false);
	m_esContext = esContext;
	m_MusicId = 2;
	Create();

	// Create some button to get Event
	m_buttonResume = new CButtonRectangle("RESUME", 270, 650, 400, 100, 20, BUTTON_BACK, 7);
	m_buttonOption = new CButtonRectangle("OPTION", 270, 350, 400, 100, 20, BUTTON_TRANS_FORWARD, 9);
	m_buttonExit = new CButtonRectangle("EXIT", 270, 500, 400, 100, 20, BUTTON_TRANS_FORWARD, 8);

	// get the background picture
	m_OBJ_background = dynamic_cast<OBJ_Background*>(SceneManager::GetInstance()->GetBackgroundByID(0));

	
}

bool GS_GamePause::LoadResouces()
{
	m_isLoaded = true;
	return true;
}

void GS_GamePause::Render(ESContext *esContext)
{
	//Render Something during loading file

	// set environment for render
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// render something 

	//m_OBJ_background->UpdatePosition(Vector3(200, 300, 0));
	//m_OBJ_background->Render();
	m_buttonResume->Render();
	m_buttonExit->Render();
	m_buttonOption->Render();
	// swap buffer 
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);


}

void GS_GamePause::Update(ESContext * esContext, float deltaTime)
{
	// check file all loading done or not
	// if done, change to MainMenu Scene

	// check loading file is done yet
	if (m_isLoaded && m_isNeedLoaded)
	{
		m_isNeedLoaded = false;
		printf("\nLOADING DONE!!\n");
	}

	//Update the Sprite Animation for Render Background
	m_OBJ_background->Update(deltaTime);
	m_buttonResume->m_OBJ_Button->Update(deltaTime);
	m_buttonExit->m_OBJ_Button->Update(deltaTime);
	m_buttonOption->m_OBJ_Button->Update(deltaTime);
	//Update the Sprite Animation for Render button


}

// GS process when an Event is Catch, call in Game's Update, after GS is updated
GS_TYPE GS_GamePause::OnEvent(Event *_event)
{
	if (_event == m_buttonResume)
	{
		//printf("Event Handle\n");
		m_event = nullptr;
		return GS_BACK;
	}
	if (_event == m_buttonExit)
	{
		//printf("Event Handle\n");
		m_event = nullptr;
		return GS_GAMEEND;
	}
	if (_event == m_buttonOption)
	{
		//printf("Event Handle\n");
		m_event = nullptr;
		return GS_OPTIONMENU;
	}

}

void GS_GamePause::Create()
{

	// test Resources file are loaded yet and load file if they aren't loaded
	if (m_isNeedLoaded)
	{
		LoadResouces();
	}

	// Play Music
	//SoundManager::GetInstance()->m_aMusic[0]->Play();

	

}

// clean up when the GS is released
void GS_GamePause::Release()
{
	
}

// CALLBACK when Touch Down Event is call
void GS_GamePause::TouchActionDown(int x, int y)
{
	//printf("down\n");
	
}

// CALLBACK when Touch Up Event is call
void GS_GamePause::TouchActionUp(int x, int y)
{
	//printf("up\n");
	if (m_buttonResume->CheckClick(x, y)) m_event = m_buttonResume;
	if (m_buttonExit->CheckClick(x, y)) m_event = m_buttonExit;
	if (m_buttonOption->CheckClick(x, y)) m_event = m_buttonOption;
}

// CALLBACK when Touch Move Event is call
void GS_GamePause::TouchActionMove(int x, int y, int currentX, int currentY)
{
	//printf("Move\n");
}

void GS_GamePause::SetIsLoaded(bool i)
{
	m_isLoaded = i;
}

bool GS_GamePause::GetIsLoaded()
{
	return m_isLoaded;
}
