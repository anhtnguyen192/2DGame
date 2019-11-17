#include "stdafx.h"
#include "Game.h"
#include"UserDataManager.h"
#include "Testbed\Tests\AddPair.h"
Game * Game::s_Instance = nullptr;

Game::Game()
{
	// Load all resource
	printf("LOADING RESOURCES..............\n");
	ResourcesManager::GetInstance()->Init("../Resources/ResourcesManeger.txt");
	//printf("%s\n", ResourcesManager::GetInstance()->m_a2DTextures[1].);
	printf("LOADING RM DONE!!\n");

	SceneManager::GetInstance()->Init("../Resources/SceneManager.txt");
	printf("LOADING SM DONE!!\n");
	//printf("%s\n", ResourcesManager::GetInstance()->m_a2DTextures[1].GetID());
	TextManager::GetInstance()->Init("../Resources/TextManager.txt");
	printf("LOADING TEXT MANAGER DONE!!\n");

	SoundManager::GetInstance()->Init("../Resources/SoundManager.txt");
	printf("LOADING SOUND MANAGER DONE!!\n");

	SceneManager::GetInstance()->LinkObjects();
	printf("LINK Objects DONE!!\n");

	UserDataManager::GetInstance()->LoadData();

	// Create GS
	m_GS_Welcome =		new GS_WelcomeScene(m_esContext);
	m_GS_MainMenu =		new GS_MainMenuScene(m_esContext);
	m_GS_OptionMenu =   new GS_OptionMenuScene(m_esContext);
	m_GS_Credit =		new GS_Credit(m_esContext);
	m_GS_HighScore =	new GS_HighScoreScene(m_esContext);
	m_GS_GamePlay =		new GS_GamePlayScene(m_esContext);
	m_GS_GamePause =	new GS_GamePause(m_esContext);
	m_GS_GameEnd =		new GS_GameEnd(m_esContext);
	
	//......

	// Init first GS
	m_stackGameState.push(GS_WELCOME);
	
	m_state = GetGameState();
	SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Play();
}


Game::~Game()
{
	while (!m_stackGameState.empty())
	{
		m_stackGameState.pop();
	}
	UserDataManager::GetInstance()->SaveData();
	UserDataManager::GetInstance()->DestroyInstance();
	if (m_GS_GamePlay)delete m_GS_GamePlay;
	if (m_GS_GameEnd)delete m_GS_GameEnd;
	if (m_GS_GamePause)delete m_GS_GamePause;
	
	if (m_GS_Welcome)delete m_GS_Welcome;
	if (m_GS_MainMenu)delete m_GS_MainMenu;
	if (m_GS_OptionMenu)delete m_GS_OptionMenu;
	if (m_GS_HighScore)delete m_GS_HighScore;
	if (m_GS_Credit)delete m_GS_Credit;

	ResourcesManager::GetInstance()->DestroyInstance();
	SceneManager::GetInstance()->DestroyInstance();
	TextManager::GetInstance()->DestroyInstance();
	SoundManager::GetInstance()->DestroyInstance();
	Camera::GetInstance()->DestroyInstance();

	m_state = nullptr;
}



Game * Game::GetInstance()
{
	if (!s_Instance)
		s_Instance = new Game();
	return s_Instance;
}

void Game::Update(ESContext * esContext, float deltaTime)
{
	if (m_state)
	{
		m_state->Update(esContext, deltaTime);
		OnEvent();
	}
}



void Game::Render(ESContext *esContext)
{
	DWORD start, end;
	start = GetTickCount();

	m_state->Render(esContext);


	// Limit FPS
	end = GetTickCount();
	DWORD frameTime = end - start;
	if (frameTime < 1000.0 / LIMIT_FPS)
	{
		//Sleep(1000 / LIMIT_FPS - frameTime);

	}
	
}

