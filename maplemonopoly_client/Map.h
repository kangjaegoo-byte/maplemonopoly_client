#pragma once
class Map
{
private:
	std::vector<Region> m_maps;
	CRITICAL_SECTION	m_mapLock;
public:

	void Async(const Region& region);
	void Render();
	void DestoryUser(int _playerIdx);
	Map();
	~Map();
};

