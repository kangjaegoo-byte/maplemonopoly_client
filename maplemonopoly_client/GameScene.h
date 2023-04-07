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
	bool m_change = false;
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
	void GameUserAsync(char* _buffer);
	void TurnSend(int _playerIdx);
	void DiceDropResult(DiceData* _diceData);
	void PlayerMove(char* _data);
	void GameBuyRegion(Region* dataPtr);

	void PlayerDead(char* _data);
	void					GameBuyRegionModalProcessResponse(char* _dataPtr);
	void					MoneyPassCost(char* _dataPtr);
	void					GameBuyRegionModalOtherProcessResponseEx(char* _dataPtr);
	void					GameOtherBuyResponse(char* _dataPtr);
	void GameEnd(int _data);
	void PlayerDisconnect(int _data);

};

