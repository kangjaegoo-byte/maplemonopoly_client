#include "pch.h"
#include "Dice.h"
#include "Bitmap.h"
#include "Sprite.h"
#include "Animation.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "DiceNumber.h"
Dice::Dice(int _x1, int _y1, int _x2, int _y2) : m_dice1X(_x1), m_dice1Y(_y1), m_dice2X(_x2), m_dice2Y(_y2), m_dice1InitX(_x1), m_dice1InitY(_y1), m_dice2InitX(_x2), m_dice2InitY(_y2)
{
	Init();
}

Dice::Dice() 
{
	Init();
}

Dice::~Dice()
{
	Clean();
}

void Dice::Init()
{
	InitializeCriticalSection(&m_diceLock);
	m_diceNumber = new DiceNumber(400, 300);
}

void Dice::Render()
{
	if (m_state == DICE_HOLD) return;

	EnterCriticalSection(&m_diceLock);
	m_dice1Animation->GetFrame(m_animation1Index)->Render(ResourceManager::GetInstance()->GetBitmap(GAME_DICE_BITMAP), D2D1_POINT_2F{ (FLOAT)m_dice1X,(FLOAT)m_dice1Y });
	m_dice2Animation->GetFrame(m_animation2Index)->Render(ResourceManager::GetInstance()->GetBitmap(GAME_DICE_BITMAP), D2D1_POINT_2F{ (FLOAT)m_dice2X,(FLOAT)m_dice2Y });
	m_diceNumber->Render();
	EnterCriticalSection(&m_diceLock);
}

void Dice::Update(int _tick)
{
	if (m_state == DICE_HOLD) return;

	if (m_state == DICE_RESULT)
	{
		if (m_myTurn)
		{
			char buffer[256];
			memcpy(buffer, &m_sum, sizeof(int));
			memcpy(buffer + sizeof(int), &m_playerIndex, sizeof(int));

			PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
			*(int*)(header + 1) = m_sum;
			*(int*)((int*)(header + 1) + 1) = m_playerIndex;
			header->id = PKT_S_DICEDROPEND;
			header->size = 12;
			Network::GetInstance()->Send(buffer, header->size);
			m_myTurn = false;
		}
	}
	else
	{
		const int passTick = 150;
		m_sumTick += _tick;

		if (m_sumTick >= passTick)
		{
			m_sumTick = 0;

			if (m_animation1Index + 1 < m_dice1Animation->GetFrameCount())
			{
				m_animation1Index += 1;
			}

			if (m_animation2Index + 1 < m_dice2Animation->GetFrameCount())
			{
				m_animation2Index += 1;
			}

			if (m_animation1Index == m_dice1Animation->GetFrameCount() - 1 && m_animation2Index == m_dice2Animation->GetFrameCount() - 1)
			{
				m_state = DICE_RESULT;

				switch (m_sum)
				{
				case 1:
					ResourceManager::GetInstance()->GetSound(ONE_SOUND)->Playing(false);
					break;
				case 2:
					ResourceManager::GetInstance()->GetSound(TWO_SOUND)->Playing(false);
					break;
				case 3:
					ResourceManager::GetInstance()->GetSound(THREE_SOUND)->Playing(false);
					break;
				case 4:
					ResourceManager::GetInstance()->GetSound(FOUR_SOUND)->Playing(false);
					break;
				case 5:
					ResourceManager::GetInstance()->GetSound(FIVE_SOUND)->Playing(false);
					break;
				case 6:
					ResourceManager::GetInstance()->GetSound(SIX_SOUND)->Playing(false);
					break;
				case 7:
					ResourceManager::GetInstance()->GetSound(SEVEN_SOUND)->Playing(false);
					break;
				case 8:
					ResourceManager::GetInstance()->GetSound(EIGHT_SOUND)->Playing(false);
					break;
				case 9:
					ResourceManager::GetInstance()->GetSound(NINE_SOUND)->Playing(false);
					break;
				case 10:
					ResourceManager::GetInstance()->GetSound(TEN_SOUND)->Playing(false);
					break;
				case 11:
					ResourceManager::GetInstance()->GetSound(ELEVEN_SOUND)->Playing(false);
					break;
				case 12:
					ResourceManager::GetInstance()->GetSound(TWELVE_SOUND)->Playing(false);
					break;
				}
			}

			switch (m_playerIndex)
			{
			case 0:
				m_dice1X += 77;
				m_dice1Y += 53;
				m_dice2X += 77;
				m_dice2Y += 53;
				break;

			case 1:
				m_dice1X -= 77;
				m_dice1Y += 53;
				m_dice2X -= 77;
				m_dice2Y += 53;
				break;

			case 2:
				m_dice1X += 77;
				m_dice1Y -= 53;
				m_dice2X += 77;
				m_dice2Y -= 53;
				break;

			case 3:
				m_dice1X -= 77;
				m_dice1Y -= 53;
				m_dice2X -= 77;
				m_dice2Y -= 53;
				break;
			}
		}
	}
}

void Dice::Clean()
{
	DeleteCriticalSection(&m_diceLock);
	delete m_diceNumber;
}

void Dice::Drop(DiceData* _diceData, bool _myTurn)
{
	m_dice1 = _diceData->_dice1;
	m_dice2 = _diceData->_dice2;
	m_sum = _diceData->_sum;
	m_playerIndex = _diceData->_playerIndex;
	SetDiceResource(m_dice1, &m_dice1Animation);
	SetDiceResource(m_dice2, &m_dice2Animation);
	m_diceNumber->SetData(m_sum);
	m_myTurn = _myTurn;
	m_state = DICE_DROP;
	ResourceManager::GetInstance()->GetSound(DICE_DROP_SOUND)->Playing(false);
}

void Dice::Hold(int _playerIndex)
{
	struct Pos 
	{
		int _x = 0;
		int _y = 0;
	};

	Pos startPos1 [4] = { {137,129},{686,120},{94, 513},{701,455} };
	Pos startPos2 [4] = { {79,153},{720,161},{148, 544},{663,485} };


	m_dice1X = startPos1[_playerIndex]._x;
	m_dice1Y = startPos1[_playerIndex]._y;
	m_dice2X = startPos2[_playerIndex]._x;
	m_dice2Y = startPos2[_playerIndex]._y;
	m_dice1 = 0;
	m_dice2 = 0;
	m_sum = 0;
	m_myTurn = false;
	m_state = DICE_HOLD;
	m_animation1Index = 0;
	m_animation2Index = 0;
	m_diceNumber->InitData();
}

void Dice::SetDiceResource(int _value, Animation** _ani)
{
	switch (_value)
	{
	case 1:
		*_ani = ResourceManager::GetInstance()->GetAnimation(GAME_DICE_ONE_ANIMATION);
		break;
	case 2:
		*_ani = ResourceManager::GetInstance()->GetAnimation(GAME_DICE_TWO_ANIMATION);
		break;
	case 3:
		*_ani = ResourceManager::GetInstance()->GetAnimation(GAME_DICE_THREE_ANIMATION);
		break;
	case 4:
		*_ani = ResourceManager::GetInstance()->GetAnimation(GAME_DICE_FOUR_ANIMATION);
		break;
	case 5:
		*_ani = ResourceManager::GetInstance()->GetAnimation(GAME_DICE_FIVE_ANIMATION);
		break;
	case 6:
		*_ani = ResourceManager::GetInstance()->GetAnimation(GAME_DICE_SIX_ANIMATION);
		break;
	}
}
