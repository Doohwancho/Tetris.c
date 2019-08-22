//블록 생성과 관련된 업무를 담당하는 파일

#include "tetris.h"

blocks[7][4][4][4] = // [블록종류][회전][세로][가로]
{
	// J미노(0번 블록)
	{
		0,0,0,0,// 0번 방향
		0,1,0,0,
		0,1,1,1,
		0,0,0,0,

		0,0,0,0,// 1번 방향
		0,0,1,1,
		0,0,1,0,
		0,0,1,0,

		0,0,0,0,// 2번 방향
		0,0,0,0,
		0,1,1,1,
		0,0,0,1,

		0,0,0,0,// 3번 방향
		0,0,1,0,
		0,0,1,0,
		0,1,1,0
	},
	// L미노(1번 블록)
	{
		0,0,0,0,// 0번 방향
		0,0,0,1,
		0,1,1,1,
		0,0,0,0,

		0,0,0,0,// 1번 방향
		0,0,1,0,
		0,0,1,0,
		0,0,1,1,

		0,0,0,0,// 2번 방향
		0,0,0,0,
		0,1,1,1,
		0,1,0,0,

		0,0,0,0,// 3번 방향
		0,1,1,0,
		0,0,1,0,
		0,0,1,0
	},
	// O미노(2번 블록)
	{
		0,0,0,0,// 0번 방향
		0,1,1,0,
		0,1,1,0,
		0,0,0,0,

		0,0,0,0,// 1번 방향
		0,1,1,0,
		0,1,1,0,
		0,0,0,0,

		0,0,0,0,// 2번 방향
		0,1,1,0,
		0,1,1,0,
		0,0,0,0,

		0,0,0,0,// 3번 방향
		0,1,1,0,
		0,1,1,0,
		0,0,0,0
	},
	// T미노(3번 블록)
	{
		0,0,0,0,// 0번 방향
		0,0,1,0,
		0,1,1,1,
		0,0,0,0,

		0,0,0,0,// 1번 방향
		0,0,1,0,
		0,0,1,1,
		0,0,1,0,

		0,0,0,0,// 2번 방향
		0,0,0,0,
		0,1,1,1,
		0,0,1,0,

		0,0,0,0,// 3번 방향
		0,0,1,0,
		0,1,1,0,
		0,0,1,0
	},
	// I미노(4번 블록)
	{
		0,0,0,0,// 0번 방향
		0,0,0,0,
		1,1,1,1,
		0,0,0,0,

		0,0,1,0,// 1번 방향
		0,0,1,0,
		0,0,1,0,
		0,0,1,0,

		0,0,0,0,// 2번 방향
		1,1,1,1,
		0,0,0,0,
		0,0,0,0,

		0,1,0,0,// 3번 방향
		0,1,0,0,
		0,1,0,0,
		0,1,0,0
	},
	// Z미노(5번 블록)
	{
		0,0,0,0,// 0번 방향
		0,1,1,0,
		0,0,1,1,
		0,0,0,0,

		0,0,0,1,// 1번 방향
		0,0,1,1,
		0,0,1,0,
		0,0,0,0,

		0,1,1,0,// 2번 방향
		0,0,1,1,
		0,0,0,0,
		0,0,0,0,

		0,0,1,0,// 3번 방향
		0,1,1,0,
		0,1,0,0,
		0,0,0,0
	},
	// S미노(6번 블록)
	{
		0,0,0,0,// 0번 방향
		0,0,1,1,
		0,1,1,0,
		0,0,0,0,

		0,0,1,0,// 1번 방향
		0,0,1,1,
		0,0,0,1,
		0,0,0,0,

		0,0,1,1,// 2번 방향
		0,1,1,0,
		0,0,0,0,
		0,0,0,0,

		0,1,0,0,// 3번 방향
		0,1,1,0,
		0,0,1,0,
		0,0,0,0
	}
};

void NewBlockMaker()
{
	block_type = BlockSelecter();

	block_X = 3;
	block_Y = 0;
	block_rotation = 0;

	NextBlockPush();
	PrintNextBlock();

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blocks[block_type][block_rotation][y][x] == 1)
				copyboard[block_Y + y][block_X + x] = MBLOCK;
		}
	}
	flag_neednewblock = 0;
}

void MakeShadowBlock()
{
	int shadow_Y = 0;
	while (1)
	{
		if (CrushCheck(0, shadow_Y + 1, 0) == TRUE)
			++shadow_Y;

		if (CrushCheck(0, shadow_Y + 1, 0) == FALSE)
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					if (blocks[block_type][block_rotation][y][x] == 1 && copyboard[block_Y + y + (shadow_Y)][block_X + x] < 1)
						copyboard[block_Y + y + (shadow_Y)][block_X + x] = SBLOCK;
			
				}
			}
			shadow_Y = 0;
			break;
		}
	}
}

void DeleteShadowBlock()
{
	for (int y = 0; y < SIZE_Y - 1; y++)
	{
		for (int x = 1; x < SIZE_X - 1; x++)
		{
			if (copyboard[y][x] == SBLOCK)
				copyboard[y][x] = EMPTY;
		}
	}
}

void BlockShuffler()
{
	int j, temp;
	for (int i = 0; i < 7; i++)
	{
		shuffleblock[i] = i;
	}

	for (int i = 0; i < 7; i++)
	{
		j = rand() & 7;

		temp = shuffleblock[i];
		shuffleblock[i] = shuffleblock[j];
		shuffleblock[j] = temp;
	}
}

int BlockSelecter()
{
	count++;

	if (count > 6)
	{
		BlockShuffler();
		count = 0;
	}
	return shuffleblock[count];
}
