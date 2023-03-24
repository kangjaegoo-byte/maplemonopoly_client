#pragma once
#include "GameObject.h"
class Dice : public GameObject
{
private:
	int m_dice1X;
	int m_dice1Y;
	int m_dice2X;
	int m_dice2Y;
	int m_dice1InitX;
	int m_dice1InitY;
	int m_dice2InitX;
	int m_dice2InitY;

	int m_dice1;
	int m_dice2;
	int m_sum;
	int m_playerIndex;
	int m_animation1Index = 0;
	int m_animation2Index = 0;
	class Bitamp* m_bitmap;
	class Animation* m_dice1Animation;
	Animation* m_dice2Animation;
	DiceState m_state = DICE_HOLD;
	int m_sumTick = 0;
	bool	 m_myTurn = false;
	CRITICAL_SECTION		m_diceLock;
	class DiceNumber* m_diceNumber;
public:
	Dice();
	Dice(int _x1, int _y1, int _x2, int _y2);
	~Dice();

	virtual void Init() override;
	virtual void Render() override;
	virtual void Update(int _tick) override;
	virtual void Clean() override;

	void		 Drop(DiceData* _diceData, bool _myTurn);
	void		 Hold(int _playerIndex);
	void         SetDiceResource(int _value, Animation** _ani);
};

