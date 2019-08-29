//유저의 입력과 블록동 상태변경 등을 담당하는 파일

#include "tetris.h"

void BlockMove(int inputX, int inputY, int input_rotation)
{
	int temp_rotation = block_rotation + input_rotation;
	if (temp_rotation > 3)
		temp_rotation = 0;


	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blocks[block_type][block_rotation][y][x] == 1)
				copyboard[block_Y + y][block_X + x] = EMPTY;
		}
	}

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blocks[block_type][temp_rotation][y][x] == 1)
				copyboard[block_Y + y + inputY][block_X + x + inputX] = MBLOCK;
		}
	}
	block_X = block_X + inputX;
	block_Y = block_Y + inputY;
	block_rotation = temp_rotation;
}

void BlockFix()
{
	HardDropSound();
	for (int y = 0; y < SIZE_Y; y++)
	{
		for (int x = 0; x < SIZE_X; x++)
		{
			if (copyboard[y][x] == MBLOCK)
				copyboard[y][x] = FBLOCK;
		}
	}
	flag_neednewblock = 1;
	return;
}

void KeyboardController()
{
	int key;
	if (_kbhit()) //키보드 입력을 받았다면
	{
		key = _getch();
		if (key == 224) //받은키가 방향키면
		{
			key = _getch(); //한번 더 받는다.
			switch (key)
			{
			case LEFT:
				if(CrushCheck(-1,0,0)==TRUE)
					BlockMove(-1, 0, 0);
				break;
			case RIGHT:
				if(CrushCheck(1,0,0)==TRUE)
					BlockMove(1, 0, 0);
				break;
			case DOWN:
				if(CrushCheck(0,1,0)==TRUE)
					BlockMove(0, 1, 0);
				break;
			case UP:
				for (int rotatemove_y = 0; ; rotatemove_y--)
				{
					for (int rotatemove_x = 0; rotatemove_x < 3; rotatemove_x++)
					{
						for (int n = 0; n < 2; n++)
						{
							rotatemove_x *= -1; //보정치를 양수만 하면 보정이 오른쪽으로만 됨

							if (CrushCheck(rotatemove_x, rotatemove_y, 1) == TRUE)
							{
								BlockMove(rotatemove_x, rotatemove_y, 1);
								return;
							}
						}
					}
				}

				if (CrushCheck(0, 0, 1) == TRUE)
					BlockMove(0, 0, 1);
				break;
			}
		}
		else
			switch (key)
			{
			case SPACE:
				flag_harddrop = 1;
				while (flag_crush != 1)
					AutoDrop();
				break;
			}
	}
	return;
}

void AutoDrop()
{
	if (CrushCheck(0, 1, 0) == TRUE && flag_crush == 0)
		BlockMove(0, 1, 0);

	else if (CrushCheck(0, 1, 0) == TRUE && flag_crush == 1)
		flag_crush = 0;

	else if (CrushCheck(0, 1, 0) == FALSE && flag_crush == 0)
		flag_crush = 1;

	else if (CrushCheck(0, 1, 0) == FALSE && flag_crush == 1)
	{
		BlockFix();
		LineCheck();
		flag_crush = 0;
	}
}