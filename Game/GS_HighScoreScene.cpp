#include "GS_HighScoreScene.h"

bool GS_HighScoreScene::m_isNeedLoaded = true;

GS_HighScoreScene::GS_HighScoreScene()
{
	m_type = GS_HIGHSCORE;
}


GS_HighScoreScene::~GS_HighScoreScene()
{
	Release();
	// delete buttons
	delete m_buttonBack;
	m_buttonBack = nullptr;
}

GS_HighScoreScene::GS_HighScoreScene(ESContext *esContext)
{
	//m_isLoaded = false;       
	SetIsLoaded(false);
	m_esContext = esContext;
	m_MusicId = 4;
	Create();

	// Create some button to get Event
	m_buttonBack = new CButtonCircle("BACK", 270, 300, 50, 2, BUTTON_BACK);

	// get the background picture
	m_OBJ_background = dynamic_cast<OBJ_Background*>(SceneManager::GetInstance()->GetBackgroundByID(0));

	
}

bool GS_HighScoreScene::LoadResouces()
{
	m_isLoaded = true;

	return true;
}

void GS_HighScoreScene::Render(ESContext *esContext)
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



	TextManager::GetInstance()->GetTextByID(20)->RenderString();
	char str[20];
	for(int i = 0;i<3;i++)
	{
		int score = UserDataManager::GetInstance()->m_listHighScore[i];
		//printf("%d\n", score);
		memset(str, 0, 20);
		_itoa(score, str, 10);
		TextManager::GetInstance()->GetTextByID(21+i)->BackWardTextData();
		TextManager::GetInstance()->GetTextByID(21 + i)->PushBackTextData(str);
		TextManager::GetInstance()->GetTextByID(21 + i)->RenderString();
	}
	



	m_buttonBack->Render();
	// swap buffer 
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);


}

void GS_HighScoreScene::Update(ESContext * esContext, float deltaTime)
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
	m_buttonBack->m_OBJ_Button->Update(deltaTime);
	//Update the Sprite Animation for Render button


}

// GS process when an Event is Catch, call in Game's Update, after GS is updated
GS_TYPE GS_HighScoreScene::OnEvent(Event *_event)
{
	if (_event == m_buttonBack)
	{
		//printf("Event Handle\n");
		m_event = nullptr;
		return GS_BACK;
	}

}

void GS_HighScoreScene::Create()
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
void GS_HighScoreScene::Release()
{
	
}

// CALLBACK when Touch Down Event is call
void GS_HighScoreScene::TouchActionDown(int x, int y)
{
	//printf("down\n");
	
}

// CALLBACK when Touch Up Event is call
void GS_HighScoreScene::TouchActionUp(int x, int y)
{
	//printf("up\n");
	if (m_buttonBack->CheckClick(x, y)) m_event = m_buttonBack;
}

// CALLBACK when Touch Move Event is call
void GS_HighScoreScene::TouchActionMove(int x, int y, int currentX, int currentY)
{
	//printf("Move\n");
}

//void GS_HighScoreScene::Key(unsigned char key, bool bIsPressed)
//{
//	if (bIsPressed && key == 0x20 && m_event == nullptr) m_event = m_buttonBack;
//}

void GS_HighScoreScene::SetIsLoaded(bool i)
{
	m_isLoaded = i;
}

bool GS_HighScoreScene::GetIsLoaded()
{
	return m_isLoaded;
}
