#include "tetris.h"


void BackGroundMusic()
{
	mciOpen.lpstrElementName = "TetrisMp3.mp3"; 
	mciOpen.lpstrDeviceType = "mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)& mciOpen);

	dwID = mciOpen.wDeviceID;

	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT,
		(DWORD)(LPVOID)& m_mciPlayParms);
}
void BackGroundMusicPause()
{
	mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY,
		(DWORD)(LPVOID)& m_mciPlayParms);
}
void BackGroundMusicResume()
{
	mciSendCommandW(dwID, MCI_RESUME, 0, NULL);
}

void LineClearSound()
{
	sndPlaySoundA("line.wav", SND_ASYNC | SND_NODEFAULT);
}

void HardDropSound()
{
	sndPlaySoundA("fall.wav", SND_ASYNC | SND_NODEFAULT);
}

void GameOverMusic()
{
	sndPlaySoundA("gameover.wav", SND_ASYNC | SND_NODEFAULT);
}