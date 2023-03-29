#include "pch.h"
#include "ClientMap.h"

ClientMap* ClientMap::m_instance = nullptr;

ClientMap* ClientMap::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new ClientMap();

	return m_instance;
}

ClientMap::ClientMap()
{
	const int MapDataCount = 32;
	m_maps.resize(32);
	m_maps[0] = ClientMapData{ 405 ,522,false,0,0 };		// 출발점
	m_maps[1] = ClientMapData{ 336 ,497,false,371,465 };	// 모텔
	m_maps[2] = ClientMapData{ 298 ,471,false,0,0 };		// 카드 뽑기
	m_maps[3] = ClientMapData{ 265 ,445,false,296,418 };	// 주유소
	m_maps[4] = ClientMapData{ 232 ,414,false,0,0 };		// 화학마크
	m_maps[5] = ClientMapData{ 195 ,393,false,229,364 };	// 마트
	m_maps[6] = ClientMapData{ 159 ,366,false,192,339 };	// 교도소
	m_maps[7] = ClientMapData{ 124 ,340,false,162,311 };	// 수력발전소
	m_maps[8] = ClientMapData{ 90 ,294,true,0,0 };			// 대피소	180 오른쪽방향 회전
	m_maps[9] = ClientMapData{ 170 ,274,true,0,0 };			// 카드
	m_maps[10] = ClientMapData{ 208 ,249,true,172,220 };	// 패스푸드점
	m_maps[11] = ClientMapData{ 244 ,221,true,207,196 };	// 영화관
	m_maps[12] = ClientMapData{ 277 ,196,true,0,0 };		// 화학마크
	m_maps[13] = ClientMapData{ 312 ,170,true,276,143, };	// 병원
	m_maps[14] = ClientMapData{ 349 ,146,true,0,0 };		// 화력발전소
	m_maps[15] = ClientMapData{ 383 ,110,true,348,92 };		// 경찰서 
	m_maps[16] = ClientMapData{ 401 ,51,true,0,0 };			// 공동묘지
	m_maps[17] = ClientMapData{ 424 ,119,true,455,89 };		// 교회
	m_maps[18] = ClientMapData{ 455 ,145,true,0,0 };		// 카드
	m_maps[19] = ClientMapData{ 492 ,171,true,525,145 };		// 백화점
	m_maps[20] = ClientMapData{ 521 ,195,true,0,0 };		// 화학마크
	m_maps[21] = ClientMapData{ 558 ,222,true,594,195 };	// 방송국
	m_maps[22] = ClientMapData{ 593 ,248,true,629,221 };		// 공항
	m_maps[23] = ClientMapData{ 630 ,274,true,667,248 };			// 풍력발전소

	m_maps[24] = ClientMapData{ 709 ,288,false,0,0 };		// 좀비레이스 180 왼쪽방향으로 회전
	m_maps[25] = ClientMapData{ 674 ,340,false,637,310 };	// 호텔
	m_maps[26] = ClientMapData{ 640 ,364,false,593,338 };		// 카드
	m_maps[27] = ClientMapData{ 602 ,391,false,570,362 };	// 카지노
	m_maps[28] = ClientMapData{ 561 ,421,false,0,0 }; // 화학마크
	m_maps[29] = ClientMapData{ 534 ,444,false,495,413 }; // 군사기지
	m_maps[30] = ClientMapData{ 499 ,469,false,0,0 }; // 태양광발전소
	m_maps[31] = ClientMapData{ 465 ,498,false,427,469 }; // 시청
}

ClientMapData ClientMap::GetPos(int _pos)
{
	return m_maps[_pos];
}

ClientMap::~ClientMap()
{

}
