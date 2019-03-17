#include <iostream>
#include <Windows.h> 
#include<time.h>
#include<conio.h>
#include <io.h>	
#include <iomanip>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
struct Gamer
{
	char Name[20];
	int score;
}Player;

void ShowCursor(bool visible);
void GotoXY(int X, int Y);
void StartInitField(int Array[][32], int line, int column);
void PrintField(int Array[][32], int line, int column);
void PrintPlayField(int Array[][32], int line, int column);
void PrintFigure(int Figure[7][4][8][12], int figure, int rotation, int x, int y);
void PrintNextFigure(int Figure[7][4][8][12], int nextFigure);
void PrintLevelScore(int &level, int &score, int& delay);
int ShiftFigureX(int Figure[7][4][8][12], int figure, int rotation);
int ShiftFigureY(int Figure[7][4][8][12], int figure, int rotation);
void ClearFigure(int Figure[7][4][8][12], int figure, int rotation, int x, int y);
void InitField(int Field[42][32], int Figure[7][4][8][12], int figure, int rotation, int x, int y);
void DeleteFullLine(int Field[42][32], int line, int column, int &score);
int FigureGen();
bool Collision(int Field[42][32], int Figure[7][4][8][12], int figure, int rotation, int x, int y);
void SetColor(int &figure);

void InitControlField(int Array[][32], int line, int column);
void PrintControlField(int Array[][32], int line, int column, char Tetris[][30], int tLine, int tColumn);
void PrintControleOptions();
int ControlLevelScoreDelay(int &level, int &score);
void EnterUser(Gamer &Player);
int SaveToFile(Gamer &Player);
int LoadFromFile();

enum Status { EMPTY = 0, FIGURE = 1 };

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coords;
const int LINE = 42;
const int COLUMN = 32;
const int startdelay = 1200;



