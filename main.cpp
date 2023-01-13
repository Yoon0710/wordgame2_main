#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<Windows.h>
#include<vector>	
#include<fstream>	
using namespace std;

void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}

void SetConsoleView()
{
	system("mode con:cols=50 lines=20");
	system("title [WORDGAME] by.Yoon0710");
}

void DrawReadyGame()
{
	system("cls");
	gotoxy(5, 2);
	cout << "==============================";
	gotoxy(5, 3);
	cout << "========= WORD GAME ==========";
	gotoxy(5, 4);
	cout << "==============================";
	gotoxy(6, 6);
	cout << "Press 'S' To Start";
	gotoxy(6, 7);
	cout << "Press 'Q' TO Quit";
	gotoxy(9, 14);
	cout << "by. YOONGWANGWON" << endl;
}

void DrawStartGame(int life, int score, vector<string>& pastWord)
{
	system("cls");
	gotoxy(5, 1);
	cout << "life = " << life;
	gotoxy(5, 2);
	cout << "score = " << score;
	gotoxy(5, 8);
	cout << "past = ";
	for (int i = 0; i < static_cast<int>(pastWord.size()); ++i)
	{
		cout << pastWord[i] << " ";
	}

	gotoxy(5, 12);
	cout << "input = ";
	gotoxy(13, 14);
	cout << "����ȭ�� 'qq'" << endl;
}

void SetDictionary(vector<string>& strArr)
{
	static const int INIT_NUM = 4;
	static const string str[INIT_NUM] = { "apple", "banana", "code", "program" };	
	ifstream readFromFile("words.txt");
	if (!readFromFile.is_open())
	{
		ofstream writeToFile("words.txt");
		for (int i = 0; i < INIT_NUM; ++i)
		{
			string tmp = str[i];
			if (i != INIT_NUM - 1)
			{
				tmp += "\n";
			}
			writeToFile.write(tmp.c_str(), tmp.size());
			strArr.push_back(str[i]);
		}
		writeToFile.close();
		return;
	}

	while (!readFromFile.eof())
	{
		string tmp;
		getline(readFromFile, tmp);
		strArr.push_back(tmp);
	}
	readFromFile.close();
	return;
}

bool ReadyGame()
{
	DrawReadyGame();
	while (true)
	{
		int key = GetKeyDown();
		if (key == 's' || key == 'S')
		{
			return true;
		}
		else if (key == 'q' || key == 'Q')
		{
			break;
		}
	}
	return false;
}

void StartGame()
{
	int score = 0;
	vector<string> pastWord;
	vector<string> strArr;
	SetDictionary(strArr);		//read from file

	while (true)
	{
		//1 play
		int num = 0;
		srand((unsigned int)time(NULL));		
		num = rand() % static_cast<int>(strArr.size());

		string strQuestion;
		const string strOriginal = strArr[num];	
		const int originLen = static_cast<int>(strOriginal.length());

		//init
		for (int i = 0; i < originLen; ++i)
		{
			strQuestion += "_";
		}

		int life = originLen + 2;

		//1 question
		while (true)
		{
			DrawStartGame(life, score, pastWord);

			//draw question
			gotoxy(5, 5);
			for (int i = 0; i < originLen; ++i)
			{
				cout << strQuestion[i] << " ";
			}
			cout << endl;

			//input
			gotoxy(9, 12);
			string strInput;
			cin >> strInput;
			if (strInput == "qq")
			{
				return;
			}
			pastWord.push_back(strInput);

			if (strInput.length() == 1)
			{
				//alphabet
				for (int i = 0; i < originLen; ++i)
				{
					if (strOriginal[i] == strInput[0])
					{
						strQuestion[i] = strInput[0];
					}
				}
			}
			else if (strInput.length() > 1)
			{
				//word
				if (strOriginal == strInput)
				{
					//score up
					score += 5;
					pastWord.clear();
					break;
				}
			}

			life -= 1;
			if (life < 0)
			{
				score -= 5;
				if (score < 0)
				{
					score = 0;
				}
				pastWord.clear();
				break;
			}
		}
	}
}

int main(void)
{
	SetConsoleView();
	bool isStart = false;
	while (true)
	{
		isStart = ReadyGame();
		if (isStart)
		{
			StartGame();		
		}
		else
		{
			break;
		}
	}
	return 0;
}