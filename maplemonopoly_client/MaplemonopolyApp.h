#pragma once
#include "App.h"
class MaplemonopolyApp : public App
{
private:
	class GameWnd* m_wnd;

public:
	MaplemonopolyApp();
	~MaplemonopolyApp();

	virtual bool Init(HINSTANCE _instance, const WCHAR* _className, const WCHAR* _classTitle, int _nCmdShow) override;
	virtual	int	Run() override;
	virtual LRESULT	Dispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	void MouseMoveEvent(int _x, int _y);
	void MouseClickEnvet(int _x, int _y);
	void MouseClickUpEnvet(int _x, int _y);
	void CharEvent(WPARAM _key);
};
		
