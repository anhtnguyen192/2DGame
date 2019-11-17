#include "GS_GameEnd.h"

bool GS_GameEnd::m_isNeedLoaded = true;

GS_GameEnd::GS_GameEnd()
{
	m_type = GS_GAMEEND;
}


GS_GameEnd::~GS_GameEnd()
{
	Release();
	// delete buttons
	delete m_buttonEnd;
	m_buttonEnd = nullptr;
}

GS_GameEnd::GS_GameEnd(ESContext *esContext)
{
	m_isNewHighScore = false;
	m_iScore = 0;
	//m_isLoaded = false;       
	SetIsLoaded(false);
	m_esContext = esContext;
	m_MusicId = 1;
	Create();

	// Create some button to get Event
	m_buttonEnd = new CButtonCircle("END", 270, 300, 50, 4, BUTTON_TRANS_FORWARD);

	// get the background picture
	m_OBJ_background = dynamic_cast<OBJ_Background*>(SceneManager::GetInstance()->GetBackgroundByID(0));

	
}

bool GS_GameEnd::LoadResouces()
{
	m_isLoaded = true;
	return true;
}

void GS_GameEnd::Render(ESContext *esContext)
{
	//Render Something during loading file

	// set environment for render
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// render something 

	//m_OBJ_background->UpdatePosition(Vector3(200, 300, 0));
	//printf("%d\n", m_iScore);
	m_OBJ_background->Render();


	TextManager::GetInstance()->GetTextByID(30)->RenderString();

	if (m_isNewHighScore)
	{
		TextManager::GetInstance()->GetTextByID(31)->RenderString();
	}
	char str[20];
	memset(str, 0, 20);
	_itoa(m_iScore, str, 10);
	TextManager::GetInstance()->GetTextByID(32)->BackWardTextData();
	TextManager::GetInstance()->GetTextByID(32)->PushBackTextData(str);
	TextManager::GetInstance()->GetTextByID(32)->RenderString();

	
	m_buttonEnd->Render();
	// swap buffer 
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);


}

void GS_GameEnd::Update(ESContext * esContext, float deltaTime)
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
	m_buttonEnd->m_OBJ_Button->Update(deltaTime);
	//Update the Sprite Animation for Render button


}

// GS process when an Event is Catch, call in Game's Update, after GS is updated
GS_TYPE GS_GameEnd::OnEvent(Event *_event)
{
	if (_event == m_buttonEnd)
	{
		//printf("Event Handle\n");
		m_event = nullptr;
		return GS_MAINMENU;
	}

}

void GS_GameEnd::GetScoreAndCheckNewHighscore()
{
	m_iScore = Box2DSceneManager::GetInstance()->scores;
	m_isNewHighScore = UserDataManager::GetInstance()->EvaluateNewScore(m_iScore);
}

void GS_GameEnd::Create()
{

	// test Resources file are loaded yet and load file if they aren't loaded
	if (m_isNeedLoaded)
	{
		LoadResouces();
	}
}

// clean up when the GS is released
void GS_GameEnd::Release()
{
	
}

// CALLBACK when Touch Down Event is call
void GS_GameEnd::TouchActionDown(int x, int y)
{
	//printf("down\n");
	
}

// CALLBACK when Touch Up Event is call
void GS_GameEnd::TouchActionUp(int x, int y)
{
	//printf("up\n");
	if (m_buttonEnd->CheckClick(x, y)) m_event = m_buttonEnd;
}

// CALLBACK when Touch Move Event is call
void GS_GameEnd::TouchActionMove(int x, int y, int currentX, int currentY)
{
	//printf("Move\n");
}

//void GS_GameEnd::Key(unsigned char key, bool bIsPressed)
//{
//	if (bIsPressed && key == 0x20 && m_event!=m_buttonEnd)
//	{
//		m_event = m_buttonEnd;
//	}
//}

void GS_GameEnd::SetIsLoaded(bool i)
{
	m_isLoaded = i;
}

bool GS_GameEnd::GetIsLoaded()
{
	return m_isLoaded;
}
