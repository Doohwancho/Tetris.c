#pragma once
#pragma comment(lib,"winmm.lib")


#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include <mmsystem.h>

#define _CRT_SECURE_NO_WARNINGS
#define SOUND_FILE_NAME "Tetris.wav"

#define SIZE_X 12 //12
#define SIZE_Y 24 //24
#define SIZE_X_ADJ  10
#define SIZE_Y_ADJ  2

#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define UP 72
#define SPACE 32

#define TRUE 1 //�浹�� ���ߴٸ�
#define FALSE 0 //�浹�� �ߴٸ�

enum { EMPTY = 0, MBLOCK = 1, OVERLINE = 2, SBLOCK = 3, WALL = 4, FBLOCK = 5 };

int blocks[7][4][4][4];
int block_X;
int block_Y;
int block_rotation;
int block_type;
int flag_crush;
int flag_neednewblock;
int board[SIZE_Y][SIZE_X];
int copyboard[SIZE_Y][SIZE_X];
int level;
int deleteline_total;
int deleteline_combo;
int gamespeed;
int bestscore;
int score;
int flag_harddrop;
int shuffleblock[7];
int count;
int block_typeN1;
int block_typeN2;
int block_typeN3;

//2_ConsoleController �ҽ������� �Լ� ����
void Gotoxy(int x, int y);
void ConsoleSize();
void RemoveScrollbar();
void RemoveCurser();
void SetConsole();
void MusicPlay();

//3_GameDrawer �ҽ������� �Լ� ����
void IntroDrawer();
void UIDrawer();
void PrintGameBoard();
void PrintGameOver();
void PrintNextBlock();

//4_BlockMaker �ҽ������� �Լ� ����
void NewBlockMaker();
void MakeShadowBlock();
void DeleteShadowBlock();
void BlockShuffler();
int BlockSelecter();

//5_BlockController �ҽ������� �Լ� ����
void BlockMove(int x, int y, int z);
void BlockFix();
void KeyboardController();
void AutoDrop();

//6_BlockDetector
int CrushCheck(int x, int y, int z);
void LineCheck();

//7_GameManager �ҽ������� �Լ� ����
void ResetCopyGameBoard();
void ResetGameBoard();
void SpeedManager();
void ScoreManager();
void PrintInformation();
void ResetInformation();
void GameOverCheck();
void NextBlockPush();