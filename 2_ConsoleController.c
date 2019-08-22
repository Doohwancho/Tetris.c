//콘솔창 세팅과 관련한 함수들이 들어가는 파일

#include "tetris.h"

void Gotoxy(int x, int y)
{
	COORD pos = { 2*x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void RemoveCurser()
{
	CONSOLE_CURSOR_INFO curinfo = { 0, };
	curinfo.dwSize = 1;
	curinfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}

void ConsoleSize()
{
	system("mode con cols=79 lines=30"); //가로 79, 세로 30
}

void RemoveScrollbar()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

void SetConsole()
{
	ConsoleSize();
	RemoveScrollbar();
	RemoveCurser();
	MusicPlay();
}


void MusicPlay() // 음악을 반복재생합니다.
{
	PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
