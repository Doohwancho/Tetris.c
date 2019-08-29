//게임 점수 획득, 난이도 조절, 게임종료와 같은 진행 담당

#include "tetris.h"

void ResetCopyGameBoard()
{
	for (int y = 0; y < SIZE_Y; y++)
		for (int x = 0; x < SIZE_X; x++)
			copyboard[y][x] = EMPTY;

	for (int y = 0; y < SIZE_Y; y++)
		for (int x = 0; x < SIZE_X; x++)
		{
			if (x == 0 || x == SIZE_X - 1)
				copyboard[y][x] = WALL;

			if (y == SIZE_Y - 1)
				copyboard[y][x] = WALL;

			if (y == 2 && x != 0 && x != SIZE_X - 1)
				copyboard[y][x] = OVERLINE;
		}
}

void ResetGameBoard()
{
	for (int y = 0; y < SIZE_Y; y++)
		for (int x = 0; x < SIZE_X; x++)
			board[y][x] = 1000;
}

void SpeedManager()
{
	if (deleteline_total < 10)
	{
		level = 1;
		gamespeed = 75;
		return;
	}
	else if (deleteline_total < 20)
	{
		level = 2;
		gamespeed = 45;
		return;
	}
	else if (deleteline_total < 30)
	{
		level - 3;
		gamespeed = 35;
		return;
	}
	else if (deleteline_total < 40)
	{
		level = 4;
		gamespeed = 30;
		return;
	}
	else if (deleteline_total < 50)
	{
		level = 5;
		gamespeed = 25;
		return;
	}
	else if (deleteline_total < 60)
	{
		level = 6;
		gamespeed = 20;
		return;
	}
	else if (deleteline_total < 70)
	{
		level = 7;
		gamespeed = 15;
		return;
	}
	else
	{
		level = 8;
		gamespeed = 10;
		return;
	}
}

void ScoreManager()
{
	score += 5;
	switch (deleteline_combo)
	{
	case 1:
		score += 50;
		return;
	case 2:
		score += 150;
		return;
	case 3:
		score += 300;
		return;
	case 4:
		score += 500;
		return;
	default:
		return;
	}
}

void ResetInformation()
{
	UIDrawer();
	level = 1;
	score = 0;
	deleteline_total = 0;
	gamespeed = 50;
	count = 7;

	block_typeN1 = BlockSelecter();
	block_typeN2 = BlockSelecter();
	block_typeN3 = BlockSelecter();

	errno_t err;
	FILE* data;

	err = fopen_s(&data, "score.txt", "rt");

	if (data == 0)
		bestscore = 0;
	else
	{
		fscanf_s(data, "%d", &bestscore); // 있으면 그 값을 넣어준다.
		fclose(data);
	}
}

void GameOverCheck()
{
	for (int x = 1; x < SIZE_X - 2; x++)
	{
		if (copyboard[2][x] == FBLOCK)
		{
			if (bestscore < score)
			{
				errno_t err;
				FILE* data;

				err = fopen_s(&data, "score.txt", "wt");

				if (data == 0)
				{
					Gotoxy(0, 0);
					printf("데이터 저장에 실패했습니다.");
				}
				else
				{
					fprintf(data, "%d", score);
					fclose(data);
				}
			}

			PrintGameOver();

			system("cls");

			BackGroundMusicResume();
			ResetGameBoard();
			ResetCopyGameBoard();
			PrintGameBoard();
			ResetInformation();
			PrintInformation();
		}
	}
}

void NextBlockPush()
{
	block_type = block_typeN1;
	block_typeN1 = block_typeN2;
	block_typeN2 = block_typeN3;
	block_typeN3 = BlockSelecter();
}