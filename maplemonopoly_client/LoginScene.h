#pragma once
#include "Scene.h"
class UIComponent;
class Sound;
/**************************************************
	LoginScene : ·Î±×ÀÎ ¾À
**************************************************/
class LoginScene : public Scene
{
	enum : int 
	{
		LOGIN_INPUT = 0,
		LOGIN_BUTTON = 1,
		LOGIN_ALERTMODAL = 2,
		LOGIN_UI_COUNT = 3,
	};
private:
	ID2D1HwndRenderTarget*		m_rt;
	ID2D1BitmapRenderTarget*	m_crt;
	IDWriteTextFormat*			m_textFormat;
	ID2D1SolidColorBrush*		m_whiteBrush;
	Sound*						m_bgm;
	std::vector<UIComponent*>	m_uiVector;
public:
	LoginScene();
	~LoginScene();

	virtual void	Init()		override;
	virtual void	Update()	override;
	virtual void	Render()	override;
	virtual void	Clean()		override;

	virtual void	MouseMoveEvent(int _x, int _y) override;
	virtual void	MouseClickEnvet(int _x, int _y) override;
	virtual void	CharEvent(WPARAM _key) override;
};

