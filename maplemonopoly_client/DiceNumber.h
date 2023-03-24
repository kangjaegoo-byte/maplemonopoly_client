#pragma once
#include "GameObject.h"
class DiceNumber : public GameObject
{
private:
	int m_number = 0;
	Bitmap* m_bitmap;

public:
	DiceNumber(int _x, int _y);
	~DiceNumber();

	virtual void Init() override;
	virtual void Render() override;
	virtual void Update(int _tick) override;
	virtual void Clean() override;
	void		 SetData(int _data);
	void		 InitData();
};

