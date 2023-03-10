#pragma once
/*********************************************************
				데이터 타입을 설정합니다.
**********************************************************/
enum ThreadId : unsigned int 
{
	BGM =   1,
	SOUND = 2,
	LOAD =  3,
	RECV =  4
};

enum Scenetype : unsigned int
{
	LOADING_SCENE = 0,
	LOGIN_SCENE = 1,
	LOBBY_SCENE = 2,
	SCENE_COUNT = 3
};

enum Resourcename : unsigned int
{
	LOADING_BACKGROUND_BITMAP,
	LOGIN_BACKGROUND_BITMAP,
	LOGIN_ALERTMODAL_BITMAP,
	LOBBY_BACKGROUND_BITMAP,
	LOBBY_CREATEROOMMODAL_BITMAP,
	WATING_ROOM_BACKGROUND_BITMAP,
	ORANGE_MURSHROOM_BITMAP,
	PIG_BITMAP,
	HORNY_MURSHROOM_BITMAP,
	ORANGE_MURSHROOM_IDLE_ANIMATION,
	HORNY_MURSHROOM_IDLE_ANIMATION,
	PIG_IDLE_ANIMATION,
	LOGIN_BGM,
	LOGIN_CLICK_SOUND,
};

enum Location : unsigned int
{
	LOBBY_ROOM =  0,
	WATING_ROOM = 1,
	GAME_ROOM	= 2
};

struct Packet
{
	WORD _size;			// Pakcet Size
	WORD _cnt;			// data cnt 
	WORD _type;			// data type
	char _data[1000];	// data
};

/*********************************************************
				클라이언트 요청 타입
**********************************************************/
enum ControllerType : int
{
	CLIENT_LOADING_REQUEST = 0,
	CLIENT_NEXTSCENE_REQUEST = 1,
	CLIENT_LOGIN_PROCESS_REQUEST = 2,
	CLIENT_LOBBY_CHAT_MSG_SEND_REQUEST = 3,
	CLIENT_LOBBY_DATA_ASYNC_REQUEST = 4,
	CLIENT_LOBBY_CREATE_ROOM_REQUEST = 5,
	CLIENT_WATING_ROOM_ASYNCDATA = 6,
	CLIENT_ETNER_WATING_ROOM_REQUEST = 7,
	CLIENT_WROOM_EXIT_REQUEST = 8,
	CLIENT_WROOM_CHAT_MSG_SEND_REQUEST = 9,
	CLIENT_CPICK_REQUEST = 10
};

/*********************************************************
				서버 응답 타입
**********************************************************/
enum ServerResponse : int
{
	CLIENT_LOADING_RESPONSE = 0,
	CLIENT_NEXTSCENE_RESPONSE = 1,
	CLIENT_LOBBY_CHAT_MSG_SEND_RESPONSE = 2,
	CLIENT_LOBBY_USERLIST_DATA_ASYNC_RESPONSE = 3,
	CLIENT_LOBBY_ROOMLIST_DATA_ASYNC_RESPONSE = 4,
	CLIENT_LOBBY_CREATE_ROOM_RESPONSE = 5,
	CLIENT_WATING_ROOM_USERLIST_RESPONSE = 6,
	CLIENT_WATING_ROOM_TITLE_RESPONSE = 7,
	CLIENT_WROOM_BOOM_RESPONSE = 8,
	CLIENT_WROOM_CHAT_MSG_SEND_RESPONSE = 9,
};

enum Roomstatus : int
{
	HOLD = 0
};

struct SpriteBinaryFileHeader
{
	char fileName[256];
	int resourceType;
	int  spriteCount;
};

struct SpriteBinaryFileData
{
	D2D1_RECT_F		rect;
	D2D1_POINT_2F	pivotPos;
};

enum RESOURCE_TYPE : int
{
	SPRITE = 0,
	ANIMATION = 1,
};

enum CPick : int
{
	HONY_MURSHROOM =   0,
	ORANGE_MURSHROOM = 1,
	PIG				=  2,
	NOUSER			=  3
};