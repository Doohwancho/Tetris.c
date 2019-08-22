//�����Լ��� ���� ����


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

		for(int i = 0; i < 4; i++) //��ĭ �Ʒ��� �������µ��� 6���� �Է��� ���� �� ����
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