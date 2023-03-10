#include "pch.h"
#include "MaplemonopolyApp.h"

int APIENTRY wWinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstace, LPTSTR _lpCmdLine, int _nCmdShow)
{
	if (MaplemonopolyApp::GetInstance()->Init(_hInstance, L"maplemonopoly", L"maplemonopoly", _nCmdShow) == false)
		return 0;

	return MaplemonopolyApp::GetInstance()->Run();
}
