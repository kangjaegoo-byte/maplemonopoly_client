#pragma once
class App
{
protected:
	HINSTANCE m_hInstance;
	HWND m_hwnd;
	WCHAR* m_className;
	WCHAR* m_classTitle;
	class Wnd* m_wnd;

public:
	App() {};
	virtual ~App() {};

	virtual bool Init(HINSTANCE _instance, const WCHAR* _className, const WCHAR* _classTitle, int _nCmdShow) abstract;
	virtual	int	Run() abstract;
	virtual LRESULT	Dispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) abstract;
	static  LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

