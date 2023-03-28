#include "pch.h"
#include "GameWnd.h"

GameWnd::GameWnd(HINSTANCE _instance, const wchar_t* _title, const wchar_t* _className, int _width, int _height, int _nCmdShow, App* _app) 
{
	Wnd::Init(_instance, _title, _className, _width, _height, _nCmdShow, _app);
	ShowCursor(FALSE);
	

	D2D1Core::GetInstance()->CreateRenderTarget(m_hwnd); // Create RenderTarget
	D2D1Core::GetInstance()->CreateCompatibleRenderTarget(); // Create CompatibleRenderTarget 
	DebugInit();

	WCHAR mouseCursorPath[300] = L"..\\imgpack\\basics\\aero_arrow.png";
	WCHAR mouseLoadPath[1000] = L"";
	_wfullpath(mouseLoadPath, mouseCursorPath, _MAX_PATH);
	m_mousecursor = D2D1Core::GetInstance()->LoadBitmapByFileName(mouseLoadPath);

}

GameWnd::~GameWnd()
{
	if (m_mousecursor)
		delete m_mousecursor;
}

void GameWnd::Render()
{
	ID2D1Bitmap* bitmap = nullptr;
	D2D1Core::GetInstance()->GetCRT()->BeginDraw();

	SceneManager::GetInstance()->Render();
	D2D1Core::GetInstance()->GetCRT()->DrawBitmap(m_mousecursor->GetBitmap(), D2D1::RectF(m_mx, m_my, m_mx + 32, m_my + 32));
	DebugRender();

	D2D1Core::GetInstance()->GetCRT()->EndDraw();
	D2D1Core::GetInstance()->GetCRT()->GetBitmap(&bitmap);
	D2D1Core::GetInstance()->GetRT()->BeginDraw();

	RECT rect;
	GetClientRect(D2D1Core::GetInstance()->GetHWND(), &rect);
	D2D1_RECT_F rt_dest = { rect.left, rect.top, rect.right, rect.bottom };

	if (bitmap)
		D2D1Core::GetInstance()->GetRT()->DrawBitmap(bitmap, rt_dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	D2D1Core::GetInstance()->GetRT()->EndDraw();
	bitmap->Release();
}

void GameWnd::DebugInit()
{
	D2D1Core::GetInstance()->CreateColorBrush(&m_blackBrush, D2D1::ColorF::Black);
	D2D1Core::GetInstance()->CreateColorBrush(&m_whiteBrush, D2D1::ColorF::White);
	D2D1Core::GetInstance()->SetFontFormat(&m_textFormat, L"³ª´®°íµñ", 10);
}

void GameWnd::DebugRender()
{
	D2D1Core::GetInstance()->GetCRT()->FillRectangle(D2D1::RectF(0.0f, 0.0f, 65.0f, 18.0f), m_whiteBrush);
	WCHAR text[1000];
	swprintf_s(text, _countof(text), L"X:%d, Y:%d", m_mx, m_my);
	D2D1Core::GetInstance()->GetCRT()->DrawTextW(text, wcslen(text), m_textFormat, D2D1::RectF(0.0f, 0.0f, 100.0f, 25.0f), m_blackBrush);
}

void GameWnd::MouseMoveEvent(int _x, int _y)
{
	m_mx = _x;
	m_my = _y;
}
