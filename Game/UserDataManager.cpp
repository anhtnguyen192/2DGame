#include "UserDataManager.h"

UserDataManager*UserDataManager::s_Instance = nullptr;

UserDataManager::UserDataManager()
{
}


UserDataManager::~UserDataManager()
{
	m_listHighScore.clear();
}

UserDataManager * UserDataManager::GetInstance()
{
	if (!s_Instance)
		s_Instance = new UserDataManager();
	return s_Instance;
}

void UserDataManager::DestroyInstance()
{
	if (s_Instance)
	{
		delete s_Instance;
		s_Instance = nullptr;
	}
}

int UserDataManager::LoadData()
{
	int result = 0;
	// read Highscore file
	int k = LoadHighScore("../Resources/highscore.txt");
	if (k != 0) result = -1;


	return result;
}

int UserDataManager::SaveData()
{
	WriteFileHighScore("../Resources/highscore.txt");
	return 0;
}

int UserDataManager::LoadHighScore(char* filename)
{
	FILE* f;
	f = fopen(filename, "r");
	if(f)
	{
		int x(0),y(0),z(0);
		
		fscanf(f, "%d\n%d\n%d", &x,&y,&z);
		m_listHighScore.push_back(x);
		m_listHighScore.push_back(y);
		m_listHighScore.push_back(z);
		return 0;
	}
	else
	{
		printf("File %s khong ton tai", &filename);
		return -1;
	}
}

int UserDataManager::WriteFileHighScore(const char* filename)
{
	fstream ofs;
	ofs.open(filename, ios::out | ios::trunc);
	for (int i = 0; i < 3; i++)
	{
		ofs << m_listHighScore[i] << endl;
	}
	ofs.close(); 
	return 0;
}

bool UserDataManager::EvaluateNewScore(int score)
{

	sort(m_listHighScore.begin(), m_listHighScore.end(), UserDataManager::myfunction);
	if (m_listHighScore[2] < score)
	{
		m_listHighScore.pop_back();
		m_listHighScore.push_back(score);
		sort(m_listHighScore.begin(), m_listHighScore.end(), UserDataManager::myfunction);
		return true;
	}
	return false;
}

bool UserDataManager::myfunction(int i, int j)
{
	{ return (i > j); }
}
