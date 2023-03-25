#include "pch.h"
#include "Map.h"
#include "ResourceManager.h"
#include "D2D1Core.h"
#include "Bitmap.h"
#include "Sprite.h"
#include "ClientMap.h"
void Map::Async(const Region& region)
{
	EnterCriticalSection(&m_mapLock);
	int index = region._mapIndex;
	m_maps[index] = region;
	LeaveCriticalSection(&m_mapLock);
}

void Map::Render()
{
	EnterCriticalSection(&m_mapLock);
	for (int i = 0; i < 32; i++)
	{
		Region r = m_maps[i];
		int playerIdx = r._ownerPlayerIndx;
		Bitmap* b = ResourceManager::GetInstance()->GetBitmap(GAME_MONO_BITMAP);
		Sprite* s = nullptr;
		if (r._level == 1)
		{
			s = ResourceManager::GetInstance()->GetPlayerHouse(playerIdx);
		}
		else if (r._level == 2)
		{
			s = ResourceManager::GetInstance()->GetPlayerHotel(playerIdx);
		}

		if (s)
		{
			ClientMapData d = ClientMap::GetInstance()->GetPos(r._mapIndex);
			s->SetPivot({ (FLOAT)d._mxPos, (FLOAT)d._myPos });
			s->Render(b, 30, 40);
		}

	}
	LeaveCriticalSection(&m_mapLock);
}

void Map::DestoryUser(int _playerIdx)
{
	EnterCriticalSection(&m_mapLock);
	for (int i = 0; i < 32; i++)
	{
		if (m_maps[i]._ownerPlayerIndx == _playerIdx)
		{
			m_maps[i]._level = 0;
			m_maps[i]._passCost = m_maps[i]._oriCost;
			m_maps[i]._ownerPlayerIndx = -1;
		}
	}
	LeaveCriticalSection(&m_mapLock);
}

Map::Map()
{
	InitializeCriticalSection(&m_mapLock);
	m_maps.resize(32);
}

Map::~Map()
{
	DeleteCriticalSection(&m_mapLock);
}
