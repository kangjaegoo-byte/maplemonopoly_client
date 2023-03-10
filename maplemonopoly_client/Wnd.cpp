#include "pch.h"
#include "Wnd.h"
#include "App.h"
Wnd::Wnd()
{
}

Wnd::~Wnd()
{
}

void Wnd::Init(HINSTANCE _hInstance, const wchar_t* _title, const wchar_t* _className, int _width, int _height, int _nCmdShow, App* _app)
{
	m_width = _width;
	m_height = _height;
	m_hInstance = _hInstance;

	WNDCLASSEX wecx;
	wecx.cbSize = sizeof(WNDCLASSEX);
	wecx.style = CS_HREDRAW | CS_VREDRAW;
	wecx.cbClsExtra = 0;
	wecx.cbWndExtra = sizeof(LONG_PTR);
	wecx.hInstance = _hInstance;
	wecx.hIcon = LoadIcon(_hInstance, IDI_APPLICATION);
	wecx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wecx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wecx.lpszClassName = _className;
	wecx.lpszMenuName = nullptr;
	wecx.hIconSm = LoadIcon(wecx.hInstance, IDI_APPLICATION);
	wecx.lpfnWndProc = _app->WndProc;  // 정적함수
	if (!RegisterClassEx(&wecx))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx Main failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);
		return;
	}

	RECT rc = { 0, 0, m_width, m_height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	m_hwnd = CreateWindow(
		_className,
		_title,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0,
		rc.right - rc.left, rc.bottom - rc.top,
		NULL,
		NULL,
		_hInstance,
		_app);

	ShowWindow(m_hwnd, _nCmdShow);
	UpdateWindow(m_hwnd);
}
