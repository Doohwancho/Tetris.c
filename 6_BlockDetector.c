//블럭끼리 부딪혔는지, 한줄이 다 채워졌는지와 같은 탐색엄무 담당

#include "tetris.h"

int CrushCheck(int blockX_ODJ, int blockY_ODJ, int r_ODJ)
{
	int temp_rotation = block_rotation + r_ODJ;
	if (temp_rotation > 3)
		temp_rotation = 0;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blocks[block_type][temp_rotation][y][x] == 1 && copyboard[block_Y + blockY_ODJ + y][block_X + blockX_ODJ + x] > 3)
				return FALSE;
		}
	}
	return TRUE;
}

void LineCheck() 
{
	int k; 
	int block_linecheck;

	for (int y = SIZE_Y - 2; y > 2;) 
	{
		block_linecheck = 0; 

		for (int x = 1; x < SIZE_X - 1; x++) 
			if (copyboard[y][x] == FBLOCK) 
				block_linecheck++; 

		if (block_linecheck == SIZE_X - 2) 
		{
			deleteline_total++;
			deleteline_combo++;
			for (k = y; k > 1; k--) 
				for (int l = 1; l < SIZE_X - 1; l++)
				{
					if (copyboard[k - 1][l] != OVERLINE) 
						copyboard[k][l] = copyboard[k - 1][l];

					if (copyboard[k - 1][l] == OVERLINE)
						copyboard[k][l] = EMPTY;
				}
		}
		else
			y--; 
	}
	ScoreManager();
	deleteline_combo = 0;
}