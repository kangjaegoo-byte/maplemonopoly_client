#pragma once
/**************************************************
	FPSManager : 프레임 관리 매니저
**************************************************/
class FPSManager
{
	const int MOVETICK = 20;

private:
	static FPSManager*		m_instance;
	int						m_sumTick = 0;
	int						m_currentTIck = 0;
	int						m_lastTick = 0;

	FPSManager();
	~FPSManager();

public:
	static FPSManager*		GetInstance();
	bool					OK();
	void					DeleteInstance();
};

