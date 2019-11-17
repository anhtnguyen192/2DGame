#pragma once

#include<vector>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;
class UserDataManager
{
public:
	UserDataManager();
	~UserDataManager();
	static UserDataManager* GetInstance();
	int LoadData();
	int SaveData();

	void DestroyInstance();
	static UserDataManager* s_Instance;
	int LoadHighScore(char* filename);
	vector<int> m_listHighScore;
	int WriteFileHighScore(const char* filename);
	bool EvaluateNewScore(int score);

	static bool myfunction(int i, int j); 

};

