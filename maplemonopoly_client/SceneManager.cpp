#include "pch.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "LoadingScene.h"
#include "LoginScene.h"
#include "LobbyScene.h"
#include "UserDTO.h"
#include "MaplemonopolyApp.h"
#include "RoomDTO.h"
SceneManager* SceneManager::m_instance = nullptr;

SceneManager* SceneManager::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new SceneManager();

	return m_instance;
}

void SceneManager::DeleteInstance()
{
    DeleteCriticalSection(&m_sceneDeleteRequireLock);
	delete m_instance;
}

void SceneManager::Init()
{
    InitializeCriticalSection(&m_sceneDeleteRequireLock);
	m_sceneVector.resize(Scenetype::SCENE_COUNT, nullptr);
}

void SceneManager::Update()
{
    if (m_sceneVector[m_nowscene] == nullptr)
        return;
    EnterCriticalSection(&m_sceneDeleteRequireLock);
    m_sceneVector[m_nowscene]->Update();
    m_sceneVector[m_nowscene]->Render();
    LeaveCriticalSection(&m_sceneDeleteRequireLock);
}

void SceneManager::MouseMoveEvent(int _x, int _y)
{
    if (m_sceneVector[m_nowscene] == nullptr)
        return;
    EnterCriticalSection(&m_sceneDeleteRequireLock);
    m_sceneVector[m_nowscene]->MouseMoveEvent(_x, _y);
    LeaveCriticalSection(&m_sceneDeleteRequireLock);
}

void SceneManager::MouseClickEnvet(int _x, int _y)
{
    if (m_sceneVector[m_nowscene] == nullptr)
        return;
    EnterCriticalSection(&m_sceneDeleteRequireLock);
    m_sceneVector[m_nowscene]->MouseClickEnvet(_x, _y);
    LeaveCriticalSection(&m_sceneDeleteRequireLock);
}

void SceneManager::CharEvent(WPARAM _key)
{
    if (m_sceneVector[m_nowscene] == nullptr)
        return;
    EnterCriticalSection(&m_sceneDeleteRequireLock);
    m_sceneVector[m_nowscene]->CharEvent(_key);
    LeaveCriticalSection(&m_sceneDeleteRequireLock);
}

void SceneManager::Recv(char* _buffer)
{
    WORD* size = (WORD*)_buffer;
    int dataSize = *size - PACKET_HEADER_SIZE;
    size++;

    WORD* cnt = (WORD*)size;
    int dataCnt = *cnt;
    cnt++;

    WORD* type = (WORD*)cnt;
    int controllerType = *type;
    type++;

    char* dataPtr = (char*)type;


    switch (controllerType)
    {
    case CLIENT_LOADING_RESPONSE:
        LoadingPage(static_cast<Scenetype>(* dataPtr));
        break;

    case CLIENT_NEXTSCENE_RESPONSE:
        SceneChange(static_cast<Scenetype>(*dataPtr));
        break;

    case CLIENT_LOBBY_CHAT_MSG_SEND_RESPONSE:
        LobbyChatMsgRecv(reinterpret_cast<WCHAR*>(dataPtr), dataSize);
        break;

    case CLIENT_LOBBY_USERLIST_DATA_ASYNC_RESPONSE:
        LobbyUserListDataAsync(dataPtr, dataCnt);
        break;

    case CLIENT_LOBBY_ROOMLIST_DATA_ASYNC_RESPONSE:
        LobbyRoomListDataAsync(dataPtr, dataCnt);
        break;

    case CLIENT_LOBBY_CREATE_ROOM_RESPONSE:
        CreateRoomResponse(static_cast<WORD>(*dataPtr));
        break;

    case CLIENT_WATING_ROOM_USERLIST_RESPONSE:
        WatingRoomUserList(dataPtr, dataCnt);
        break;

    case CLIENT_WATING_ROOM_TITLE_RESPONSE:
        WatingRoomTitle(reinterpret_cast<WCHAR*>(dataPtr), dataSize);
        break;

    case CLIENT_WROOM_BOOM_RESPONSE:
        WatingRoomBoom();
        break;

    case CLIENT_WROOM_CHAT_MSG_SEND_RESPONSE:
        WRoomChatMsgRecv(reinterpret_cast<WCHAR*>(dataPtr), dataSize);
        break;
    }
}

void SceneManager::LoadingPage(Scenetype _next)
{
    EnterCriticalSection(&m_sceneDeleteRequireLock);
    if (m_sceneVector[m_nowscene] != nullptr)
    {
        delete m_sceneVector[m_nowscene];
        m_sceneVector[m_nowscene] = nullptr;
    }
    m_nowscene = LOADING_SCENE;
    m_sceneVector[m_nowscene] = new LoadingScene(_next);
    LeaveCriticalSection(&m_sceneDeleteRequireLock);
}

