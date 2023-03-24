#include "pch.h"
#include "MaplemonopolyApp.h"

MaplemonopolyApp app;

int APIENTRY wWinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstace, LPTSTR _lpCmdLine, int _nCmdShow)
{
	srand(time(NULL));

	if (app.Init(_hInstance, L"maplemonopoly", L"maplemonopoly", _nCmdShow) == false)
		return 0;

	return app.Run();
}
