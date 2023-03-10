#pragma once
class App;
/**************************************************
	Wnd : 윈도우 화면 클래스
**************************************************/
class Wnd
{
protected:
	HINSTANCE					m_hInstance;
	HWND						m_hwnd;
	int							m_width;
	int							m_height;

public:
	Wnd();
	~Wnd();

	void Init(HINSTANCE _hInstance, const wchar_t* _title, const wchar_t* _className, int _width, int _height, int _nCmdShow, App* _app);
	HWND GetHWND() { return m_hwnd; }
};

