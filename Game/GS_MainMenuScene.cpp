#include "GS_MainMenuScene.h"

bool GS_MainMenuScene::m_isNeedLoaded = true;

GS_MainMenuScene::GS_MainMenuScene()
{
	m_type = GS_MAINMENU;
}


GS_MainMenuScene::~GS_MainMenuScene()
{
	Release();
	// delete buttons
	/*delete m_buttonQuit;
	m_buttonQuit = nullptr;*/
	delete m_buttonPlay;
	m_buttonPlay = nullptr;
	delete m_buttonOption;
	m_buttonOption = nullptr;
	delete m_buttonHighScore;
	m_buttonHighScore = nullptr;
	delete m_butonCredit;
	m_butonCredit = nullptr;
}

GS_MainMenuScene::GS_MainMenuScene(ESContext *esContext)
{
	//m_isLoaded = false;       
	SetIsLoaded(false);
	m_esContext = esContext;
	m_MusicId = 5;
	timeCount = 0;
	Create();

	// Create some button to get Event
	m_buttonPlay = new CButtonRectangle("PLAY GAME", 270, 800, 400, 100, 20, BUTTON_TRANS_FORWARD, 2);
	m_buttonOption = new CButtonRectangle("OPTION", 270, 650, 400, 100, 20, BUTTON_TRANS_FORWARD, 4);
	m_buttonHighScore = new CButtonRectangle("HIGH SCORE", 270, 500, 400, 100, 20, BUTTON_TRANS_FORWARD, 5);
	m_butonCredit = new CButtonRectangle("CREDIT", 270, 350, 400, 100, 20, BUTTON_TRANS_FORWARD, 6);
	//m_buttonQuit = new CButtonRectangle("QUIT GAME", 270, 200, 400, 100, 20, BUTTON_EXIT, 3);
	// get the background picture
	m_OBJ_background = dynamic_cast<OBJ_Background*>(SceneManager::GetInstance()->GetBackgroundByID(0));

	
}

bool GS_MainMenuScene::LoadResouces()
{
	m_isNeedLoaded = false;
	m_isLoaded = true;
	return true;
}

void GS_MainMenuScene::Render(ESContext *esContext)
{
	//Render Something during loading file

	// set environment for render
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// render something 
	
	//m_OBJ_background->UpdatePosition(Vector3(200, 300, 0));
	m_OBJ_background->Render();
	m_buttonPlay->Render();
	//m_buttonQuit->Render();
	m_buttonOption->Render();
	m_buttonHighScore->Render();
	m_butonCredit->Render();
	//TextManager::GetInstance()->m_aText[2]->Render("PLAY GAME", Vector2(120,800),Vector4(0.5, 0.5, 0.5, 1), 3,3);
	//SceneManager::GetInstance()->Render();
	// swap buffer 
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);


}

void GS_MainMenuScene::Update(ESContext * esContext, float deltaTime)
{
	// check file all loading done or not
	// if done, change to MainMenu Scene
	timeCount += deltaTime;
	// check loading file is done yet
	if (m_isLoaded && m_isNeedLoaded)
	{
		m_isNeedLoaded = false;
		printf("\nLOADING DONE!!\n");
	}

	//Update the Sprite Animation for Render Background
	m_OBJ_background->Update(deltaTime);

	//Update the Sprite Animation for Render button
	m_buttonPlay->m_OBJ_Button->Update(deltaTime);
	//m_buttonQuit->m_OBJ_Button->Update(deltaTime);
	m_buttonOption->m_OBJ_Button->Update(deltaTime);
	m_butonCredit->m_OBJ_Button->Update(deltaTime);
	m_buttonHighScore->m_OBJ_Button->Update(deltaTime);


}

// GS process when an Event is Catch, call in Game's Update, after GS is updated
GS_TYPE GS_MainMenuScene::OnEvent(Event *_event)
{
	if (_event == m_buttonPlay)
	{
		//printf("Event Handle\n");
		m_event = nullptr;
		return GS_GAMEPLAY;
	}
	//if (_event == m_buttonQuit)
	//{
	//	//printf("Event Handle QUit\n");
	//	m_event = nullptr;
	//	return GS_EXIT;
	//}
	if (_event == m_buttonOption)
	{
		//printf("Event Handle QUit\n");
		m_event = nullptr;
		return GS_OPTIONMENU;
	}
	if (_event == m_buttonHighScore)
	{
		m_event = nullptr;
		return GS_HIGHSCORE;
	}
	if (_event == m_butonCredit)
	{
		//printf("Event Handle QUit\n");
		m_event = nullptr;
		return GS_CREDIT;
	}
}

void GS_MainMenuScene::Create()
{
	timeCount = 0;
	// test Resources file are loaded yet and load file if they aren't loaded
	if (m_isNeedLoaded)
	{
		LoadResouces();
	}

	// Play Music
	//SoundManager::GetInstance()->m_aMusic[0]->Play();

	

}

// clean up when the GS is released
void GS_MainMenuScene::Release()
{
	
}

// CALLBACK when Touch Down Event is call
void GS_MainMenuScene::TouchActionDown(int x, int y)
{
	//printf("down\n");
}

// CALLBACK when Touch Up Event is call
void GS_MainMenuScene::TouchActionUp(int x, int y)
{
	//printf("up\n");
	if (timeCount > 0.5)
	{
		if (m_buttonPlay->CheckClick(x, y)) m_event = m_buttonPlay;
		//if (m_buttonQuit->CheckClick(x, y)) m_event = m_buttonQuit;
		if (m_buttonOption->CheckClick(x, y)) m_event = m_buttonOption;
		if (m_butonCredit->CheckClick(x, y)) m_event = m_butonCredit;
		if (m_buttonHighScore->CheckClick(x, y)) m_event = m_buttonHighScore;
	}
}

// CALLBACK when Touch Move Event is call
void GS_MainMenuScene::TouchActionMove(int x, int y, int currentX, int currentY)
{
	//printf("Move\n");
}

void GS_MainMenuScene::SetIsLoaded(bool i)
{
	m_isLoaded = i;
}

bool GS_MainMenuScene::GetIsLoaded()
{
	return m_isLoaded;
}
