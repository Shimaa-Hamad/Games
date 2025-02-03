#include<iostream>
#include<cstdlib>

using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResult
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";

};

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;

}

string WinnerName(enWinner Winner)
{
	string ArrWinnerName[3] = { "Player1" ,"Computer" ,"NoWinner" };
	return ArrWinnerName[Winner - 1];
}

enWinner WhoWinTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}
	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}
	return enWinner::Player1;
}

string ChoiceName(enGameChoice Choice)
{
	string ArrChoiceName[3] = { "Stone" ,"Paper" ,"Scissors" };
	return ArrChoiceName[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 2F");
		break;
	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;
	default:
		system("color 6F");
		break;
	}
}

void PrintRoundInfo(stRoundInfo RoundInfo)
{
	cout << "\n-------------------Round[" << RoundInfo.RoundNumber << "]-----------------\n\n";
	cout << "Player1Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer1Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "RoundWinner: " << RoundInfo.WinnerName << endl;
	cout << "\n\n----------------------------------------------------------------------------\n\n";
	SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWinTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::Player1;
	else if (ComputerWinTimes > Player1WinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameResult FillGameResult(short HowManyRound, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResult GameResult;
	GameResult.GameRounds = HowManyRound;
	GameResult.Player1WinTimes = Player1WinTimes;
	GameResult.ComputerWinTimes = ComputerWinTimes;
	GameResult.DrawTimes = DrawTimes;
	GameResult.GameWinner = WhoWinTheGame(Player1WinTimes, ComputerWinTimes);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);
	return GameResult;
}

enGameChoice ReadPlayerChoice()
{
	short Choice = 1;
	do
	{
		cout << "\nYour Choice [1]Stone , [2]Paper , [3]Scissors\n";
		cin >> Choice;
	} while (Choice < 1 || Choice >3);
	return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

stGameResult PlayGame(short HowManyRound)
{
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	for (short GameRound = 1; GameRound <= HowManyRound; GameRound++)
	{
		cout << "\nRound [" << GameRound << "]begins :\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWinTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);
		if (RoundInfo.Winner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;
		PrintRoundInfo(RoundInfo);
	}
	return FillGameResult(HowManyRound, Player1WinTimes, ComputerWinTimes, DrawTimes);
}


string Tab(short NumOfTabs)
{
	string t = "";
	for (int i = 1; i <= NumOfTabs; i++)
	{
		t = t + "\t";
	}
	return t;
}

void ShowGameOverScreen()
{
	cout << Tab(2) << "----------------------------------\n\n";
	cout << Tab(2) << "+++ G A M E O V E R +++\n";
	cout << Tab(2) << "----------------------------------\n\n";
}

void PrintGameResult(stGameResult GameResult)
{
	cout << Tab(2) << "-------------------[Final Result]-----------------\n\n";
	cout << Tab(2) << "Game Rounds: " << GameResult.GameRounds << endl;
	cout << Tab(2) << "Player1WinTimes: " << GameResult.Player1WinTimes << endl;
	cout << Tab(2) << "ComputerWinTimes: " << GameResult.ComputerWinTimes << endl;
	cout << Tab(2) << "DrawTimes: " << GameResult.DrawTimes << endl;
	cout << Tab(2) << "Final Winner: " << GameResult.WinnerName << endl;
	cout << Tab(2) << "--------------------------------------------------------------\n";
	SetWinnerScreenColor(GameResult.GameWinner);
}

short ReadHowManyRounds()
{
	short RoundNumber = 1;
	do
	{
		cout << "Please enter Round Number From 1 To 10 \n";
		cin >> RoundNumber;
	} while (RoundNumber < 1 || RoundNumber>10);
	return RoundNumber;
}

void ResetGame()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'y';
	do
	{
		ResetGame();
		stGameResult GameResult = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		PrintGameResult(GameResult);
		cout << Tab(3) << "Do You Want To Play Again Y / N\n";
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}