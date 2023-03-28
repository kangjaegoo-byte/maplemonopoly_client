#pragma once
class App;
class Wnd
{
protected:
	HINSTANCE m_hInstance;
	HWND m_hwnd;
	int	m_width;
	int	m_height;
public:
	Wnd();
	~Wnd();

	void Init(HINSTANCE _hInstance, const wchar_t* _title, const wchar_t* _className, int _width, int _height, int _nCmdShow, App* _app);
	HWND GetHWND() { return m_hwnd; }
};

