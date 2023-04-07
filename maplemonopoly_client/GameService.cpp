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
		SceneType old = SceneManager::GetInstance()->GetNowScene();
		SceneManager::GetInstance()->Change(change._type);
		SceneManager::GetInstance()->GetScene(old)->Clean();
	}
}

void GameService::Recv(char* _buffer)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(_buffer);
	WORD size = header->size;
	WORD commond = header->id;

	switch (commond)
	{
	case PKT_C_LOBBYCHAT:
		LobbyChatMsgRecv(_buffer);
		break;

	case PKT_C_LOBBYASYNC:
		LobbyAsync(_buffer);
		break;

	case PKT_C_WROOM_ENTEROTHERUSER:
		PlayerWRoomOtherEnter(_buffer);
		break;

	case PKT_C_WROOM_ENTERUSER:
		PlayerWRoomEnter(_buffer);
		break;

	case PKT_C_WROOMCHAT:
		WRoomChat(_buffer);
		break;

	case PKT_C_WROOM_ASYNCUSERLIST:
		WRoomAsync(_buffer);
		break;

	case PKT_C_PICKCHANGE:
		WRoomPickChange(_buffer);
		break;

	case PKT_C_READY:
		WRoomReady(_buffer);
		break;

	case PKT_C_ENTERGAME:
		EnterGame();
		break;

	case PKT_C_GAMEINIT:
		GameUserAsync(_buffer);
		break;

	case PKT_C_GAMETURNSEND:
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(_buffer);
		int turn = *(int*)(header + 1);
		TurnSend(turn);
		break;
	}


	case PKT_C_TURNINFO:
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(_buffer);
		int turn = *(int*)(header + 1);
		GameUserNumber(turn);
		break;
	}


	case PKT_C_DICEDROP:
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(_buffer);
		char* readPos = (char*)(header + 1);
		DiceData* dd = (DiceData*)(readPos);
		DiceDropResult(dd);
		break;
	}

	
	case PKT_C_DICEDROPEND:
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(_buffer);
		char* readPos = (char*)(header + 1);
		PlayerMove(readPos);
		break;
	}


	case PKT_C_BUYREGION:
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(_buffer);
		Region* readPos = (Region*)(header + 1);
		GameBuyRegion(readPos);
		break;
	}


	case PKT_C_BUYREGIONRESPONSE:
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(_buffer);
		char* readPos = (char*)(header + 1);
		GameBuyRegionModalProcessResponse(readPos);
		break;
	}


	case PKT_C_BUYOTHERREGION:
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(_buffer);
		char* readPos = (char*)(header + 1);
		GameBuyRegionModalOtherProcessResponseEx(readPos);
		break;
	}

	case PKT_C_PASSCOST:
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(_buffer);
		char* readPos = (char*)(header + 1);
		MoneyPassCost(readPos);
		break;
	}

	case PKT_C_PLAYERDEAD:
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(_buffer);
		char* readPos = (char*)(header + 1);
		PlayerDead(readPos);
		break;
	}

	case PKT_C_GAMEEND:
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(_buffer);
		int readPos = *(int*)(header + 1);
		GameEnd(readPos);
		break;
	}

	case PKT_C_DISCONNECT:
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(_buffer);
		int readPos = *(int*)(header + 1);
		PlayerDisconnect(readPos);
		break;
	}	

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

void GameService::LobbyChatMsgRecv(char* buffer)
{
	SceneType now = SceneManager::GetInstance()->GetNowScene();

	if (now != LOBBY_SCENE)
		return;

	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->LobbyChatMsgRecv(buffer);
}

void GameService::LobbyUsernameAsync(WCHAR* _text, int _size)
{
	SceneType now = SceneManager::GetInstance()->GetNowScene();

	if (now != LOBBY_SCENE)
		return;

	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->LobbyUsernameAsync(_text, _size);
}

