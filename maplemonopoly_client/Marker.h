#pragma once
#include "GameObject.h"
class Marker : public GameObject
{
private:
	int m_pos = 0;
	bool m_visiable = false;
public:
	Marker();
	~Marker();

	void SetPos(int _pos);
	void SetVisiable(bool _flag);

	virtual void Init() override;
	virtual void Render() override;
	virtual void Update(int _tick) override;
	virtual void Clean() override;
};

