#pragma once
#include "View.h"
class GameView : public View
{
	enum : int
	{
		GAMEVIEW_GAMEUSER1 = 0,
		GAMEVIEW_GAMEUSER2 = 1,
		GAMEVIEW_GAMEUSER3 = 2,
		GAMEVIEW_GAMEUSER4 = 3,
		GAMEVIEW_GAMEDICEBTN = 4,
		GAMEVIEW_GAME_UI_COUNT = 5
	};

private:
	ID2D1HwndRenderTarget* m_rt;
	ID2D1BitmapRenderTarget* m_crt;
	IDWriteTextFormat* m_textFormat;
	ID2D1SolidColorBrush* m_blackBrush;
	ID2D1SolidColorBrush* m_colorBrush1;
	ID2D1SolidColorBrush* m_colorBrush2;
	std::vector<class UIComponent*>  m_uiVector;
	class Dice* m_dice;
	int m_playerIndex;
	class Player* m_players [4] = {nullptr, nullptr, nullptr ,nullptr};
	bool m_myTurn = false;
	class AlertText* m_alertText;
	class Money* m_money;
	class Map* m_map = nullptr;
	CRITICAL_SECTION				m_gameLock;
	bool m_change = false;
	bool m_viewChange = false;
	class Marker* m_marker;
public:
	GameView(ID2D1HwndRenderTarget* _rt, ID2D1BitmapRenderTarget* _crt, IDWriteTextFormat* _textFormat, ID2D1SolidColorBrush* _black, ID2D1SolidColorBrush* _color1, ID2D1SolidColorBrush* _color2);
	~GameView();

	virtual void	Init()		override;
	virtual void	Update(int _deltaTick)	override;
	virtual void	Render()	override;
	virtual void	Clean()		override;


	virtual void	MouseMoveEvent(int _x, int _y) override;
	virtual void	MouseClickEvent(int _x, int _y) override;
	virtual void	MouseClickUpEnvet(int _x, int _y) override;
	virtual void	CharEvent(WPARAM _key) override;
	virtual ViewType ChangeView() override;
	void GameUserNumber(int _dataPtr);
	void GameUserAsync(std::vector<class User>& _data);
	void TurnSend(int _playerIdx);
	void DiceDropResult(DiceData* _diceData);
	void PlayerMove(char* _data);
	void GameEnd(int _data);
	void PlayerDisconnect(int _playerIndex);
	void UpdateRank();
	void					GameBuyRegionModalProcessResponse(char* _dataPtr);
	void					MoneyPassCost(char* _dataPtr);
	void					GameOtherBuyResponse(char* _dataPtr);
	void					PlayerDead(char* _data);
	bool					GameEnd();
	void GameUserAsync(char* _buffer);

};

