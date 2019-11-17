#include "GS_WelcomeScene.h"

bool GS_WelcomeScene::m_isNeedLoaded = true;

GS_WelcomeScene::GS_WelcomeScene()
{
	m_type = GS_WELCOME;
}


GS_WelcomeScene::~GS_WelcomeScene()
{
	Release();
	// delete buttons
	/*delete m_buttonQuit;
	m_buttonQuit = nullptr;*/
	delete m_buttonPlay;
	m_buttonPlay = nullptr;
}

GS_WelcomeScene::GS_WelcomeScene(ESContext *esContext)
{
	//m_isLoaded = false;
	sState = 0;
	sHit = 0;
	SetIsLoaded(false);
	m_esContext = esContext;
	
	m_MusicId = 7;
	Create();
	
	s = dynamic_cast<Sprite*> (SceneManager::GetInstance()->GetSpriteByID(58));
	s->ChangeToState(sState);
	// Create some button to get Event
	m_buttonPlay = new CButtonCircle("PLAY", 200, 300, 50, 0, BUTTON_TRANS_FORWARD);
	//m_buttonQuit = new CButtonCircle("QUIT", 350, 300, 50, 1, BUTTON_EXIT);

	// get the background picture
	m_OBJ_background = dynamic_cast<OBJ_Background*>(SceneManager::GetInstance()->GetBackgroundByID(0));
}

bool GS_WelcomeScene::LoadResouces()
{
	//ResourcesManager*x = ResourcesManager::GetInstance();
	//printf("LOADING RESOURCES..............\n");
	//ResourcesManager::GetInstance()->Init("../Resources/ResourcesManeger.txt");
	////printf("%s\n", ResourcesManager::GetInstance()->m_a2DTextures[1].);
	//printf("LOADING RM DONE!!\n");

	//SceneManager::GetInstance()->Init("../Resources/SceneManager.txt");
	//printf("LOADING SM DONE!!\n");
	////printf("%s\n", ResourcesManager::GetInstance()->m_a2DTextures[1].GetID());
	//TextManager::GetInstance()->Init("../Resources/TextManager.txt");
	//printf("LOADING TEXT MANAGER DONE!!\n");

	//SoundManager::GetInstance()->Init("../Resources/SoundManager.txt");
	//printf("LOADING SOUND MANAGER DONE!!\n");

	//SceneManager::GetInstance()->LinkObjects();
	//printf("LINK Objects DONE!!\n");

	

	m_isLoaded = true;
	return true;
}

void GS_WelcomeScene::Render(ESContext *esContext)
{
	//Render Something during loading file

	// set environment for render
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// render something 
	
	m_OBJ_background->Render();
	//s->RenderByParameter(Vector3(270, 900, 0), Vector3(0, 0, 0), sHit);
	//s->RenderByParameter(Vector3(0, 900, 0), Vector3(0, 0, 0), sHit);
	//s->RenderByParameter(Vector3(470, 900, 0), Vector3(0, 0, 0), sHit);
	//SceneManager::GetInstance()->GetSpriteByID(55)->RenderByParameter(Vector3(270, 480, 0), Vector3(0, 0, 0),Vector3(1,1,1), sHit);
	//s->RenderByParameter(s->m_Position+Vector3(30,0,0), Vector3(0, 0, 0), sHit);
	//s->Render();
	//dynamic_cast<Sprite*> (SceneManager::GetInstance()->GetSpriteByID(59))->Render();
	TextManager::GetInstance()->GetTextByID(13)->Render("SPACE", Vector2(100, 850), Vector4(1, 1, 0, 1), 2,2);
	TextManager::GetInstance()->GetTextByID(13)->Render("AVENGERS", Vector2(10, 720), Vector4(1, 1, 0, 1), 1.8,1.8);

	TextRender *text1 = TextManager::GetInstance()->GetTextByID(0);
	float a = timeCount - floor(timeCount);
	Vector4 color = Vector4(1, 1, 1, a);
	text1->Render("Touch to Start", Vector2(120, 480), color, 2, 2);
	//m_buttonPlay->Render();
	//m_buttonQuit->Render();
	// swap buffer 
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);

	
}

void GS_WelcomeScene::Update(ESContext * esContext, float deltaTime)
{
	//printf("%f \n", timeCount);
	timeCount += deltaTime;
	/*
	if (timeCount > 1.0)  
		sHit = 1.0f; 
	else sHit = 0.0f;
	if(timeCount > 2)
	{
		
		sState = 1 - sState;
		s->ChangeToState(sState);
		timeCount = 0;
	}*/
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
	 
	//s->ChangeToState(0);
	s->Update(deltaTime);
	//Update the Sprite Animation for Render button
	//m_buttonPlay->m_OBJ_Button->Update(deltaTime);
	//m_buttonQuit->m_OBJ_Button->Update(deltaTime);

}

// GS process when an Event is Catch, call in Game's Update, after GS is updated
GS_TYPE GS_WelcomeScene::OnEvent(Event *_event)
{
	if (_event == m_buttonPlay)
	{
		printf("Event Handle\n");
		m_event = nullptr;
		return GS_MAINMENU;
	}
	/*if (_event == m_buttonQuit)
	{
		printf("Event Handle QUit\n");
		m_event = nullptr;
		return GS_EXIT;
	}*/
}

void GS_WelcomeScene::Create()
{
	timeCount = 0;
	// test Resources file are loaded yet and load file if they aren't loaded
	if (m_isNeedLoaded)
	{
		LoadResouces();
	}

	// Play Music
	//SoundManager::GetInstance()->m_aMusic[1]->Play();

	
	
}

// clean up when the GS is released
void GS_WelcomeScene::Release()
{
	
}

// CALLBACK when Touch Down Event is call
void GS_WelcomeScene::TouchActionDown(int x, int y)
{
	//printf("down\n");
	
}

// CALLBACK when Touch Up Event is call
void GS_WelcomeScene::TouchActionUp(int x, int y)
{
	//printf("up\n");
	//if (m_buttonPlay->CheckClick(x, y)) 
	m_event = m_buttonPlay;
	//if (m_buttonQuit->CheckClick(x, y)) m_event = m_buttonQuit;
}

// CALLBACK when Touch Move Event is call
void GS_WelcomeScene::TouchActionMove(int x, int y, int currentX, int currentY)
{
	//printf("Move\n");
}

void GS_WelcomeScene::SetIsLoaded(bool i)
{
	m_isLoaded = i;
}

bool GS_WelcomeScene::GetIsLoaded()
{
	return m_isLoaded;
}
