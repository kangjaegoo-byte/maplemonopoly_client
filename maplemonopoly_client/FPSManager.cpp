#include "pch.h"
#include "FPSManager.h"

FPSManager* FPSManager::m_instance = nullptr;

FPSManager::FPSManager()
{

}

FPSManager::~FPSManager()
{
}

FPSManager* FPSManager::GetInstance()
{
    if (m_instance == nullptr)
        m_instance = new FPSManager();

    return m_instance;
}

bool FPSManager::OK()
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

void FPSManager::DeleteInstance()
{
    delete m_instance;
}
