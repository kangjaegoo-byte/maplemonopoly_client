#include "pch.h"
#include "LobbyScene.h"
#include "ResourceManager.h"
#include "Bitmap.h"
#include "LobbyView.h"
#include "CRoomView.h"
#include "WRoomView.h"
LobbyScene::LobbyScene() : Scene(LOBBY_SCENE)
{
	Init();
}

LobbyScene::~LobbyScene()
{
	Clean();
}

void LobbyScene::Init()
{
	m_viewVector.resize(VIEW_COUNT, nullptr);
	m_crt = D2D1Core::GetInstance()->GetCRT();
	m_rt = D2D1Core::GetInstance()->GetRT();
	D2D1Core::GetInstance()->SetFontFormat(&m_textFormat, L"³ª´®°íµñ", 12);
	D2D1Core::GetInstance()->SetFontFormat(&m_boldTextAliginNormalForamt, L"³ª´®°íµñ", 14, DWRITE_TEXT_ALIGNMENT_CENTER);
	D2D1Core::GetInstance()->SetFontFormat(&m_staticTextAlignFormat, L"³ª´®°íµñ", 14, DWRITE_FONT_WEIGHT_BOLD, DWRITE_TEXT_ALIGNMENT_CENTER);
	D2D1Core::GetInstance()->CreateColorBrush(&m_blackBrush, D2D1::ColorF::Black);
	D2D1Core::GetInstance()->CreateColorBrush(&m_redBrush, D2D1::ColorF::Red);
	D2D1Core::GetInstance()->CreateColorBrush(&m_blueBrush, D2D1::ColorF::Blue);

	m_viewVector[LOBBY_VIEW] = new LobbyView(m_rt, m_crt, m_textFormat,m_boldTextAliginNormalForamt,m_blackBrush,m_blueBrush,m_redBrush);
	m_viewVector[CROOM_VIEW] = new CRoomView(m_rt, m_crt, m_textFormat, m_blackBrush);
	m_viewVector[WROOM_VIEW] = new WRoomView(m_rt, m_crt, m_textFormat, m_staticTextAlignFormat, m_blackBrush);
}

void LobbyScene::Update()
{
	m_viewVector[m_zindex]->Update();
}

void LobbyScene::Render()
{
	for (int i = 0; i <= m_zindex; i++)
		m_viewVector[i]->Render();
}

void LobbyScene::Clean()
{
	m_textFormat->Release();
	m_boldTextAliginNormalForamt->Release();
	m_blackBrush->Release();
	m_redBrush->Release();
	m_blueBrush->Release();
	m_staticTextAlignFormat->Release();
	ResourceManager::GetInstance()->Delete(LOBBY_BACKGROUND_BITMAP);
	ResourceManager::GetInstance()->Delete(LOBBY_CREATEROOMMODAL_BITMAP);
	ResourceManager::GetInstance()->Delete(WATING_ROOM_BACKGROUND_BITMAP);

	ResourceManager::GetInstance()->Delete(ORANGE_MURSHROOM_BITMAP);
	ResourceManager::GetInstance()->Delete(HORNY_MURSHROOM_BITMAP);
	ResourceManager::GetInstance()->Delete(PIG_BITMAP);


	ResourceManager::GetInstance()->DeleteAnimation(HORNY_MURSHROOM_IDLE_ANIMATION);
	ResourceManager::GetInstance()->DeleteAnimation(PIG_IDLE_ANIMATION);
	ResourceManager::GetInstance()->DeleteAnimation(ORANGE_MURSHROOM_IDLE_ANIMATION);

	for (int i = 0; i < VIEW_COUNT; i++)
		if (m_viewVector[i])
			delete m_viewVector[i];
}

void LobbyScene::MouseMoveEvent(int _x, int _y)
{
	m_viewVector[m_zindex]->MouseMoveEvent(_x, _y);
}

void LobbyScene::MouseClickEnvet(int _x, int _y)
{
	m_viewVector[m_zindex]->MouseClickEnvet(_x, _y);
}

void LobbyScene::CharEvent(WPARAM _key)
{
	m_viewVector[m_zindex]->CharEvent(_key);
}

void LobbyScene::RecvLobbyChatMsg(WCHAR* _text, int _size)
{
	if (m_viewVector[LOBBY_VIEW])
		static_cast<LobbyView*>(m_viewVector[LOBBY_VIEW])->RecvLobbyChatMsg(_text, _size);
}

void LobbyScene::LobbyUserListDataAsync(const std::vector<UserDTO>& _data)
{
	if (m_viewVector[LOBBY_VIEW])
		static_cast<LobbyView*>(m_viewVector[LOBBY_VIEW])->LobbyUserListDataAsync(_data);
}

void LobbyScene::LobbyRoomListDataAsync(const std::vector<RoomDTO>& _data)
{
	if (m_viewVector[LOBBY_VIEW])
		static_cast<LobbyView*>(m_viewVector[LOBBY_VIEW])->LobbyRoomListDataAsync(_data);
}

void LobbyScene::WatingRoomUserList(std::vector<UserDTO>& _data)
{
	if (m_zindex == WROOM_VIEW)
		static_cast<WRoomView*>(m_viewVector[WROOM_VIEW])->WatingRoomUserList(_data);
}

void LobbyScene::WatingRoomTitle(WCHAR* _buffer, int _dataCnt)
{
	if (m_zindex == WROOM_VIEW)
		static_cast<WRoomView*>(m_viewVector[WROOM_VIEW])->WatingRoomTitle(_buffer, _dataCnt);
}

void LobbyScene::MoveViewIndex(int _index)
{
	m_zindex = _index;
}

void LobbyScene::WatingRoomBoom()
{
	static_cast<WRoomView*>(m_viewVector[WROOM_VIEW])->WatingRoomBoom();
}

void LobbyScene::WRoomChatMsgRecv(WCHAR* _buffer, int _dataSize)
{
	if (m_zindex == WROOM_VIEW)
		static_cast<WRoomView*>(m_viewVector[WROOM_VIEW])->WRoomChatMsgRecv(_buffer, _dataSize);
}
