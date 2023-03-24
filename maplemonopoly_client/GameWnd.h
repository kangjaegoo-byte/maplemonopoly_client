#pragma once
#include "Wnd.h"
class GameWnd : public Wnd
{
private:
	int m_mx;
	int m_my;
	Bitmap* m_mousecursor = nullptr;
	ID2D1SolidColorBrush* m_whiteBrush;
	ID2D1SolidColorBrush* m_blackBrush;
	IDWriteTextFormat* m_textFormat;

public:
	GameWnd(HINSTANCE _instance, const wchar_t* _title, const wchar_t* _className, int _width, int _height, int _nCmdShow, App* _app);
	~GameWnd();

	void Render();
	void DebugInit();
	void DebugRender();
	void MouseMoveEvent(int _x, int _y);
};

