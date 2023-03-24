#pragma once
class ClientMap
{
private:
	static ClientMap* m_instance;
	std::vector<ClientMapData> m_maps;
public:

	static ClientMap* GetInstance();
	ClientMapData GetPos(int _pos);
	ClientMap();
	~ClientMap();
};

