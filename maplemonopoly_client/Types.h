#pragma once

enum Threadid : unsigned int
{
	BGM = 1,
	SOUND = 2,
	LOAD = 3,
	RECV = 4
};

enum SceneType : unsigned int
{
	NONE=  -1,
	LOADING_SCENE = 0,
	LOGIN_SCENE = 1,
	LOBBY_SCENE = 2,
	GAME_SCENE = 3,
	SCENE_COUNT = 4
};

enum ResourceName : unsigned int
{
	LOADING_BACKGROUND_BITMAP,
	LOGIN_BACKGROUND_BITMAP,
	LOGIN_ALERTMODAL_BITMAP,
	LOBBY_BACKGROUND_BITMAP,
	LOBBY_CREATEROOMMODAL_BITMAP,
	WATING_ROOM_BACKGROUND_BITMAP,
	ORANGE_MURSHROOM_BITMAP,
	PIG_BITMAP,
	HORN_MURSHROOM_BITMAP,
	ORANGE_MURSHROOM_IDLE_ANIMATION,
	HORN_MURSHROOM_IDLE_ANIMATION,
	PIG_IDLE_ANIMATION,
	ORANGE_MURSHROOM_MOVE_ANIMATION,
	HORN_MURSHROOM_MOVE_ANIMATION,
	PIG_MOVE_ANIMATION,
	GAME_BACKGROUND_BITMAP,
	GAME_BOARD_BITMAP,
	GAME_DICE_BITMAP,
	GAME_DICE_ONE_ANIMATION,
	GAME_DICE_TWO_ANIMATION,
	GAME_DICE_THREE_ANIMATION,
	GAME_DICE_FOUR_ANIMATION,
	GAME_DICE_FIVE_ANIMATION,
	GAME_DICE_SIX_ANIMATION,
	GAME_MODAL_VIEW_BITMAP,
	GAME_MONO_BITMAP,
	GAME_MONEY_BITMAP,
	LOGIN_BGM,
	DICE_DROP_SOUND,
	DICE_NUMBER_BITMAP,
	READY_BITMAP,

	USERINFO1_BITMAP,
	USERINFO2_BITMAP,
	USERINFO3_BITMAP,
	USERINFO4_BITMAP,


	GAME_ONEPICK_HOUSE,
	GAME_ONEPICK_HOTEL,
	GAME_TWOPICK_HOUSE,
	GAME_TWOPICK_HOTEL,
	GAME_THREEPICK_HOUSE,
	GAME_THREEPICK_HOTEL,
	GAME_FOURPICK_HOUSE,
	GAME_FOURPICK_HOTEL,
	GAME_DICE_BTN_BITMAP,
	GAME_ALERT_TEXT_BITMAP,

	GAME_ONE_DICE,
	GAME_TWO_DICE,
	GAME_THREE_DICE,
	GAME_FOUR_DICE,
	GAME_FIVE_DICE,
	GAME_SIX_DICE,
	GAME_SEVEN_DICE,
	GAME_EIGHT_DICE,
	GAME_NINE_DICE,
	GAME_TEN_DICE,
	GAME_ELEVEN_DICE,
	GAME_TWELVE_DICE,
	GAME_DICE_BTN_PRESS_SPRITE,
	GAME_DICE_BTN_PRESS_UP_SPRITE,

	ONE_SOUND,
	TWO_SOUND,
	THREE_SOUND,
	FOUR_SOUND,
	FIVE_SOUND,
	SIX_SOUND,
	SEVEN_SOUND,
	EIGHT_SOUND,
	NINE_SOUND,
	TEN_SOUND,
	ELEVEN_SOUND,
	TWELVE_SOUND,
	MYTURN_SOUND,
};

enum Location : unsigned int
{
	LOBBY_ROOM = 0,
	WATING_ROOM = 1,
	GAME_ROOM = 2
};

struct Packet
{
	WORD _size;			// Pakcet Size
	WORD _cnt;			// data cnt 
	WORD _type;			// data type
	char _data[1000];	// data
};


