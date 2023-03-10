#include "pch.h"
#include "GameWnd.h"

GameWnd::GameWnd(HINSTANCE _instance, const wchar_t* _title, const wchar_t* _className, int _width, int _height, int _nCmdShow, App* _app)
{
	Wnd::Init(_instance, _title, _className, _width, _height, _nCmdShow, _app);
	ShowCursor(FALSE); // 마우스 커서 hide
}

GameWnd::~GameWnd()
{

}
