#include "GS_Credit.h"

bool GS_Credit::m_isNeedLoaded = true;

GS_Credit::GS_Credit()
{
	m_type = GS_CREDIT;
	
	
}


GS_Credit::~GS_Credit()
{
	Release();
	// delete buttons
	delete m_buttonBack;
	m_buttonBack = nullptr;
	m_Lines.clear();
}

GS_Credit::GS_Credit(ESContext *esContext)
{
	//m_isLoaded = false;     
	SetIsLoaded(false);
	m_esContext = esContext;
	m_textType = TextManager::GetInstance()->GetTextByID(12);
	m_Lines.push_back("Gameloft Internship");
	m_Lines.push_back("24/6/2019-23/8/2019");
	m_Lines.push_back("Producted by Team1:");
	m_Lines.push_back(" 1.Nguyen Quang Thanh - Leader");
	m_Lines.push_back(" 2.Nguyen Huu Trang");
	m_Lines.push_back(" 3.Nguyen Tuan Anh");
	m_Lines.push_back(" 4.Do Quoc Trong");
	m_MusicId = 0;
	// Create some button to get Event
	m_buttonBack = new CButtonCircle("BACK", 270, 300, 50, 2, BUTTON_BACK);

	// get the background picture
	m_OBJ_background = dynamic_cast<OBJ_Background*>(SceneManager::GetInstance()->GetBackgroundByID(0));
	Create();
}

bool GS_Credit::LoadResouces()
{
	m_isLoaded = true;
	return true;
}

void GS_Credit::Render(ESContext *esContext)
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
	
	Vector2 textFistLinePosition = Vector2(50, 800);
	for (int i = 0; i < m_Lines.size(); i++)
	{
		Vector2 position = textFistLinePosition - Vector2(0, i * 50);
		Vector4	color = Vector4((rand() % 500 + 500 ) *0.001, (rand() % 400 + 600) *0.001, (rand() % 700 + 300) *0.001, 1);
		m_textType->Render(m_Lines[i], position, color, 1,1);
	}
	m_buttonBack->Render();
	// swap buffer 
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);


}

void GS_Credit::Update(ESContext * esContext, float deltaTime)
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
GS_TYPE GS_Credit::OnEvent(Event *_event)
{
	if (_event == m_buttonBack)
	{
		//printf("Event Handle\n");
		m_event = nullptr;
		return GS_BACK;
	}

}

void GS_Credit::Create()
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
void GS_Credit::Release()
{
	// delete buttons
	//delete m_buttonBack;
}

// CALLBACK when Touch Down Event is call
void GS_Credit::TouchActionDown(int x, int y)
{
	//printf("down\n");
	
}

// CALLBACK when Touch Up Event is call
void GS_Credit::TouchActionUp(int x, int y)
{
	//printf("up\n");
	if (m_buttonBack->CheckClick(x, y)) m_event = m_buttonBack;
}

// CALLBACK when Touch Move Event is call
void GS_Credit::TouchActionMove(int x, int y, int currentX, int currentY)
{
	//printf("Move\n");
	
}

void GS_Credit::Key(unsigned char key, bool bIsPressed)
{
	//if (bIsPressed && key == 0x20 && m_event == nullptr) m_event = m_buttonBack;
}

void GS_Credit::SetIsLoaded(bool i)
{
	m_isLoaded = i;
}

bool GS_Credit::GetIsLoaded()
{
	return m_isLoaded;
}
