#include "pch.h"
#include "GameService.h"
#include "LoadingScene.h"
#include "GameScene.h"
#include "LobbyScene.h"
#include "LoginScene.h"
#include "User.h"
#include "Room.h"
GameService* GameService::m_instance = nullptr;

GameService* GameService::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new GameService();

	return m_instance;
}

void GameService::Init()
{
	LoadingScene* loadingScene = new LoadingScene();
	LoginScene* loginScene = new LoginScene();
	LobbyScene* lobbyScene = new LobbyScene();
	GameScene* gameScene = new GameScene();

	SceneManager::GetInstance()->Add(loadingScene);
	SceneManager::GetInstance()->Add(loginScene);
	SceneManager::GetInstance()->Add(lobbyScene);
	SceneManager::GetInstance()->Add(gameScene);
}

void GameService::Clean()
{
	
}

void GameService::SceneChange()
{
	SceneChangeData change = SceneManager::GetInstance()->Change();

	if (change._type == SceneType::NONE)
		return;

	if (change._loading)
	{
		LoadingScene* loadingScene = static_cast<LoadingScene*>(SceneManager::GetInstance()->GetScene(LOADING_SCENE));
		loadingScene->SetLoadTargetScene(change._type);
		SceneManager::GetInstance()->Change(LOADING_SCENE);
	}
	else
	{
		SceneManager::GetInstance()->Change(change._type);
	}
}

void GameService::Recv(char* _buffer)
{
	WORD* size = (WORD*)_buffer;
	int dataSize = *size - PACKET_HEADER_SIZE;
	size++;

	WORD* cnt = (WORD*)size;
	int dataCnt = *cnt;
	cnt++;

	WORD* type = (WORD*)cnt;
	int responseType = *type;
	type++;

	char* dataPtr = (char*)type;

	switch (responseType)
	{
	case ASYNC_LOBBY_USERLIST_RESPONSE:
		LobbyUserListAsync(dataPtr, dataCnt);
		break;

	case PROCESS_LOBBY_CHAT_RESPONSE:
		LobbyChatMsgRecv((WCHAR*)dataPtr, dataSize);
		break;

	case ASYNC_LOBBY_ROOMLIST_RESPONSE:
		LobbyRoomListAsync(dataPtr, dataCnt);
		break;

	case ASYNC_LOBBY_USERNAME_RESPONSE:
		LobbyUsernameAsync((WCHAR*)dataPtr, dataSize);
		break;

	case ASYNC_WROOM_USER_RESPONSE:
		WRoomUserListAsync(dataPtr, dataCnt);
		break;

	case ASYNC_WROOM_TITLE_RESPONSE:
		WRoomTitleAsync((WCHAR*)dataPtr, dataSize);
		break;

	case PROCESS_WROOM_CHAT_RESPONSE:
		WRoomChat((WCHAR*)dataPtr, dataSize);
		break;
		
	case PROCESS_GAME_ENTER_RESPONSE:
		EnterGame();
		break;

	case PROCESS_GAME_USER_ASYNC_RESPONSE:
		GameUserAsync(dataPtr, dataCnt);
		break;

	case PROCESS_GAME_USER_NUMBER_RESPONSE:
		GameUserNumber(static_cast<int>(*dataPtr));
		break;

	case PROCESS_GAME_TURN_SEND_RESPONSE:
		TurnSend(static_cast<int>(*dataPtr));
		break;

	case PROCESS_GAME_DICE_RESPONSE:
		DiceDropResult(reinterpret_cast<DiceData*>(dataPtr));
		break;
	}

}

void GameService::LobbyUserListAsync(char* _data, int _cnt)
{
	SceneType now = SceneManager::GetInstance()->GetNowScene();

	if (now != LOBBY_SCENE)
		return;

	std::vector<User> users;
	users.resize(_cnt);

	if (_cnt > 0)
		memcpy(&users[0], _data, _cnt * sizeof(User));

	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->LobbyUserListDataAsync(users);
}

void GameService::LobbyRoomListAsync(char* _data, int _cnt)
{
	SceneType now = SceneManager::GetInstance()->GetNowScene();

	if (now != LOBBY_SCENE)
		return;

	std::vector<Room> rooms;
	rooms.resize(_cnt);

	if (_cnt > 0)
		memcpy(&rooms[0], _data, _cnt * sizeof(Room));

	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->LobbyRoomListDataAsync(rooms);
}

void GameService::LobbyChatMsgRecv(WCHAR* _text, int _size)
{
	SceneType now = SceneManager::GetInstance()->GetNowScene();

	if (now != LOBBY_SCENE)
		return;

	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->LobbyChatMsgRecv(_text, _size);
}

void GameService::LobbyUsernameAsync(WCHAR* _text, int _size)
{
	SceneType now = SceneManager::GetInstance()->GetNowScene();

	if (now != LOBBY_SCENE)
		return;

	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->LobbyUsernameAsync(_text, _size);
}

void GameService::WRoomUserListAsync(char* _data, int _cnt)
{
	SceneType now = SceneManager::GetInstance()->GetNowScene();

	if (now != LOBBY_SCENE)
		return;

	std::vector<User> data;
	data.resize(_cnt);

	memcpy(&data[0], _data, _cnt * sizeof(User));

	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->WRoomUserListAsync(data);
}

void GameService::WRoomTitleAsync(WCHAR* _text, int _size)
{
	SceneType now = SceneManager::GetInstance()->GetNowScene();

	if (now != LOBBY_SCENE)
		return;

	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->WRoomTitleAsync(_text, _size);
}

void GameService::WRoomChat(WCHAR* _text, int _size)
{
	SceneType now = SceneManager::GetInstance()->GetNowScene();

	if (now != LOBBY_SCENE)
		return;

	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->WRoomChat(_text, _size);
}

void GameService::EnterGame()
{
	SceneType now = SceneManager::GetInstance()->GetNowScene();

	if (now != LOBBY_SCENE)
		return;


	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->EnterGame();
}

void GameService::GameUserAsync(char* _data, int _cnt)
{
	SceneType now = SceneManager::GetInstance()->GetNowScene();

	std::vector<User> data;
	data.resize(_cnt);

	memcpy(&data[0], _data, _cnt * sizeof(User));
	static_cast<GameScene*>(SceneManager::GetInstance()->GetScene(GAME_SCENE))->GameUserAsync(data);
}

void GameService::GameUserNumber(int _idx)
{
	SceneType now = SceneManager::GetInstance()->GetNowScene();
	static_cast<GameScene*>(SceneManager::GetInstance()->GetScene(GAME_SCENE))->GameUserNumber(_idx);
}

void GameService::TurnSend(int _playerIdx)
{
	static_cast<GameScene*>(SceneManager::GetInstance()->GetScene(GAME_SCENE))->TurnSend(_playerIdx);
}

void GameService::DiceDropResult(DiceData* _diceData)
{
	static_cast<GameScene*>(SceneManager::GetInstance()->GetScene(GAME_SCENE))->DiceDropResult(_diceData);
}
