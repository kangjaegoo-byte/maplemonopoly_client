#include "pch.h"
#include "LobbyScene.h"
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

	m_viewVector[LOBBY_VIEW] = new LobbyView(m_rt, m_crt, m_textFormat, m_boldTextAliginNormalForamt, m_blackBrush, m_blueBrush, m_redBrush);
	m_viewVector[CROOM_VIEW] = new CRoomView(m_rt, m_crt, m_textFormat, m_blackBrush);
	m_viewVector[WROOM_VIEW] = new WRoomView(m_rt, m_crt, m_textFormat, m_staticTextAlignFormat, m_blackBrush);
}

void LobbyScene::Update(int _deltaTick)
{
	ViewType viewChange = m_viewVector[m_zindex]->ChangeView();

	if (viewChange == ViewType::VIEW_NONE)
	{
		m_viewVector[m_zindex]->Update(_deltaTick);
	}
	else
	{
		m_zindex = viewChange;
	}
}

void LobbyScene::Render()
{
	for (int i = 0; i <= m_zindex; i++)
		m_viewVector[i]->Render();
}

void LobbyScene::Clean()
{
	for (int i = 0; i < VIEW_COUNT; i++)
		m_viewVector[i]->Clean();
}
	
void LobbyScene::MouseMoveEvent(int _x, int _y)
{
	m_viewVector[m_zindex]->MouseMoveEvent(_x, _y);
}

void LobbyScene::MouseClickEvent(int _x, int _y)
{
	m_viewVector[m_zindex]->MouseClickEvent(_x, _y);
}

void LobbyScene::MouseClickUpEnvet(int _x, int _y)
{
}

void LobbyScene::CharEvent(WPARAM _key)
{
	m_viewVector[m_zindex]->CharEvent(_key);
}

SceneChangeData LobbyScene::Change()
{
	if (m_change == false)
		return SceneChangeData{ false, SceneType::NONE };
	else
	{
		m_change = false;
		return SceneChangeData{ false, SceneType::GAME_SCENE };
	}
}

void LobbyScene::LobbyUserListDataAsync(const std::vector<User>& _data)
{
	if (m_viewVector[LOBBY_VIEW])
		static_cast<LobbyView*>(m_viewVector[LOBBY_VIEW])->LobbyUserListDataAsync(_data);
}

void LobbyScene::LobbyRoomListDataAsync(const std::vector<class Room>& _data)
{
	if (m_viewVector[LOBBY_VIEW])
		static_cast<LobbyView*>(m_viewVector[LOBBY_VIEW])->LobbyRoomListDataAsync(_data);
}

void LobbyScene::LobbyChatMsgRecv(WCHAR* _text, int _size)
{
	if (m_viewVector[LOBBY_VIEW])
		static_cast<LobbyView*>(m_viewVector[LOBBY_VIEW])->LobbyChatMsgRecv(_text, _size);
}

void LobbyScene::LobbyUsernameAsync(WCHAR* _text, int _size)
{
	if (m_viewVector[LOBBY_VIEW])
		static_cast<LobbyView*>(m_viewVector[LOBBY_VIEW])->LobbyUsernameAsync(_text, _size);
}

void LobbyScene::WRoomUserListAsync(std::vector<class User>& _data)
{
	if (m_viewVector[WROOM_VIEW])
		static_cast<WRoomView*>(m_viewVector[WROOM_VIEW])->WRoomUserListAsync(_data);
}

void LobbyScene::WRoomTitleAsync(WCHAR* _text, int _size)
{
	if (m_viewVector[WROOM_VIEW])
		static_cast<WRoomView*>(m_viewVector[WROOM_VIEW])->WRoomTitleAsync(_text, _size);
}

void LobbyScene::WRoomChat(WCHAR* _text, int _size)
{
	if (m_viewVector[WROOM_VIEW])
		static_cast<WRoomView*>(m_viewVector[WROOM_VIEW])->WRoomChatMsgRecv(_text, _size);
}
