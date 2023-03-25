#pragma once
#include "GameObject.h"
class Money : public GameObject
{
	// Player1 (120,120)
	// Player2 (720,130)
	// Player3 (110,480)
	// Player4 (700,480

	const int PASSTICK = 50;

	struct Pos
	{
		int _x;
		int _y;
	};

	enum State
	{
		IDLE,
		MOVE
	};

	enum MoneyMoveState
	{
		FROM_POS,
		CENTER_POS,
		OTHER_POS
	};

private:
	int m_x;
	int m_y;
	int m_from;
	int m_to;
	int m_sumTick = 0;
	Pos m_playerPos[4] = { {120,120}, {720,130}, {110,480}, {672, 515} };
	Pos m_next;
	Pos m_now;
	Pos m_center = { 400, 300 };
	State m_state;
	MoneyMoveState m_moveState;
	Pos m_centerMovePos[4] = { {40,30},{-40,30},{40,-30},{-40,-30} };
	Pos m_nextMovePos[4] = { {-40,-30},{40,-30},{-40,30},{40,30} };
	Pos m_movePos;

public:
	Money();
	~Money();

	void MoneyPassCost(int _from, int _to);
	void GameOtherBuyResponse(int _from, int _to);
	void GameBuyRegionModalProcessResponse(int _from);


	virtual void Init() override;
	virtual void Render() override;
	virtual void Update(int _tick) override;
	virtual void Update(int _tick, class AlertText* _text);
	virtual void Clean() override;
};

