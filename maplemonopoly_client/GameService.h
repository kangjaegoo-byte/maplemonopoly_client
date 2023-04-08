#pragma once
class GameService
{
private:
	static GameService* m_instance;

	GameService() {};
	~GameService() {};

	
public:
	static GameService* GetInstance();
	static void DeleteInstance() { if(m_instance) delete m_instance; }

	void   Init();
	void   Clean();
	void   SceneChange();
	void   Recv(char* _buffer);
public:
	void   LobbyUserListAsync(char* _data, int _cnt);
	void   LobbyRoomListAsync(char* _data, int _cnt);
	void   LobbyChatMsgRecv(char* buffer);
	void   LobbyUsernameAsync(WCHAR* _text, int _size);
	void   WRoomChat(WCHAR* _text, int _size);
	void   WRoomChat(char* buffer);
	void   EnterGame();
	void   GameUserAsync(char* _data, int _cnt);
	void   GameUserAsync(char* _buffer);
	void   GameUserNumber(int _idx);
	void   TurnSend(int _playerIdx);
	void   DiceDropResult(DiceData* _diceData);
	void   PlayerMove(char* _data);
	void   GameBuyRegion(Region* dataPtr);

	void   GameBuyRegionModalProcessResponse(char* _dataPtr);
	void   MoneyPassCost(char* _dataPtr);
	void   GameBuyRegionModalOtherProcessResponseEx(char* _dataPtr);
	void   GameOtherBuyResponse(char* _dataPtr);
	void PlayerDead(char* _data);
	void GameEnd(int _data);
	void PlayerDisconnect(int _playerIndex);

	void PlayerWRoomEnter(class  User* _user);
	void PlayerWRoomEnter(char* buffer);
	void PlayerWRoomOtherEnter(char* buffer);
	void PlayerWRoomExit(User* _user);
	void PlayerReady(char* buffer);
	void PlayerPickChange(char* buffer);
	void WRoomTitleAsync(WCHAR* _dataPtr, int _dataSize);

	void LobbyAsync(char* buffer);
	void WRoomAsync(char* buffer);
	void WRoomPickChange(char* buffer);
	void WRoomReady(char* buffer);
};

