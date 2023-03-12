#include "pch.h"
#include "MaplemonopolyApp.h"
#include "GameWnd.h"
#include "SceneManager.h"
#include "FPSManager.h"
#include "ResourceManager.h"
#include "Bitmap.h"
#include "UserDTO.h"
MaplemonopolyApp* MaplemonopolyApp::m_instance = nullptr;

MaplemonopolyApp::MaplemonopolyApp()
{
}

MaplemonopolyApp::~MaplemonopolyApp()
{
	DebugClean();
}

MaplemonopolyApp* MaplemonopolyApp::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new MaplemonopolyApp();

	return m_instance;
}

bool MaplemonopolyApp::Init(HINSTANCE _instance, const WCHAR* _className, const WCHAR* _classTitle, int _nCmdShow)
{
	try 
	{
		D2D1Core::GetInstance()->Init();	// D2D1Core Init !!
		m_wnd = new GameWnd(_instance, _className, _classTitle, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, _nCmdShow, m_instance); // GameWnd Create...
		D2D1Core::GetInstance()->CreateRenderTarget(m_wnd->GetHWND()); // Create RenderTarget
		D2D1Core::GetInstance()->CreateCompatibleRenderTarget(); // Create CompatibleRenderTarget 

#if _DEBUG
		DebugInit();
#endif
		
		SceneManager::GetInstance()->Init();
		m_sceneManager = SceneManager::GetInstance();

		if (Network::GetInstance()->Init() == false) // Net Work Init
			return false;

		if (Network::GetInstance()->Connect() == false) // Net Work Connect And RecvProc
			return false;

		Scenetype next = LOGIN_SCENE;
		
		WCHAR mouseCursorPath [300] = L"..\\imgpack\\basics\\aero_arrow.png";
		WCHAR mouseLoadPath[1000] = L"";
		_wfullpath(mouseLoadPath, mouseCursorPath, _MAX_PATH);

		m_mousecursor = D2D1Core::GetInstance()->LoadBitmapByFileName(mouseLoadPath);

		Network::GetInstance()->SendPacket((char*)&next, CLIENT_LOADING_REQUEST, PACKET_HEADER_SIZE + sizeof(next), 0);
	}
	catch (int expn) 
	{
		return false;
	}
	return true;
}

int MaplemonopolyApp::Run()
{
	MSG msg = { 0 };

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}


		if (m_sceneManager && FPSManager::GetInstance()->OK())
		{
			Render();
		}

		Sleep(1);
	}

	return 0;
}

LRESULT MaplemonopolyApp::Dispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_KEYUP:
		break;

	case WM_KEYDOWN:
		break;

	case WM_CHAR:
		CharEvent(wParam);
		break;

	case WM_TIMER:
		break;

	case WM_SIZE:
		break;

	case WM_COMMAND:
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_MOUSEMOVE:
		MouseMoveEvent(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_LBUTTONUP:
		MouseClickEnvet(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_MOUSEWHEEL:
		break;

	case WM_VSCROLL:
		break;

	case WM_PAINT:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}

void MaplemonopolyApp::MouseMoveEvent(int _x, int _y)
{
	m_mx = _x;
	m_my = _y;
	if (m_sceneManager)
		m_sceneManager->MouseMoveEvent(_x, _y);
}

void MaplemonopolyApp::MouseClickEnvet(int _x, int _y)
{
	if (m_sceneManager)
		m_sceneManager->MouseClickEnvet(_x, _y);
}

void MaplemonopolyApp::CharEvent(WPARAM _key)
{
	if (m_sceneManager)
		m_sceneManager->CharEvent(_key);
}

void MaplemonopolyApp::Render()
{
	ID2D1Bitmap* bitmap = nullptr;
	D2D1Core::GetInstance()->GetCRT()->BeginDraw();

	m_sceneManager->Update();

#if _DEBUG
	DebugRender();
#endif
	MouseCursorRender();

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

void MaplemonopolyApp::MouseCursorRender()
{
	D2D1Core::GetInstance()->GetCRT()->DrawBitmap(m_mousecursor->GetBitmap(), D2D1::RectF(m_mx,m_my,m_mx+32,m_my+32));
}

void MaplemonopolyApp::DebugInit()
{
	D2D1Core::GetInstance()->CreateColorBrush(&m_blackBrush, D2D1::ColorF::Black);
	D2D1Core::GetInstance()->CreateColorBrush(&m_whiteBrush, D2D1::ColorF::White);
	D2D1Core::GetInstance()->SetFontFormat(&m_textFormat, L"³ª´®°íµñ", 10);
}

void MaplemonopolyApp::DebugRender()
{
	D2D1Core::GetInstance()->GetCRT()->FillRectangle(D2D1::RectF(0.0f, 0.0f, 65.0f, 18.0f), m_whiteBrush);
	WCHAR text[1000];
	swprintf_s(text, _countof(text), L"X:%d, Y:%d", m_mx, m_my);
	D2D1Core::GetInstance()->GetCRT()->DrawTextW(text, wcslen(text), m_textFormat, D2D1::RectF(0.0f, 0.0f, 100.0f, 25.0f), m_blackBrush);
}

void MaplemonopolyApp::DebugClean()
{
	m_blackBrush->Release();
	m_whiteBrush->Release();
	m_textFormat->Release();
	delete m_mousecursor;
}

void MaplemonopolyApp::SetUserInfo(UserDTO* _userDTO)
{
	m_userInfo = _userDTO;
}

UserDTO* MaplemonopolyApp::GetUserInfo()
{
	return m_userInfo;
}
