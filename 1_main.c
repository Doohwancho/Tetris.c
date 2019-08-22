//메인함수가 들어가는 파일


#include "tetris.h"

int main()
{
	SetConsole();
	srand((unsigned)time(NULL));
	IntroDrawer();

	ResetGameBoard();
	ResetCopyGameBoard();
	ResetInformation();
	NewBlockMaker();
	PrintGameBoard();
	PrintInformation();

	while (1)
	{
		SpeedManager();

		for(int i = 0; i < 4; i++) //한칸 아래로 떨어지는동안 6번의 입력을 받을 수 있음
		{
			KeyboardController();
			MakeShadowBlock();

			PrintGameBoard();
			Sleep(gamespeed);

			DeleteShadowBlock();

			if (flag_harddrop == 1)
			{
				flag_harddrop = 0;
				break;
			}
		}
		AutoDrop();
		PrintInformation();
		GameOverCheck();

		if (flag_neednewblock == 1)
			NewBlockMaker();
	}
	return 0;
}