int main()
{
	system("mode 100,50");//размер окна под изображение
	srand(time(0));


	int Field[LINE][COLUMN] = { 0 };
	int ControlField[LINE][COLUMN] = { 0 };
	char Tetris[7][30] =
	{
		{ '0', '*', '*', '*', '*', '*', '0', '*', '*', '*', '*', '0', '*', '*', '*', '*', '*', '0', '*', '*', '*', '0', '0', '*', '0', '0', '*', '*', '0', '0' },
		{ '0', '0', '0', '*', '0', '0', '0', '*', '0', '0', '0', '0', '0', '0', '*', '0', '0', '0', '*', '0', '0', '*', '0', '0', '0', '*', '0', '0', '*', '0' },
		{ '0', '0', '0', '*', '0', '0', '0', '*', '0', '0', '0', '0', '0', '0', '*', '0', '0', '0', '*', '0', '0', '*', '0', '*', '0', '*', '0', '0', '0', '0' },
		{ '0', '0', '0', '*', '0', '0', '0', '*', '*', '*', '0', '0', '0', '0', '*', '0', '0', '0', '*', '*', '*', '0', '0', '*', '0', '0', '*', '*', '0', '0' },
		{ '0', '0', '0', '*', '0', '0', '0', '*', '0', '0', '0', '0', '0', '0', '*', '0', '0', '0', '*', '0', '*', '0', '0', '*', '0', '0', '0', '0', '*', '0' },
		{ '0', '0', '0', '*', '0', '0', '0', '*', '0', '0', '0', '0', '0', '0', '*', '0', '0', '0', '*', '0', '0', '*', '0', '*', '0', '*', '0', '0', '*', '0' },
		{ '0', '0', '0', '*', '0', '0', '0', '*', '*', '*', '*', '0', '0', '0', '*', '0', '0', '0', '*', '0', '0', '*', '0', '*', '0', '0', '*', '*', '0', '0' }
	};

	int Figure[7][4][8][12] =
	{
		{// Figure[0]
			{ // Figure[0][0][8][12] 'I' Line
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },// Horizontale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },//Figure[0][0][8][12] 
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[0][1][8][12] 'I' Line
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },// Verticale
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },//Figure[0][1][8][12] 
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 }
			},
			{// Figure[0][2][8][12] 'I' Line
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },// Horizontale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },//Figure[0][2][8][12] 
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[0][3][8][12] 'I' Line
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },// Verticale
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },//Figure[0][3][8][12] 
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 }
			}
		},
		{// Figure[1]
			{ // Figure[1][0][8][12] 'O' Cube
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },// Horizontale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },//Figure[1][0][8][12] 
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[1][1][8][12] 'O' Cube
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },// Horizontale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },//Figure[1][1][8][12] 
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[1][2][8][12] 'O' Cube
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },// Horizontale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },//Figure[1][2][8][12] - 
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[1][3][8][12] 'O' Cube
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },// Horizontale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },//Figure[1][3][8][12] 
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			}
		},
		{// Figure[2]
			{// Figure[2][0][8][12] 'S' 
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },// Horizontale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },//Figure[2][0][8][12] 
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[2][1][8][12] 'S'
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },// Verticale
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },//Figure[2][1][8][12] 
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[2][2][8][12] 'S'
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },// Horizontale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },//Figure[2][2][8][12] 
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[2][3][8][12] 'S'
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },// Verticale
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },//Figure[2][3][8][12] 
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			}
		},
		{// Figure[3]
			{// Figure[3][0][8][12] 'Z'
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },// Verticale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },//Figure[3][0][8][12]
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[3][1][8][12] 'Z'
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },// Horizontale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },//Figure[3][1][8][12]
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[3][2][8][12] 'Z'
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },// Verticale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },//Figure[3][2][8][12]
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[3][3][8][12] 'Z'
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },// Horizontale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },//Figure[3][3][8][12]
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			}
		},
		{// Figure[4]
			{// Figure[4][0][8][12] 'Z'
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },// Verticale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },//Figure[4][0][8][12]
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[4][1][8][12] 'Z'
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },// Horizontale
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },//Figure[4][1][8][12]
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[4][2][8][12] 'Z'
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },// Verticale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },//Figure[4][2][8][12]
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[4][3][8][12] 'Z'
				//{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				//{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				//{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },//Figure[4][3][8][12]
				//{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				//{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				//{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				//{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				//{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },// Horizontale
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },//Figure[4][3][8][12]
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			}

		},
		{// Figure[5]
			{// Figure[5][0][8][12] 'Z'
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },// Verticale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },//Figure[5][0][8][12]
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[5][1][8][12] 'Z'
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },// Horizontale
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },//Figure[5][1][8][12]
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[5][2][8][12] 'Z'
				{ 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0 },// Verticale
				{ 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },//Figure[5][2][8][12]
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[5][3][8][12] 'Z'
				//{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },// Horizontale
				//{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				//{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },//Figure[5][3][8][12]
				//{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				//{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				//{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				//{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				//{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },// Horizontale
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },//Figure[5][3][8][12]
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			}

		},
		{// Figure[6]
			{// Figure[6][0][8][12] 'Z'
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },// Verticale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },//Figure[6][0][8][12]
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[6][1][8][12] 'Z'
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },// Horizontale
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },//Figure[6][1][8][12]
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[6][2][8][12] 'Z'
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },// Verticale
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },//Figure[6][2][8][12]
				{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			},
			{// Figure[6][3][8][12] 'Z'
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },// Horizontale
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },//Figure[6][3][8][12]
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
			}
		}
	};	
	int delay = startdelay;
	int figure = 0;
	int nextFigure = FigureGen();
	int rotation = 0;
	int level = 1;
	int score = 0;
	ShowCursor(false);
	StartInitField(Field, LINE, COLUMN);
	PrintField(Field, LINE, COLUMN);
	InitControlField(ControlField, LINE, COLUMN);
	PrintControlField(ControlField, LINE, COLUMN, Tetris, 7, 30);
	bool play = 1;		
	int startPositionX = 16;
	int startPositionY = 1;
	int deltaMoveDown = 2;
	int deltaMoveSide = 3;
	int key = 0;
	while (play)
	{
		if (startPositionY == 1 && !Collision(Field, Figure, figure, rotation, startPositionX, startPositionY))
		{
			delay = ControlLevelScoreDelay(level, score);
			PrintLevelScore(level, score, delay);
			figure = nextFigure;
			nextFigure = FigureGen();
			PrintNextFigure(Figure, nextFigure);			
			rotation = 0;
			PrintFigure(Figure, figure, rotation, startPositionX, startPositionY);
			Sleep(delay);
			ClearFigure(Figure, figure, rotation, startPositionX, startPositionY);
			startPositionY += deltaMoveDown;
		}
		else if (startPositionY == 1 && Collision(Field, Figure, figure, rotation, startPositionX, startPositionY))
		{
			PrintFigure(Figure, figure, rotation, startPositionX, startPositionY);//?????
			GotoXY(37, 13);
			cout << "GAME OVER";
			break;
		}
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case KEY_UP:
				if (rotation == 3) rotation = 0;
				else rotation += 1;
				if (Collision(Field, Figure, figure, rotation, startPositionX, startPositionY))
				{
					if (rotation == 0) rotation = 3;
					else rotation -= 1;
				}
				break;
			case KEY_DOWN:				
				delay = 120;
				break;
			case KEY_LEFT:
				startPositionX -= deltaMoveSide;
				if (Collision(Field, Figure, figure, rotation, startPositionX, startPositionY))
					startPositionX += deltaMoveSide;
				break;
			case KEY_RIGHT:
				startPositionX += deltaMoveSide;
				if (Collision(Field, Figure, figure, rotation, startPositionX, startPositionY))
					startPositionX -= deltaMoveSide;
				break;
			case 81:// Q
			case 113:// q
				play = false;
				break;
			case 27://Esc
				GotoXY(0, 42);
				return 0;
			}
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
		}
		else if (startPositionY >1 && startPositionY < 42)
		{
			if (Collision(Field, Figure, figure, rotation, startPositionX, startPositionY))
			{
				startPositionY -= deltaMoveDown;
				PrintFigure(Figure, figure, rotation, startPositionX, startPositionY);
				InitField(Field, Figure, figure, rotation, startPositionX, startPositionY);				
				PrintPlayField(Field, LINE, COLUMN);
				DeleteFullLine(Field, LINE, COLUMN, score);				
				startPositionX = 16;
				startPositionY = 1;
			}
			else
			{
				PrintFigure(Figure, figure, rotation, startPositionX, startPositionY);
				Sleep(delay);
				ClearFigure(Figure, figure, rotation, startPositionX, startPositionY);
				startPositionY += deltaMoveDown;
			}
		}
	}
	Player.score = score;
	PrintControleOptions();
	bool exit = false;
	char *ptr = nullptr;
	while (!exit)
	{
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case 83://S
			case 115://s save to file				
				EnterUser(Player);
				SaveToFile(Player);
				break;
			case 82://R
			case 114://r Load from file				
				LoadFromFile();
				break;
			case 27://Esc
				exit = true;
				break;
			}
		}

	}
	GotoXY(0, 42);
	return 0;
}
/////////////////FUNCTIONS////////////////////////////////
int FigureGen()
{
	int index = rand() % 7;
	return index;
}
void ShowCursor(bool visible)
{
	CONSOLE_CURSOR_INFO cci = { sizeof(cci), visible };
	SetConsoleCursorInfo(hStdOut, &cci);
}
void GotoXY(int X, int Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hStdOut, coord);
}
void StartInitField(int Array[][32], int line, int column)
{
	for (int i = 0; i<line; i++)
	{
		for (int j = 0; j< column; j++)
		{
			if (i == 0 && j == 0)  Array[i][j] = char(201);                                          // г
			else if ((j == 0 || j == column - 1) && i > 0 && i < line - 1) Array[i][j] = char(186);      // ¦
			else if (i == line - 1 && j == 0) Array[i][j] = char(200);                                 // L
			else if (i == 0 && j == column - 1) Array[i][j] = char(187);                             // ¬
			else if (i == line - 1 && j == column - 1) Array[i][j] = char(188);                      // -
			else if (i == 0 || i == line - 1 && j != 0 && j != column - 1) Array[i][j] = char(205); // =
			else Array[i][j] = 0;
		}
	}
}
void PrintField(int Array[][32], int line, int column)
{
	for (int i = 0; i<line; i++)
	{
		for (int j = 0; j< column; j++)
		{
			cout << char(Array[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}
void PrintPlayField(int Array[][32], int line, int column)
{
	for (int i = 1; i<line - 1; i++)
	{
		GotoXY(1, i);
		for (int j = 1; j< column - 1; j++)
		{	
			if (Array[i][j] != EMPTY)
			{
				SetColor(Array[i][j]);
				cout << char(177);
			}
			else cout << char(Array[i][j]);
		}
	}
}
void PrintFigure(int Figure[7][4][8][12], int figure, int rotation, int x, int y)
{
	int color = figure + 1;
	SetColor(color);	
	int shiftLeft = ShiftFigureX(Figure, figure, rotation);
	int shiftUp = ShiftFigureY(Figure, figure, rotation);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (Figure[figure][rotation][i][j] == FIGURE)
			{
				GotoXY(x + j - shiftLeft, y + i - shiftUp);
				cout << char(177);
			}
		}
		cout << endl;
	}
}
void SetColor(int &figure)///КОЛОР
{
	/* SetConsoleTextAttribute (h, 0xA2);
	Первый разряд (в данном случае 2) - это цвет текста. 
	Второй разряд (в данном случае А) - цвет фона.
	
	Цвета в шестнадцатеричной форме:

	0 = Black       8 = Gray
	1 = Blue        9 = Light Blue
	2 = Green       A = Light Green
	3 = Aqua        B = Light Aqua
	4 = Red         C = Light Red
	5 = Purple      D = Light Purple
	6 = Yellow      E = Light Yellow
	7 = White       F = Bright White

	*/
	switch (figure)
	{
	case 0:
		SetConsoleTextAttribute(hStdOut, 0x9);
		break;
	case 1:
		SetConsoleTextAttribute(hStdOut, 0x9);
		break;
	case 2:
		SetConsoleTextAttribute(hStdOut, 0xA);
		break;
	case 3:
		SetConsoleTextAttribute(hStdOut, 0xB);
		break;
	case 4:
		SetConsoleTextAttribute(hStdOut, 0xC);
		break;
	case 5:
		SetConsoleTextAttribute(hStdOut, 0xD);
		break;
	case 6:
		SetConsoleTextAttribute(hStdOut, 0xE);
		break;
	case 7:
		SetConsoleTextAttribute(hStdOut, 0xF);
		break;	
	}
}
void ClearFigure(int Figure[7][4][8][12], int figure, int rotation, int x, int y)///КОЛОР
{
	int shiftLeft = ShiftFigureX(Figure, figure, rotation);
	int shiftUp = ShiftFigureY(Figure, figure, rotation);	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (Figure[figure][rotation][i][j] == FIGURE)
			{
				GotoXY(x + j - shiftLeft, y + i - shiftUp);
				cout << char(' ');
			}
		}
		cout << endl;
	}
}
int ShiftFigureX(int Figure[7][4][8][12], int figure, int rotation)
{
	int shiftX = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Figure[figure][rotation][j][i] == EMPTY);
			else return shiftX;
		}
		shiftX++;
	}
	return shiftX;
}
int ShiftFigureY(int Figure[7][4][8][12], int figure, int rotation)
{
	int shiftY = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (Figure[figure][rotation][i][j] == EMPTY);
			else return shiftY;
		}
		shiftY++;
	}
	return shiftY;
}
bool Collision(int Field[42][32], int Figure[7][4][8][12], int figure, int rotation, int x, int y)
{
	bool collision = false;
	int shiftLeft = ShiftFigureX(Figure, figure, rotation);
	int shiftUp = ShiftFigureY(Figure, figure, rotation);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (Figure[figure][rotation][i][j] == FIGURE && Field[y + i - shiftUp][x + j - shiftLeft] != EMPTY)
			{
				collision = true;
				return collision;
			}
		}
	}
	return collision;
}
void InitField(int Field[42][32], int Figure[7][4][8][12], int figure, int rotation, int x, int y)
{
	int shiftLeft = ShiftFigureX(Figure, figure, rotation);
	int shiftUp = ShiftFigureY(Figure, figure, rotation);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (Figure[figure][rotation][i][j] == FIGURE)
			{
				Field[y + i - shiftUp][x + j - shiftLeft] = figure+1;				
			}
		}
	}
}
void DeleteFullLine(int Field[42][32], int line, int column, int &score)
{
	bool full;
	int j;
	int i;
	int doubleLine = 0;
	for (i = line - 2; i>1; i--)
	{
		full = true;
		for (j = 1; j< column - 1; j++)
		{
			if (Field[i][j] == EMPTY)
			{
				full = false;
				break;
			}

		}
		if (full)
		{
			doubleLine += 1;
			for (int y = i; y > 1; y--)
			{
				for (int x = 1; x< column - 1; x++)
				{
					Field[y][x] = Field[y - 1][x];
				}
			}
			i = line - 1;
			if (doubleLine == 2)
			{
				PrintPlayField(Field, line, column);
				Sleep(100);
				doubleLine = 0;
				score += 20;
			}
		}
	}
}
////////////////////////////CONTROL
void InitControlField(int Array[][32], int line, int column)
{
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (i == 0 && j == 0)  Array[i][j] = char(201);                                          // г
			else if ((j == 0 || j == column - 1) && i > 0 && i < line - 1) Array[i][j] = char(186);      // ¦
			else if (i == line - 1 && j == 0) Array[i][j] = char(200);                                 // L
			else if (i == 0 && j == column - 1) Array[i][j] = char(187);                             // ¬
			else if (i == line - 1 && j == column - 1) Array[i][j] = char(188);                      // -
			else if (i == 0 || i == line - 1 && j != 0 && j != column - 1) Array[i][j] = char(205); // =
			else Array[i][j] = 0;
		}
	}
}
void PrintControlField(int Array[][32], int line, int column, char Tetris[][30], int tLine, int tColumn)
{
	for (int i = 0; i < line; i++)
	{
		GotoXY(34, i);
		for (int j = 0; j < column; j++)
		{
			cout << char(Array[i][j]);
		}
	}
	int Color = 3;
	SetColor(Color);
	for (int i = 0; i < tLine; i++)
	{
		GotoXY(35, 1 + i);
		for (int j = 0; j < tColumn; j++)
		{
			if (Tetris[i][j] == '0') cout << ' ';
			else cout << Tetris[i][j];
		}
		Sleep(50);
	}
	GotoXY(50, 9);
	cout << "LEVEL:";
	GotoXY(50, 12);
	cout << "SCORE:";
	GotoXY(35, 35);
	cout << char(17) << " LEFT";
	GotoXY(35, 36);
	cout << char(16) << " RIGHT";
	GotoXY(35, 37);
	cout << char(30) << " ROTATION";
	GotoXY(35, 38);
	cout << char(31) << " DOWN";
	GotoXY(35, 39);
	cout << 'Q' << " STOP PLAY";
	GotoXY(35, 40);
	cout << "Esc" << " QUIT GAME";
}
void PrintNextFigure(int Figure[7][4][8][12], int nextFigure)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			GotoXY(36 + j, 9 + i);
			cout << ' ';
		}
	}
	int shiftLeft = ShiftFigureX(Figure, nextFigure, 0);
	int shiftUp = ShiftFigureY(Figure, nextFigure, 0);
	int color = nextFigure + 1;
	SetColor(color);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (Figure[nextFigure][0][i][j] == FIGURE)
			{
				GotoXY(36 + j - shiftLeft, 9 + i - shiftUp);
				cout << char(177);
			}
		}		
	}
}
void PrintLevelScore(int &level, int &score, int& delay)
{
	int Color = 5;
	SetColor(Color);
	GotoXY(50, 10);
	cout << level;
	GotoXY(50, 13);
	cout << score;	
}
void PrintControleOptions()
{
	int Color = 3;
	SetColor(Color);
	GotoXY(35, 35);
	cout << 'S' << " Save record";
	GotoXY(35, 36);
	cout << 'R' << " Look records";
	GotoXY(35, 37);
	cout << "            ";
	GotoXY(35, 38);
	cout << "            ";
	GotoXY(35, 39);
	cout << "            ";
	GotoXY(35, 40);
	cout << "Esc" << " QUIT GAME";
}
int ControlLevelScoreDelay(int &level, int &score)
{
	if (score < 60) level = 1;
	else level = score / 60;
	int delay;	
	if (level == 1)
	{
		delay = startdelay;
		return delay;
	}
	else
	{		
		delay = startdelay - level * 100;
		return delay;
	}	
}
void EnterUser(Gamer &Player)
{
	int Color = 3;
	SetColor(Color);
	GotoXY(35, 15);
	ShowCursor(true);
	cout << "Enter name: ";
	cin.getline(Player.Name, 20);
	GotoXY(35, 17);
	ShowCursor(false);
}
int SaveToFile(Gamer &Player)
{
	int Color = 3;
	SetColor(Color);
	FILE *fPtr = nullptr;
	if (fopen_s(&fPtr, "Records.dat", "ab"))
	{
		perror("Error to open");
		return EXIT_FAILURE;
	}
	fwrite(Player.Name, 20, 1, fPtr);
	fwrite(&Player.score, sizeof(int), 1, fPtr);
	GotoXY(35, 17);
	cout << "Record was written!";
	Sleep(1000);
	GotoXY(35, 17);
	cout << "                    ";
	GotoXY(35, 15);
	cout << "                        ";
	fclose(fPtr);
	return EXIT_SUCCESS;
}
int LoadFromFile()
{
	int Color = 3;
	SetColor(Color);
	GotoXY(35, 15);
	cout << " Name " << setw(20) << "Score";
	FILE *fPtr = nullptr;
	if (_access("Records.dat", 0) == 0)
	{
		if (fopen_s(&fPtr, "Records.dat", "rb"))
		{
			cout << "Error to open" << endl;
			perror("Error to open");
			return EXIT_FAILURE;
		}
		int countFromFile = 0;
		int length = _filelength(_fileno(fPtr));
		int recordsInFile = length / 24;		
		for (int i = 0; i < recordsInFile; i++)
		{
			if (fread_s(Player.Name, 20, 20, 1, fPtr) < 1)
			{
				fclose(fPtr);
				cout << "Read error User";
				return EXIT_FAILURE;
			}
			if (fread_s(&Player.score, sizeof(int), sizeof(int), 1, fPtr) < 1)
			{
				fclose(fPtr);
				cout << "Read error";
				return EXIT_FAILURE;
			}
			GotoXY(36, 16 + i);
			cout << Player.Name; 
			GotoXY(57, 16 + i);
			cout << Player.score;
		}
		fclose(fPtr);
		return EXIT_SUCCESS;
	}
}