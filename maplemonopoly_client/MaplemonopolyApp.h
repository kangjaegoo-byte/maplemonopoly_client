#pragma once
#include "App.h"
class SceneManager;
class Bitmap;
class UserDTO;
/**************************************************
	MaplemonopolyApp : 메이플모노폴리 어플리케이션
**************************************************/
class MaplemonopolyApp : public App
{
private:
	static MaplemonopolyApp*			 m_instance;
	SceneManager*						 m_sceneManager = nullptr;
	Bitmap*								 m_mousecursor = nullptr;
	/*_DEBUG 용도*/
	ID2D1SolidColorBrush*				 m_whiteBrush;
	ID2D1SolidColorBrush*				 m_blackBrush;
	int									 m_mx;
	int									 m_my;
	IDWriteTextFormat*					 m_textFormat;
	/*          */
	UserDTO*							 m_userInfo;
public:
	MaplemonopolyApp();
	~MaplemonopolyApp();

	static  MaplemonopolyApp* GetInstance();
	virtual bool			  Init(HINSTANCE _instance, const WCHAR* _className, const WCHAR* _classTitle, int _nCmdShow) override;
	virtual	int				  Run() override;
	virtual LRESULT			  Dispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

public:
	void					  MouseMoveEvent(int _x, int _y);
	void					  MouseClickEnvet(int _x, int _y);
	void					  CharEvent(WPARAM _key);
	void					  Render();
	void					  MouseCursorRender();
	void					  DebugInit();
	void					  DebugRender();
	void					  DebugClean();
	void					  SetUserInfo(UserDTO* _userDTO);
	UserDTO*				  GetUserInfo();
};

