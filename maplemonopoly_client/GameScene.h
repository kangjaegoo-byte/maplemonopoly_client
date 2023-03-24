#pragma once
#include "Scene.h"

class GameScene : public Scene
{
	enum : int
	{
		GAME_VIEW = 0,
		GAME_MODAL_VIEW = 1,
		GAME_END_VIEW = 2,
		GAME_VIEW_COUNT = 3,
	};
private:
	ID2D1HwndRenderTarget* m_rt;
	ID2D1BitmapRenderTarget* m_crt;
	IDWriteTextFormat* m_textFormat;
	ID2D1SolidColorBrush* m_blackBrush;
	ID2D1SolidColorBrush* m_colorBrush1;
	ID2D1SolidColorBrush* m_colorBrush2;
	std::vector<class UIComponent*>	m_uiVector;
	std::vector<class View*>			m_viewVector;
	int							m_zindex = 0;
	int	m_playerIndex;
public:
	GameScene();
	~GameScene();

	virtual void	Init()		override;
	virtual void	Update(int _deltaTick)	override;
	virtual void	Render()	override;
	virtual void	Clean()		override;

	virtual void	MouseMoveEvent(int _x, int _y) override;
	virtual void	MouseClickUpEnvet(int _x, int _y) override;
	virtual void	MouseClickEvent(int _x, int _y) override;
	virtual void	CharEvent(WPARAM _key) override;
	virtual SceneChangeData	Change()	override;

	void GameUserNumber(int _dataPtr);
	void GameUserAsync(std::vector<class User>& _data);
	void TurnSend(int _playerIdx);
	void DiceDropResult(DiceData* _diceData);
};

