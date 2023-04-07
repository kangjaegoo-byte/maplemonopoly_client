#include "pch.h"
#include "Player.h"
#include "Animation.h"
#include "ClientMap.h"
#include "Sprite.h"
Player::Player(Pick _pick, int _money, int _pos, int _x, int _y) : GameObject(_x, _y), m_pick(_pick), m_money(_money), m_pos(_pos)
{
	Init();
}

Player::~Player()
{
	Clean();
}

void Player::Init()
{
	switch (m_pick)
	{
	case HORN_MURSHROOM:
		m_moveAnimation = ResourceManager::GetInstance()->GetAnimation(HORN_MURSHROOM_MOVE_ANIMATION);
		m_idelAnimation = ResourceManager::GetInstance()->GetAnimation(HORN_MURSHROOM_IDLE_ANIMATION);
		m_bitmap = ResourceManager::GetInstance()->GetBitmap(HORN_MURSHROOM_BITMAP);
		break;
	case ORANGE_MURSHROOM:
		m_moveAnimation = ResourceManager::GetInstance()->GetAnimation(ORANGE_MURSHROOM_MOVE_ANIMATION);
		m_idelAnimation = ResourceManager::GetInstance()->GetAnimation(ORANGE_MURSHROOM_IDLE_ANIMATION);
		m_bitmap = ResourceManager::GetInstance()->GetBitmap(ORANGE_MURSHROOM_BITMAP);
		break;
	case PIG:
		m_moveAnimation = ResourceManager::GetInstance()->GetAnimation(PIG_MOVE_ANIMATION);
		m_idelAnimation = ResourceManager::GetInstance()->GetAnimation(PIG_IDLE_ANIMATION);
		m_bitmap = ResourceManager::GetInstance()->GetBitmap(PIG_BITMAP);
		break;
	}
}

void Player::Render()
{
	ClientMapData data = ClientMap::GetInstance()->GetPos(m_pos);
	switch (m_state)
	{
	case IDLE:
		m_idelAnimation->GetFrame(m_idelIndex)->Render(m_bitmap, D2D1_POINT_2F{ data._xPos + 0.0f,data._yPos + 0.0f }, data._rotate);
		break;

	case MOVE:
		m_moveAnimation->GetFrame(m_moveIndex)->Render(m_bitmap, D2D1_POINT_2F{ data._xPos + 0.0f,data._yPos + 0.0f }, data._rotate);
		break;
	}
}

void Player::Update(int _tick)
{

}

void Player::Update(int _tick, int _playerIndex)
{
	m_sumTick += _tick;
	if (m_sumTick < PASSTICK) return;

	m_sumTick = 0;

	switch (m_state)
	{
	case IDLE:
		m_idelIndex = (m_idelIndex + 1) % m_idelAnimation->GetFrameCount();
		break;

	case MOVE:
		m_moveIndex = (m_moveIndex + 1) % m_moveAnimation->GetFrameCount();
		break;
	}


	switch (m_state)
	{
	case IDLE:
		break;

	case MOVE:
		if (m_destPos != m_pos)
		{
			m_pos = (m_pos + 1) % 32;
		}
		else
		{
			m_state = IDLE;
			if (m_myPlayer)
			{
				// 1) 유저가 해당 지역에 도착했다고 서버에 알려준다.
				char buffer[256];
				PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
				*(int*)(header + 1) = _playerIndex;
				header->size = 8;
				header->id = PKT_S_PLAYERMOVEEND;
				Network::GetInstance()->Send(buffer,header->size);
			}
		}
		break;
	}
}

void Player::Clean()
{
}

void Player::Move(const Region& region)
{
	m_state = MOVE;
	m_destPos = region._mapIndex;
}

void Player::SetMoney(int _money)
{
	m_money = _money;
}
