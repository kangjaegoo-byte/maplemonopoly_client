#pragma once
#include "Scene.h"
class UserDTO;
class UIComponent;
/**************************************************
	GameScene : ∞‘¿”æ¿
**************************************************/
class GameScene : public Scene
{
	enum : int
	{
		GAMEUSER1_NAME = 0,
		GAMEUSER2_NAME = 1,
		GAMEUSER3_NAME = 2,
		GAMEUSER4_NAME = 3,

		GAMEUSER1 = 4,
		GAMEUSER2 = 5,
		GAMEUSER3 = 6,
		GAMEUSER4 = 7,
		GAME_EXIT_BTN = 8,
		GAME_UI_COUNT = 9
	};
private:
	ID2D1HwndRenderTarget*		m_rt;
	ID2D1BitmapRenderTarget*	m_crt;
	IDWriteTextFormat*			m_textFormat;
	ID2D1SolidColorBrush*		m_blackBrush;
	ID2D1SolidColorBrush*		m_colorBrush1;
	ID2D1SolidColorBrush*		m_colorBrush2;
	bool						m_start = false;
	bool						m_end = false;
	std::vector<UIComponent*>	m_uiVector;

public:
	GameScene();
	virtual ~GameScene();

	virtual void	Init()		override;
	virtual void	Update()	override;
	virtual void	Render()	override;
	virtual void	Clean()		override;

	virtual void	MouseMoveEvent(int _x, int _y) override;
	virtual void	MouseClickEnvet(int _x, int _y) override;
	virtual void	CharEvent(WPARAM _key) override;

	void			GamePlay(std::vector<UserDTO>& dto);
	void			GameExit(int _exitGameUserIndex);
};

