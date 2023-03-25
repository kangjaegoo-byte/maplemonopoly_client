#include "pch.h"
#include "Money.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Bitmap.h"
#include "AlertText.h"
Money::Money()
{
	Init();
}

Money::~Money()
{
	Clean();
}

void Money::MoneyPassCost(int _from, int _to)
{
	m_from = _from;
	m_to = _to;

	m_now = m_playerPos[_from];
	m_next = m_playerPos[_to];
	m_state = State::MOVE;
	m_movePos = m_centerMovePos[_from];
	m_moveState = MoneyMoveState::FROM_POS;
}

void Money::GameOtherBuyResponse(int _from, int _to)
{
	m_from = _from;
	m_to = _to;

	m_now = m_playerPos[_from];
	m_next = m_playerPos[_to];
	m_state = State::MOVE;
	m_movePos = m_centerMovePos[_from];
	m_moveState = MoneyMoveState::FROM_POS;
}

void Money::GameBuyRegionModalProcessResponse(int _from)
{
	m_from = _from;
	m_to = _from;

	m_now = m_playerPos[_from];
	m_next = m_center;
	m_state = State::MOVE;
	m_movePos = m_centerMovePos[_from];
	m_moveState = MoneyMoveState::FROM_POS;
}

void Money::Init()
{
	m_state = State::IDLE;
	m_moveState = MoneyMoveState::FROM_POS;
}

void Money::Render()
{
	if (m_state != MOVE)
		return;

	D2D1_RECT_F f = { m_now._x - 50.0f , m_now._y - 50.0f, m_now._x + 50.0f, m_now._y };
	D2D1Core::GetInstance()->GetCRT()->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(GAME_MONEY_BITMAP)->GetBitmap(), f, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);

}

void Money::Update(int _tick)
{

	if (m_state != MOVE)
		return;

	m_sumTick += _tick;

	if (m_sumTick < PASSTICK) return;

	m_sumTick = 0;

	switch (m_moveState)
	{
	case FROM_POS:
	{
		if (m_now._x == m_center._x && m_now._y == m_center._y)
		{
			m_moveState = CENTER_POS;
			m_movePos = m_nextMovePos[m_to];
			break;
		}

		int nextX = m_now._x + m_movePos._x;
		int nextY = m_now._y + m_movePos._y;

		switch (m_from)
		{
		case 0:
			if (nextX >= m_center._x)
				nextX = m_center._x;

			if (nextY >= m_center._y)
				nextY = m_center._y;
			break;

		case 1:
			if (nextX <= m_center._x)
				nextX = m_center._x;

			if (nextY >= m_center._y)
				nextY = m_center._y;
			break;

		case 2:
			if (nextX >= m_center._x)
				nextX = m_center._x;

			if (nextY <= m_center._y)
				nextY = m_center._y;
			break;

		case 3:
			if (nextX <= m_center._x)
				nextX = m_center._x;

			if (nextY <= m_center._y)
				nextY = m_center._y;
			break;
		}

		m_now = { nextX, nextY };
	}
	break;

	case CENTER_POS:
	{
		if (m_now._x == m_next._x && m_now._y == m_next._y)
		{
			m_moveState = OTHER_POS;
			break;
		}

		int nextX = m_now._x + m_movePos._x;
		int nextY = m_now._y + m_movePos._y;

		switch (m_to)
		{
		case 0:
			if (nextX <= m_next._x)
				nextX = m_next._x;

			if (nextY <= m_next._y)
				nextY = m_next._y;
			break;

		case 1:
			if (nextX >= m_next._x)
				nextX = m_next._x;

			if (nextY <= m_next._y)
				nextY = m_next._y;
			break;

		case 2:
			if (nextX <= m_next._x)
				nextX = m_next._x;

			if (nextY >= m_next._y)
				nextY = m_next._y;
			break;

		case 3:
			if (nextX >= m_next._x)
				nextX = m_next._x;

			if (nextY >= m_next._y)
				nextY = m_next._y;
			break;
		}
		m_now = { nextX, nextY };

	}
	break;

	case OTHER_POS:
		m_state = IDLE;
		break;
	}
}

void Money::Update(int _tick, AlertText* _text)
{
	if (m_state != MOVE)
		return;

	m_sumTick += _tick;

	if (m_sumTick < PASSTICK) return;

	m_sumTick = 0;

	switch (m_moveState)
	{
	case FROM_POS:
	{
		if (m_now._x == m_center._x && m_now._y == m_center._y)
		{
			m_moveState = CENTER_POS;
			m_movePos = m_nextMovePos[m_to];
			break;
		}

		int nextX = m_now._x + m_movePos._x;
		int nextY = m_now._y + m_movePos._y;

		switch (m_from)
		{
		case 0:
			if (nextX >= m_center._x)
				nextX = m_center._x;

			if (nextY >= m_center._y)
				nextY = m_center._y;
			break;

		case 1:
			if (nextX <= m_center._x)
				nextX = m_center._x;

			if (nextY >= m_center._y)
				nextY = m_center._y;
			break;

		case 2:
			if (nextX >= m_center._x)
				nextX = m_center._x;

			if (nextY <= m_center._y)
				nextY = m_center._y;
			break;

		case 3:
			if (nextX <= m_center._x)
				nextX = m_center._x;

			if (nextY <= m_center._y)
				nextY = m_center._y;
			break;
		}

		m_now = { nextX, nextY };
	}
	break;

	case CENTER_POS:
	{
		if (m_now._x == m_next._x && m_now._y == m_next._y)
		{
			m_moveState = OTHER_POS;
			break;
		}

		int nextX = m_now._x + m_movePos._x;
		int nextY = m_now._y + m_movePos._y;

		switch (m_to)
		{
		case 0:
			if (nextX <= m_next._x)
				nextX = m_next._x;

			if (nextY <= m_next._y)
				nextY = m_next._y;
			break;

		case 1:
			if (nextX >= m_next._x)
				nextX = m_next._x;

			if (nextY <= m_next._y)
				nextY = m_next._y;
			break;

		case 2:
			if (nextX <= m_next._x)
				nextX = m_next._x;

			if (nextY >= m_next._y)
				nextY = m_next._y;
			break;

		case 3:
			if (nextX >= m_next._x)
				nextX = m_next._x;

			if (nextY >= m_next._y)
				nextY = m_next._y;
			break;
		}
		m_now = { nextX, nextY };

	}
	break;

	case OTHER_POS:
		m_state = IDLE;
		_text->SetMoney(0);
		break;
	}
}

void Money::Clean()
{

}