void Game::GoToGS(GS_TYPE _GS_type)
{
	if ((int)_GS_type > 0 && (int)_GS_type < 20)
	{
		if (_GS_type == GS_NULL) return;
		if (_GS_type == GS_EXIT)
		{

			/*DestroyInstance();
			std::exit(0);*/
			//.....
			return;
		}
		if (_GS_type == GS_BACK)
		{
			dynamic_cast<GS_MainMenuScene*>(m_GS_MainMenu)->Create();
			SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Stop();
			m_stackGameState.pop();
			m_state = GetGameState();
			SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Play();
			//.....
			return;
		}
		if (m_state->m_type != _GS_type)
		{
			if (_GS_type == GS_WELCOME)
			{

				m_stackGameState.push(GS_WELCOME);
				m_state = GetGameState();
				SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Play();
				//.....
				return;
			}

			if (_GS_type == GS_MAINMENU)
			{
				SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Stop();
				if (m_state == m_GS_GameEnd)
				{
					
					m_GS_GamePlay->Release();
					while (m_stackGameState.top() != GS_MAINMENU)
					{
						m_stackGameState.pop();
					}
					m_stackGameState.pop();
				}
				
				m_stackGameState.push(GS_MAINMENU);
				
				m_state = GetGameState();
				SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Play();
				//.....
				return;
			}

			if (_GS_type == GS_OPTIONMENU)
			{
				SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Stop();
				m_stackGameState.push(GS_OPTIONMENU);
				m_state = GetGameState();
				SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Play();
				//.....
				return;
			}

			if (_GS_type == GS_HIGHSCORE)
			{
				SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Stop();
				m_stackGameState.push(GS_HIGHSCORE);
				m_state = GetGameState();
				SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Play();
				//.....
				return;
			}

			if (_GS_type == GS_CREDIT)
			{
				SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Stop();
				m_stackGameState.push(GS_CREDIT);
				m_state = GetGameState();
				SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Play();
				//.....
				return;
			}

			if (_GS_type == GS_GAMEPLAY)
			{
				
				//delete m_GS_GamePlay;
				//if (!m_GS_GamePlay) m_GS_GamePlay = new GS_GamePlayScene(m_esContext);
				SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Stop();
				m_GS_GamePlay->Create();
				m_stackGameState.push(GS_GAMEPLAY);
				m_state = GetGameState();
				SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Play();
				//.....
				return;
			}

			if (_GS_type == GS_GAMEPAUSE)
			{
				SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Stop();
				m_stackGameState.push(GS_GAMEPAUSE);
				m_state = GetGameState();
				SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Play();
				//.....
				return;
			}

			if (_GS_type == GS_GAMEEND)
			{
				SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Stop();
				m_GS_GameEnd->Create();
				m_stackGameState.push(GS_GAMEEND);
				dynamic_cast<GS_GameEnd*>(m_GS_GameEnd)->GetScoreAndCheckNewHighscore();
				m_state = GetGameState();
				SoundManager::GetInstance()->m_aMusic[m_state->ChangeInMusicID(m_state->m_MusicId)]->Play();

				//.....
				return;
			}
		}

	}
	

}

void Game::OnEvent()
{
	if (m_state)
	{
		GS_TYPE typeOption = m_state->OnEvent(m_state->m_event);
		GoToGS(typeOption);
	}
}

void Game::DestroyInstance()
{
	if (s_Instance)
	{
		delete s_Instance;
		s_Instance = nullptr;
	}
}

void Game::Release()
{
	//while (m_stackGameState.size() > 1)
	//{
	//	m_state = m_stackGameState.top();
	//	m_stackGameState.pop();
	//}

	//// make m_state is the Last element in stack
	//m_state = m_stackGameState.top();
	
}

void Game::Change(int & x, int & y)
{
	//x = x;
	y = Globals::screenHeight - y;
}

GameState * Game::GetGameState()
{
	if (m_stackGameState.size() > 0)
	{
		GS_TYPE type = m_stackGameState.top();
		if (type == GS_WELCOME) return m_GS_Welcome;
		if (type == GS_CREDIT) return m_GS_Credit;
		if (type == GS_MAINMENU) return m_GS_MainMenu;
		if (type == GS_OPTIONMENU) return m_GS_OptionMenu;
		if (type == GS_GAMEPLAY) return m_GS_GamePlay;
		if (type == GS_HIGHSCORE) return m_GS_HighScore;
		if (type == GS_GAMEPAUSE) return m_GS_GamePause;
		if (type == GS_GAMEEND) return m_GS_GameEnd;
		//...
	}
	return nullptr;
}

void Game::TouchActionDown(ESContext * esContext, int x, int y)
{
	// Mouse down
	Change(x, y);
	m_iCurrentMouseX = x;
	m_iCurrentMouseY = y;
	//SceneManager::GetInstance()->ChangeDown(x, y);
	//printf("%d, %d\n", x, y);
	m_state->TouchActionDown(x, y);
}

void Game::TouchActionUp(ESContext * esContext, int x, int y)
{
	Change(x, y);
	//printf("%d, %d\n", x, y);
	m_state->TouchActionUp(x, y);
}

void Game::TouchActionMove(ESContext * esContext, int x, int y)
{
	// Mouse move
	//SceneManager::GetInstance()->SetCanBeMove();
	Change(x, y);
	float fMoveVectorX = x - m_iCurrentMouseX;
	float fMoveVectorY = y - m_iCurrentMouseY;
	//printf("%d, %d\n", x, y);
	m_state->TouchActionMove(x, y, m_iCurrentMouseX, m_iCurrentMouseY);
	//SceneManager::GetInstance()->ChangeMove(a, b);
	m_iCurrentMouseX = x;
	m_iCurrentMouseY = y;
}

void Game::Key(ESContext * esContext, unsigned char key, bool bIsPressed)
{
	//printf("%c %x\n", key, key);
	m_state->Key(key, bIsPressed);
}

void Game::DeleteState(GameState * gs)
{
	delete gs;
	gs = nullptr;
}
	



