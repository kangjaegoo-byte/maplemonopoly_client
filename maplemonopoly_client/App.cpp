#include "pch.h"
#include "App.h"

LRESULT App::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	App* pApp = nullptr;

	if (message == WM_NCCREATE)
	{
		LPCREATESTRUCT pCS = (LPCREATESTRUCT)lParam;
		SetLastError(0);
		pApp = reinterpret_cast<App*>(pCS->lpCreateParams);
		if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pApp)))
		{
			if (GetLastError() != 0) return E_FAIL;
		}
	}
	else
	{
		pApp = reinterpret_cast<App*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	if (message == WM_GETMINMAXINFO && pApp == nullptr)
		return S_OK;

	return pApp->Dispatch(hWnd, message, wParam, lParam);
}
