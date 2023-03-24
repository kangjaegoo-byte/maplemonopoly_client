#pragma once
class FPS
{
	const int MOVETICK = 20;

private:
	static FPS*				m_instance;
	int						m_sumTick = 0;
	int						m_currentTIck = 0;
	int						m_lastTick = 0;

	FPS();
	~FPS();

public:
	static FPS* GetInstance();
	bool OK();
	void DeleteInstance();
};

