#pragma once
#include "Wnd.h"
class App;
/**************************************************
	GameWnd : 게임 화면 기반(FRAME)
**************************************************/
class GameWnd : public Wnd
{
public:
	GameWnd(HINSTANCE _instance, const wchar_t* _title, const wchar_t* _className, int _width, int _height, int _nCmdShow, App* _app);
	~GameWnd();
};
