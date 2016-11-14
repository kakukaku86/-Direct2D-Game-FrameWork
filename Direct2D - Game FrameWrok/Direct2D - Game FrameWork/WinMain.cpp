#include "stdfx.h"
#include "GameManager.h"

GameManager* gm = nullptr;

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	GameManager Gm;
	gm = &Gm;

	if (FAILED(Gm.Create(hInstance)))
		return -1;

	return gm->Loop();
}