#include "pch.h"
#include "FPS.h"
FPS* FPS::m_instance = nullptr;

FPS::FPS()
{
}

FPS::~FPS()
{
}

FPS* FPS::GetInstance()
{
    if (m_instance == nullptr)
        m_instance = new FPS();

    return m_instance;
}

bool FPS::OK()
{
    m_lastTick = m_currentTIck;
    m_currentTIck = GetTickCount64();
    m_sumTick += m_currentTIck - m_lastTick;

    if (m_sumTick >= MOVETICK)
    {
        m_sumTick = 0;
        return true;
    }
    else
    {
        return false;
    }
}

void FPS::DeleteInstance()
{
    delete m_instance;
}
