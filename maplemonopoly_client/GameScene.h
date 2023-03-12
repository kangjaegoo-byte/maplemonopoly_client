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

		GAMEUSER1_USERPICK = 4,
		GAMEUSER2_USERPICK = 5,
		GAMEUSER3_USERPICK = 6,
		GAMEUSER4_USERPICK = 7,
		GAME_EXIT_BTN = 8,
		GAME_UI_COUNT = 9
	};
private:
	ID2D1HwndRenderTarget*		m_rt;
	ID2D1BitmapRenderTarget*	m_crt;
	IDWriteTextFormat*			m_textFormat;
	ID2D1SolidColorBrush*		m_blackBrush;
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
	void			GameExit(std::vector<UserDTO>& dto);
};

