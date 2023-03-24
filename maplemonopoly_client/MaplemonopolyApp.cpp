#include "pch.h"
#include "MaplemonopolyApp.h"
#include "GameWnd.h"
#include "FPS.h"
#include "LoadingScene.h"
#include "LoginScene.h"
#include "LobbyScene.h"
#include "GameScene.h"
#include "GameService.h"
MaplemonopolyApp::MaplemonopolyApp()
{
}

MaplemonopolyApp::~MaplemonopolyApp()
{
}

bool MaplemonopolyApp::Init(HINSTANCE _instance, const WCHAR* _className, const WCHAR* _classTitle, int _nCmdShow)
{
	try 
	{
		D2D1Core::GetInstance()->Init();
		m_wnd = new GameWnd(_instance, _classTitle, _className, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, _nCmdShow, this);
		GameService::GetInstance()->Init();

		if (Network::GetInstance()->Init() == false) // Net Work Init
			return false;

		if (Network::GetInstance()->Connect() == false) // Net Work Connect And RecvProc
			return false;

	}
	catch (int expn)
	{
		MessageBox(NULL, L"프로그램 초기화 에러", L"ERROR", MB_OK);
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

		SceneManager::GetInstance()->Update();

		if (FPS::GetInstance()->OK())
			m_wnd->Render();
		
		GameService::GetInstance()->SceneChange();

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
		MouseClickEnvet(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_MOUSEMOVE:
		MouseMoveEvent(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_LBUTTONUP:
		MouseClickUpEnvet(LOWORD(lParam), HIWORD(lParam));
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
	m_wnd->MouseMoveEvent(_x, _y);
}

void MaplemonopolyApp::MouseClickEnvet(int _x, int _y)
{
	SceneManager::GetInstance()->MouseClickEvent(_x, _y);
}

void MaplemonopolyApp::MouseClickUpEnvet(int _x, int _y)
{
	SceneManager::GetInstance()->MouseClickUpEnvet(_x, _y);
}

void MaplemonopolyApp::CharEvent(WPARAM _key)
{
	SceneManager::GetInstance()->CharEvent(_key);
}