void GameService::WRoomChat(WCHAR* _text, int _size)
{
	SceneType now = SceneManager::GetInstance()->GetNowScene();

	if (now != LOBBY_SCENE)
		return;

	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->WRoomChat(_text, _size);
}

void GameService::WRoomChat(char* buffer)
{
	SceneType now = SceneManager::GetInstance()->GetNowScene();

	if (now != LOBBY_SCENE)
		return;

	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->WRoomChat(buffer);
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

void GameService::GameUserAsync(char* _buffer)
{
	static_cast<GameScene*>(SceneManager::GetInstance()->GetScene(GAME_SCENE))->GameUserAsync(_buffer);
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

void GameService::PlayerMove(char* _data)
{
	static_cast<GameScene*>(SceneManager::GetInstance()->GetScene(GAME_SCENE))->PlayerMove(_data);
}

void GameService::GameBuyRegion(Region* dataPtr)
{
	static_cast<GameScene*>(SceneManager::GetInstance()->GetScene(GAME_SCENE))->GameBuyRegion(dataPtr);
}

void GameService::GameBuyRegionModalProcessResponse(char* _dataPtr)
{
	static_cast<GameScene*>(SceneManager::GetInstance()->GetScene(GAME_SCENE))->GameBuyRegionModalProcessResponse(_dataPtr);
}

void GameService::MoneyPassCost(char* _dataPtr)
{
	static_cast<GameScene*>(SceneManager::GetInstance()->GetScene(GAME_SCENE))->MoneyPassCost(_dataPtr);
}

void GameService::GameBuyRegionModalOtherProcessResponseEx(char* _dataPtr)
{
	static_cast<GameScene*>(SceneManager::GetInstance()->GetScene(GAME_SCENE))->GameBuyRegionModalOtherProcessResponseEx(_dataPtr);
}

void GameService::GameOtherBuyResponse(char* _dataPtr)
{
	static_cast<GameScene*>(SceneManager::GetInstance()->GetScene(GAME_SCENE))->GameOtherBuyResponse(_dataPtr);
}

void GameService::PlayerDead(char* _data)
{
	static_cast<GameScene*>(SceneManager::GetInstance()->GetScene(GAME_SCENE))->PlayerDead(_data);
}

void GameService::GameEnd(int _data)
{
	static_cast<GameScene*>(SceneManager::GetInstance()->GetScene(GAME_SCENE))->GameEnd(_data);
}

void GameService::PlayerDisconnect(int _playerIndex)
{
	static_cast<GameScene*>(SceneManager::GetInstance()->GetScene(GAME_SCENE))->PlayerDisconnect(_playerIndex);
}

void GameService::PlayerWRoomEnter(User* _user)
{
	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->PlayerWRoomEnter(_user);
}

void GameService::PlayerWRoomEnter(char* buffer)
{
	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->PlayerWRoomEnter(buffer);
}

void GameService::PlayerWRoomOtherEnter(char* buffer)
{
	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->PlayerWRoomOtherEnter(buffer);
}

void GameService::PlayerWRoomExit(User* _user)
{

	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->PlayerWRoomExit(_user);
}

void GameService::PlayerReady(char* buffer)
{
	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->PlayerReady(buffer);
}

void GameService::PlayerPickChange(char* buffer)
{
	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->PlayerPickChange(buffer);
}

void GameService::WRoomTitleAsync(WCHAR* _dataPtr, int _dataSize)
{
	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->WRoomTitleAsync(_dataPtr, _dataSize);
}

void GameService::LobbyAsync(char* buffer)
{
	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->LobbyAsync(buffer);
}

void GameService::WRoomAsync(char* buffer)
{
	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->WRoomAsync(buffer);
}

void GameService::WRoomPickChange(char* buffer)
{
	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->WRoomPickChange(buffer);
}

void GameService::WRoomReady(char* buffer)
{
	static_cast<LobbyScene*>(SceneManager::GetInstance()->GetScene(LOBBY_SCENE))->WRoomReady(buffer);
}