enum Requesttype : int
{
	PROCESS_LOGIN_REQUEST = 0,
	PROCESS_ASYNC_LOBBY_REQUEST = 1,
	PROCESS_LOBBY_CHAT_REQUEST = 2,
	PROCESS_CREATE_ROOM_REQUEST = 3,
	PROCESS_ENTER_ROOM_REQUEST = 4,
	PROCESS_ASYNC_WROOM_REQUEST = 5,
	PROCESS_WROOM_CHAT_REQUEST = 6,
	PROCESS_WROOM_EXIT_REQUEST = 7,
	PROCESS_PICK_CHANGE_REQUEST = 8,
	PROCESS_GAME_START_REQUEST = 9,
	PROCESS_GAME_DICE_REQUEST = 10,
	PROCESS_GAME_DICE_REUSLT_REQUEST = 11,
	PROCESS_GAME_MOVE_COMPLETE_REQUEST = 12,
	PROCESS_GAME_BUYREGION_REQUEST = 13,
	PROCESS_GAME_BUYREGION_OTHER_REQUEST = 14,
	PROCESS_GAME_NEXTTURN_REQUEST = 15,
};

enum Responsetype : int
{
	ASYNC_LOBBY_USERLIST_RESPONSE = 0,
	PROCESS_LOBBY_CHAT_RESPONSE = 1,
	ASYNC_LOBBY_ROOMLIST_RESPONSE = 2,
	ASYNC_LOBBY_USERNAME_RESPONSE = 3,
	ASYNC_WROOM_USER_RESPONSE = 4,
	ASYNC_WROOM_TITLE_RESPONSE = 5,
	PROCESS_WROOM_CHAT_RESPONSE = 6,
	PROCESS_GAME_ENTER_RESPONSE = 7,
	PROCESS_GAME_USER_ASYNC_RESPONSE = 8,
	PROCESS_GAME_USER_NUMBER_RESPONSE = 9,
	PROCESS_GAME_TURN_SEND_RESPONSE = 10,
	PROCESS_GAME_DICE_RESPONSE = 11,
	PROCESS_GAME_MOVE_RESPONSE = 12,
	PROCESS_GAME_BUY_REGION_MODAL_RESPONSE = 13,
	PROCESS_GAME_BUY_REGION_MODAL_PROCESS_RESPONSE = 14,
	PROCESS_GAME_BUY_REGION_OTHER_REGION_RESPONSE = 15,
	PROCESS_GAME_MONEY_PASS_RESPONSE = 16,
	PROCESS_GAME_BUY_REGION_OTHER_MODAL_RESPONSE = 17,
};

enum Roomstatus : int
{
	HOLD = 0,
	GAME = 1
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

enum Pick : int
{
	HORN_MURSHROOM = 0,
	ORANGE_MURSHROOM = 1,
	PIG = 2,
	NOUSER = 3
};

enum PlayerState : int
{
	IDLE = 0,
	MOVE = 1
};

enum DiceState : int
{
	DICE_HOLD = 0,
	DICE_DROP = 1,
	DICE_RESULT = 2
};

struct DiceData
{
	int _dice1;
	int _dice2;
	int _sum;
	int _playerIndex;
};

struct Region
{
	int _ownerPlayerIndx = -1;
	int _passCost = 0;
	int _mapIndex = 0;
	int _level = 0;
	int _oriCost = 0;
};

struct ClientMapData
{
	int _xPos;
	int _yPos;
	bool _rotate;

	int _mxPos;
	int _myPos;
};

struct SceneChangeData
{
	bool	  _loading;
	SceneType _type;
};

enum ViewType : int
{
	VIEW_NONE = -1,
	LOBBY_VIEW = 0,
	CROOM_VIEW = 1,
	WROOM_VIEW = 2,
	VIEW_COUNT = 3
};

enum AlertTextState : int
{
	AlertTextState_NONE = -1,
	AlertTextState_DOUBLE = 0,
	AlertTextState_MONEY = 1
};
