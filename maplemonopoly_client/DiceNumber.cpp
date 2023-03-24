#include "pch.h"
#include "DiceNumber.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Bitmap.h"

DiceNumber::DiceNumber(int _x, int _y) : GameObject(_x, _y)
{
	Init();
}

DiceNumber::~DiceNumber()
{
	ResourceManager::GetInstance()->DeleteSprite(GAME_ONE_DICE);
	ResourceManager::GetInstance()->DeleteSprite(GAME_TWO_DICE);
	ResourceManager::GetInstance()->DeleteSprite(GAME_THREE_DICE);
	ResourceManager::GetInstance()->DeleteSprite(GAME_FOUR_DICE);
	ResourceManager::GetInstance()->DeleteSprite(GAME_FIVE_DICE);
	ResourceManager::GetInstance()->DeleteSprite(GAME_SIX_DICE);
	ResourceManager::GetInstance()->DeleteSprite(GAME_SEVEN_DICE);
	ResourceManager::GetInstance()->DeleteSprite(GAME_EIGHT_DICE);
	ResourceManager::GetInstance()->DeleteSprite(GAME_NINE_DICE);
	ResourceManager::GetInstance()->DeleteSprite(GAME_TEN_DICE);
	ResourceManager::GetInstance()->DeleteSprite(GAME_ELEVEN_DICE);
	ResourceManager::GetInstance()->DeleteSprite(GAME_TWELVE_DICE);
	ResourceManager::GetInstance()->DeleteBitmap(GAME_DICE_BITMAP);
}

void DiceNumber::Init()
{

}

void DiceNumber::Render()
{
	if (m_number == 0)
		return;

	switch (m_number)
	{
	case 1:
		ResourceManager::GetInstance()->GetSprite(GAME_ONE_DICE)->Render(ResourceManager::GetInstance()->GetBitmap(DICE_NUMBER_BITMAP), { m_x + 0.0f,m_y + 0.0f });
		break;
	case 2:
		ResourceManager::GetInstance()->GetSprite(GAME_TWO_DICE)->Render(ResourceManager::GetInstance()->GetBitmap(DICE_NUMBER_BITMAP), { m_x + 0.0f,m_y + 0.0f });
		break;
	case 3:
		ResourceManager::GetInstance()->GetSprite(GAME_THREE_DICE)->Render(ResourceManager::GetInstance()->GetBitmap(DICE_NUMBER_BITMAP), { m_x + 0.0f,m_y + 0.0f });
		break;
	case 4:
		ResourceManager::GetInstance()->GetSprite(GAME_FOUR_DICE)->Render(ResourceManager::GetInstance()->GetBitmap(DICE_NUMBER_BITMAP), { m_x + 0.0f,m_y + 0.0f });
		break;
	case 5:
		ResourceManager::GetInstance()->GetSprite(GAME_FIVE_DICE)->Render(ResourceManager::GetInstance()->GetBitmap(DICE_NUMBER_BITMAP), { m_x + 0.0f,m_y + 0.0f });
		break;
	case 6:
		ResourceManager::GetInstance()->GetSprite(GAME_SIX_DICE)->Render(ResourceManager::GetInstance()->GetBitmap(DICE_NUMBER_BITMAP), { m_x + 0.0f,m_y + 0.0f });
		break;
	case 7:
		ResourceManager::GetInstance()->GetSprite(GAME_SEVEN_DICE)->Render(ResourceManager::GetInstance()->GetBitmap(DICE_NUMBER_BITMAP), { m_x + 0.0f,m_y + 0.0f });
		break;
	case 8:
		ResourceManager::GetInstance()->GetSprite(GAME_EIGHT_DICE)->Render(ResourceManager::GetInstance()->GetBitmap(DICE_NUMBER_BITMAP), { m_x + 0.0f,m_y + 0.0f });
		break;
	case 9:
		ResourceManager::GetInstance()->GetSprite(GAME_NINE_DICE)->Render(ResourceManager::GetInstance()->GetBitmap(DICE_NUMBER_BITMAP), { m_x + 0.0f,m_y + 0.0f });
		break;
	case 10:
		ResourceManager::GetInstance()->GetSprite(GAME_TEN_DICE)->Render(ResourceManager::GetInstance()->GetBitmap(DICE_NUMBER_BITMAP), { m_x + 0.0f,m_y + 0.0f });
		break;
	case 11:
		ResourceManager::GetInstance()->GetSprite(GAME_ELEVEN_DICE)->Render(ResourceManager::GetInstance()->GetBitmap(DICE_NUMBER_BITMAP), { m_x + 0.0f,m_y + 0.0f });
		break;
	case 12:
		ResourceManager::GetInstance()->GetSprite(GAME_TWELVE_DICE)->Render(ResourceManager::GetInstance()->GetBitmap(DICE_NUMBER_BITMAP), { m_x + 0.0f,m_y + 0.0f });
		break;
	}


}

void DiceNumber::Update(int _tick)
{
}

void DiceNumber::Clean()
{
}

void DiceNumber::SetData(int _data)
{
	m_number = _data;
}

void DiceNumber::InitData()
{
	m_number = 0;
}
