#pragma once
#include "Scene.h"
class LoginScene : public Scene
{
	const int PassTick = 20;
	enum : int
	{
		LOGIN_INPUT = 0,
		LOGIN_BUTTON = 1,
		LOGIN_ALERTMODAL = 2,
		LOGIN_UI_COUNT = 3,
	};
private:
	ID2D1HwndRenderTarget* m_rt;
	ID2D1BitmapRenderTarget* m_crt;
	IDWriteTextFormat* m_textFormat;
	ID2D1SolidColorBrush* m_whiteBrush;
	class Sound* m_bgm = nullptr;
	std::vector<class UIComponent*>	m_uiVector;
	bool m_change = false;

public:
	LoginScene();
	~LoginScene();

	virtual void	Init()		override;
	virtual void	Update(int _deltaTick)	override;
	virtual void	Render()	override;
	virtual void	Clean()		override;

	virtual void	MouseMoveEvent(int _x, int _y) override;
	virtual void	MouseClickEvent(int _x, int _y) override;
	virtual void	MouseClickUpEnvet(int _x, int _y) override;

	virtual void	CharEvent(WPARAM _key) override;
	virtual SceneChangeData	Change()	override;
};