void SceneManager::LoginPage()
{
    EnterCriticalSection(&m_sceneDeleteRequireLock);
    if (m_sceneVector[m_nowscene] != nullptr)
    {
        delete m_sceneVector[m_nowscene];
        m_sceneVector[m_nowscene] = nullptr;
    }
    m_nowscene = LOGIN_SCENE;
    m_sceneVector[m_nowscene] = new LoginScene();
    LeaveCriticalSection(&m_sceneDeleteRequireLock);
}

void SceneManager::LobbyPage()
{
    EnterCriticalSection(&m_sceneDeleteRequireLock);
    if (m_sceneVector[m_nowscene] != nullptr)
    {
        delete m_sceneVector[m_nowscene];
        m_sceneVector[m_nowscene] = nullptr;
    }
    m_nowscene = LOBBY_SCENE;
    m_sceneVector[m_nowscene] = new LobbyScene();
    LeaveCriticalSection(&m_sceneDeleteRequireLock);
}

void SceneManager::SceneChange(Scenetype _type)
{
    switch (_type)
    {
    case LOGIN_SCENE:
        LoginPage();
        break;
    case LOBBY_SCENE:
        LobbyPage();
        break;
    case SCENE_COUNT:
        break;
    }
}

void SceneManager::LobbyChatMsgRecv(WCHAR* _text, int _size)
{
    if (m_nowscene != LOBBY_SCENE)
        return;

    if (m_sceneVector[m_nowscene])
    {
        reinterpret_cast<LobbyScene*>(m_sceneVector[m_nowscene])->RecvLobbyChatMsg(_text, _size);
    }
}

void SceneManager::LobbyUserListDataAsync(char* _buffer, int _dataCnt)
{
    if (m_nowscene != LOBBY_SCENE)
        return;

    std::vector<UserDTO> _data;
    _data.resize(_dataCnt);
    
    if (_dataCnt > 0)
        memcpy(&_data[0], _buffer, _dataCnt * sizeof(UserDTO));

    if (m_sceneVector[m_nowscene])
    {
        reinterpret_cast<LobbyScene*>(m_sceneVector[m_nowscene])->LobbyUserListDataAsync(_data);
    }
}

void SceneManager::LobbyRoomListDataAsync(char* _buffer, int _dataCnt)
{
    if (m_nowscene != LOBBY_SCENE)
        return;

    std::vector<RoomDTO> _data;
    _data.resize(_dataCnt);
    
    if (_dataCnt > 0)
        memcpy(&_data[0], _buffer, _dataCnt * sizeof(RoomDTO));

    if (m_sceneVector[m_nowscene])
    {
        reinterpret_cast<LobbyScene*>(m_sceneVector[m_nowscene])->LobbyRoomListDataAsync(_data);
    }
}

void SceneManager::CreateRoomResponse(WORD _roomSq)
{
    UserDTO* my = MaplemonopolyApp::GetInstance()->GetUserInfo();
    my->SetRoomSq(_roomSq);
}

void SceneManager::WatingRoomUserList(char* _buffer, int _dataCnt)
{
    if (m_nowscene != LOBBY_SCENE)
        return;

    std::vector<UserDTO> _data;
    _data.resize(_dataCnt);

    memcpy(&_data[0], _buffer, _dataCnt * sizeof(UserDTO));

    if (m_sceneVector[m_nowscene])
    {
        reinterpret_cast<LobbyScene*>(m_sceneVector[m_nowscene])->WatingRoomUserList(_data);
    }

}

void SceneManager::WatingRoomTitle(WCHAR* _buffer, int _dataCnt)
{
    reinterpret_cast<LobbyScene*>(m_sceneVector[m_nowscene])->WatingRoomTitle(_buffer, _dataCnt);
}

void SceneManager::WRoomChatMsgRecv(WCHAR* _buffer, int _dataSize)
{
    if (m_nowscene != LOBBY_SCENE)
        return;

    if (m_sceneVector[m_nowscene])
    {
        reinterpret_cast<LobbyScene*>(m_sceneVector[m_nowscene])->WRoomChatMsgRecv(_buffer, _dataSize);
    }
}

void SceneManager::LobbyViewIndexUp()
{
    if (m_nowscene != LOBBY_SCENE)
        return;

    reinterpret_cast<LobbyScene*>(m_sceneVector[m_nowscene])->ViewindexUp();
}

void SceneManager::LobbyViewIndexDown()
{
    if (m_nowscene != LOBBY_SCENE)
        return;

    reinterpret_cast<LobbyScene*>(m_sceneVector[m_nowscene])->ViewindexDown();
}

void SceneManager::MoveViewIndex(int _index)
{
    if (m_nowscene != LOBBY_SCENE)
        return;

    reinterpret_cast<LobbyScene*>(m_sceneVector[m_nowscene])->MoveViewIndex(_index);
}

void SceneManager::WatingRoomBoom()
{
    reinterpret_cast<LobbyScene*>(m_sceneVector[m_nowscene])->WatingRoomBoom();
}
