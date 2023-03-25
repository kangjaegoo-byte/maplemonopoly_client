#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	const int PASSTICK = 100;
private:
	bool m_myPlayer = false;
	PlayerState m_state = PlayerState::IDLE;
	Pick m_pick;
	int	 m_money = 100;
	int	 m_pos = 0;
	int	 m_moveIndex = 0;
	int	 m_idelIndex = 0;
	int  m_sumTick = 0;
	class Animation* m_moveAnimation;
	Animation* m_idelAnimation;
	class Bitmap* m_bitmap;
	int	 m_destPos = 0;
public:
	Player(Pick _pick, int _money, int _pos, int _x, int _y);
	~Player();

	void SetMy() { m_myPlayer = true; }
	virtual void Init() override;
	virtual void Render() override;
	virtual void Update(int _tick) override;
	void Update(int _tick, int _playerIndex);
	virtual void Clean() override;
	void		 Move(const Region& region);
	void		 SetMoney(int _money);
	int			 GetMoney() { return m_money; };

};
