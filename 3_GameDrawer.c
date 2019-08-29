//게임화면에 그리는 업무를 담당하는 파일

#include "tetris.h"

void IntroDrawer()
{
	int x = 5;
	int y = 2;

	Gotoxy(x + 1, y + 0); printf("☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	Gotoxy(x + 1, y + 2); printf("  ■■■  ■■■  ■■■  ■■■    ■■■  ■■■ \n"); Sleep(20);
	Gotoxy(x + 1, y + 3); printf("    ■    ■        ■    ■  ■      ■    ■      \n"); Sleep(20);
	Gotoxy(x + 1, y + 4); printf("    ■    ■■■    ■    ■■■      ■    ■■■  \n"); Sleep(20);
	Gotoxy(x + 1, y + 5); printf("    ■    ■        ■    ■  ■      ■        ■  \n"); Sleep(20);
	Gotoxy(x + 1, y + 6); printf("    ■    ■■■    ■    ■    ■  ■■■  ■■■  \n"); Sleep(20);
	Gotoxy(x + 1, y + 8); printf("★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆");

	Gotoxy(x + 1, y + 18); printf("---------------------- HOWTOPLAY ---------------------");
	Gotoxy(x + 1, y + 20); printf("[◀] LEFT MOVE  [▶] RIGHT MOVE  [SPC] HARD DROP");
	Gotoxy(x + 1, y + 22); printf("[▼] DOWN MOVE  [▲] ROTATE");
	Gotoxy(x + 1, y + 24); printf("------------------------------------------------------");

	while (1)
	{
		if (_kbhit()) // 입력이 있을때까지
			break;
		Gotoxy(x + 8, y + 13); printf("  >> PRESS ANY BUTTON <<  "); Sleep(200);
		Gotoxy(x + 8, y + 13); printf("                          "); Sleep(200);
	}

	while (_kbhit()) // 버퍼 지우기
		_getch();

	system("cls"); // 화면 지우기
}

void PrintGameBoard()
{
	for (int y = 0; y < SIZE_Y; y++)
	{
		for (int x = 0; x < SIZE_X; x++)
		{
			if (y == 2 && x != 0 && x != SIZE_X - 1 && board[y][x] == EMPTY)
				copyboard[y][x] = OVERLINE;

			if (copyboard[y][x] != board[y][x])
			{
				board[y][x] = copyboard[y][x];

				switch (board[y][x])
				{
				case EMPTY:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ); //Gotoxy(x, y);
					printf("  ");
					break;

				case MBLOCK:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("■");
					break;

				case OVERLINE:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf(". ");
					break;

				case SBLOCK:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("◎");
					break;

				case WALL:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("▩");
					break;

				case FBLOCK:
					Gotoxy(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("□");
					break;
				}
			}
		}
	}
}

void UIDrawer() // UI를 그립니다.
{

	int x = 2, y = 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	Gotoxy(23 + x, y); printf("[NEXT]"); // 1번 블록칸
	Gotoxy(21 + x, 1 + y); printf("┌");
	Gotoxy(27 + x, 1 + y); printf("┐");
	Gotoxy(21 + x, 6 + y); printf("└");
	Gotoxy(27 + x, 6 + y); printf("┘");

	Gotoxy(21 + x, 7 + y); printf("┌"); // 2번 블록칸
	Gotoxy(27 + x, 7 + y); printf("┐");
	Gotoxy(21 + x, 11 + y); printf("└");
	Gotoxy(27 + x, 11 + y); printf("┘");


	Gotoxy(21 + x, 12 + y); printf("┌"); // 3번 블록칸
	Gotoxy(27 + x, 12 + y); printf("┐");
	Gotoxy(21 + x, 15 + y); printf("└");
	Gotoxy(27 + x, 15 + y); printf("┘");


	Gotoxy(21 + x, 17 + y); printf(" [ BESTSCORE ]: ");
	Gotoxy(21 + x, 19 + y); printf(" [ YOURSCORE ]: ");
	Gotoxy(21 + x, 21 + y); printf(" [   LEVEL   ]: ");
	Gotoxy(21 + x, 23 + y); printf(" [  DESTROY  ]: ");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

}


void PrintInformation()
{
	/*
	Gotoxy(15, 10);
	printf("BestScore:%d", bestscore);

	Gotoxy(15, 12);
	printf("Score:%d", score);

	Gotoxy(15, 14);
	printf("DeleteLine:%d", deleteline_total);

	Gotoxy(15, 16);
	printf("Level:%d",level);
	*/
	
	//Gotoxy(31, 19); printf("                   ");
	//Gotoxy(31, 21); printf("                   ");
	//Gotoxy(31, 23); printf("                   ");
	//Gotoxy(31, 25); printf("                   ");

	Gotoxy(31, 19); printf("%d", bestscore);
	Gotoxy(31, 21); printf("%d", score);
	Gotoxy(31, 23); printf("%d", level);
	Gotoxy(31, 25); printf("%d", deleteline_total);
	
}

void PrintGameOver()
{
	BackGroundMusicPause();
	GameOverMusic();
	for (int y = 0; y < SIZE_Y - 1; y++)
	{
		for (int x = 1; x < SIZE_X - 1; x++)
		{
			copyboard[y][x] = EMPTY;
		}
	}

	PrintGameBoard();
	Gotoxy(14, 10); //4, 12
	printf("GameOver");

	Gotoxy(12, 14); //2, 12
	printf("Press Any Button");

	Sleep(500);
	
	while (_kbhit())
		_getch();

	_getch();
	
}

void PrintNextBlock()
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blocks[block_typeN1][0][y][x] == 1)
			{
				Gotoxy(24 + x, 4 + y);
				printf("■");
			}
			else
			{
				Gotoxy(24 + x, 4 + y);
				printf("  ");
			}

			if (blocks[block_typeN2][0][y][x] == 1)
			{
				Gotoxy(24 + x, 9 + y);
				printf("■");
			}
			else
			{
				Gotoxy(24 + x, 9 + y);
				printf("  ");
			}
			if (blocks[block_typeN3][0][y][x] == 1)
			{
				Gotoxy(24 + x, 14 + y);
				printf("■");
			}
			else
			{
				Gotoxy(24 + x, 14 + y);
				printf("  ");
			}
			
		}
	}
}