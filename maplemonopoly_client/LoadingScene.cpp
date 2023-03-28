#include "pch.h"
#include "LoadingScene.h"
#include "ResourceManager.h"
#include "Sound.h"
const int LoadingBarWidht = 395;
unsigned int _stdcall LaodProc(void* Args);
void wstrconcat(WCHAR* _ret, WCHAR* _str1, WCHAR* _str2);


LoadingScene::LoadingScene() : Scene(LOADING_SCENE)
{
	Init();
}

LoadingScene::~LoadingScene()
{
	Clean();
}

void LoadingScene::Init()
{
	// D2D1 Init
	m_crt = D2D1Core::GetInstance()->GetCRT();
	m_rt = D2D1Core::GetInstance()->GetRT();
	D2D1Core::GetInstance()->SetFontFormat(&m_textFormat, L"나눔고딕", 14);
	D2D1Core::GetInstance()->CreateColorBrush(&m_blackBrush, D2D1::ColorF::Black);
	D2D1Core::GetInstance()->CreateColorBrush(&m_blueBrush, D2D1::ColorF::CadetBlue);

	// Ladoing Bitmap Load 
	WCHAR loadPath[1000];
	WCHAR bitmapPath[256] = L"..\\imgpack\\loading\\loading.png";
	_wfullpath(loadPath, bitmapPath, _MAX_PATH);
	Bitmap* bitmap = D2D1Core::GetInstance()->LoadBitmapByFileName(loadPath);
	ResourceManager::GetInstance()->Put(LOADING_BACKGROUND_BITMAP, bitmap);
	m_loadScene = SceneType::LOGIN_SCENE;
}

void LoadingScene::Update(int _deltaTick)
{
	if (m_loadStart == false)
		Load();
}

void LoadingScene::Render()
{
	RECT rect;
	GetClientRect(D2D1Core::GetInstance()->GetHWND(), &rect);
	D2D1_RECT_F rt_dest = { rect.left, rect.top, rect.right, rect.bottom };

	m_crt->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(LOADING_BACKGROUND_BITMAP)->GetBitmap(), rt_dest);

	D2D1_RECT_F loadingBar = { 213, 454, 213 + m_percent, 513 };
	m_crt->FillRectangle(loadingBar, m_blueBrush);

	if (m_loadFilename)
	{
		WCHAR text[1000];
		swprintf_s(text, _countof(text), L"게임리소스 로드중: %s", m_loadFilename);
		m_crt->DrawTextW(text, wcslen(text), m_textFormat, { 306, 473, 705, 513 }, m_blackBrush);
	}
}

void LoadingScene::Clean()
{
	m_textFormat->Release();
	m_blackBrush->Release();
	m_blueBrush->Release();
	ResourceManager::GetInstance()->DeleteBitmap(LOADING_BACKGROUND_BITMAP);
}

void LoadingScene::MouseMoveEvent(int _x, int _y)
{
}

void LoadingScene::MouseClickEvent(int _x, int _y)
{
}

void LoadingScene::MouseClickUpEnvet(int _x, int _y)
{
}

void LoadingScene::CharEvent(WPARAM _key)
{
}

SceneChangeData LoadingScene::Change()
{
	if (m_loadEnd == false)
		return SceneChangeData{ false, SceneType::NONE };

	LoadInit();
	return SceneChangeData{ false, m_loadScene };
}

void LoadingScene::Add(int _percent)
{
	m_percent += _percent;
}

void LoadingScene::Flush()
{
	m_percent = LoadingBarWidht;
	Sleep(50);
	m_loadEnd = true;
}

void LoadingScene::Load()
{
	m_loadStart = true;
	unsigned int theradId = Threadid::LOAD;
	_beginthreadex(NULL, 0, &LaodProc, this, 0, &theradId);
}

void LoadingScene::LoadInit()
{
	m_percent = 0;
	m_loadFilename = nullptr;
	m_loadStart = false;
	m_loadEnd = false;
}

unsigned int _stdcall LaodProc(void* Args)
{
	LoadingScene* lac = reinterpret_cast<LoadingScene*>(Args);

	std::vector<WCHAR*> bitmapPathVector;
	std::vector<WCHAR*> soundPathVector;
	std::vector<WCHAR*> animationVector;
	std::vector<WCHAR*> spriteVector;

	const WCHAR* bitmapPathList[] = { L"",L"..\\imgpack\\resource\\*",L"",L"" };
	const WCHAR* soundPathList[] = { L"",L"..\\soundpack\\resource\\*",L"",L"" };
	const WCHAR* animationPathList[] = { L"",L"..\\animation\\resource\\*",L"",L"" };
	const WCHAR* spritePathList[] = { L"",L"..\\sprite\\resource\\*",L"",L"" };

	const WCHAR* rootBPathList[] = { L"",L"..\\imgpack\\resource\\", L"",L"" };
	const WCHAR* rootSPathList[] = { L"",L"..\\soundpack\\resource\\", L"",L"" };
	const WCHAR* rootAPathList[] = { L"",L"..\\animation\\resource\\", L"",L"" };
	const WCHAR* rootSpPathjList[] = { L"",L"..\\sprite\\resource\\", L"",L"" };

	SceneType loadscene = lac->GetLoadSceneType();

	ResourceManager::GetInstance()->GetFileList(bitmapPathVector, bitmapPathList[loadscene]);
	ResourceManager::GetInstance()->GetFileList(soundPathVector, soundPathList[loadscene]);
	ResourceManager::GetInstance()->GetFileList(animationVector, animationPathList[loadscene]);
	ResourceManager::GetInstance()->GetFileList(spriteVector, spritePathList[loadscene]);

	const int totalDataCount = bitmapPathVector.size() + soundPathVector.size() + animationVector.size() + spriteVector.size();

	if (totalDataCount == 0) return 0;

	int percent = LoadingBarWidht / totalDataCount;
	Sleep(500);

	for (int i = 0; i < bitmapPathVector.size(); i++)
	{
		WCHAR loadPath[1000] = L"";
		WCHAR fullPath[1000] = L"";
		WCHAR* filename = bitmapPathVector[i];
		wstrconcat(fullPath, const_cast<WCHAR*>(rootBPathList[loadscene]), filename);
		_wfullpath(loadPath, fullPath, _MAX_PATH);
		Bitmap* bitmap = D2D1Core::GetInstance()->LoadBitmapByFileName(loadPath);

		if (wcscmp(filename, L"alert.png") == 0)
			ResourceManager::GetInstance()->Put(LOGIN_ALERTMODAL_BITMAP, bitmap);

		if (wcscmp(filename, L"login_img.png") == 0)
			ResourceManager::GetInstance()->Put(LOGIN_BACKGROUND_BITMAP, bitmap);

		if (wcscmp(filename, L"lobby.png") == 0)
			ResourceManager::GetInstance()->Put(LOBBY_BACKGROUND_BITMAP, bitmap);

		if (wcscmp(filename, L"croom.png") == 0)
			ResourceManager::GetInstance()->Put(LOBBY_CREATEROOMMODAL_BITMAP, bitmap);

		if (wcscmp(filename, L"room.png") == 0)
			ResourceManager::GetInstance()->Put(WATING_ROOM_BACKGROUND_BITMAP, bitmap);

		if (wcscmp(filename, L"horny_mushroom.png") == 0)
			ResourceManager::GetInstance()->Put(HORN_MURSHROOM_BITMAP, bitmap);

		if (wcscmp(filename, L"orange_mushroom.png") == 0)
			ResourceManager::GetInstance()->Put(ORANGE_MURSHROOM_BITMAP, bitmap);

		if (wcscmp(filename, L"pig.png") == 0)
			ResourceManager::GetInstance()->Put(PIG_BITMAP, bitmap);

		if (wcscmp(filename, L"game.png") == 0)
			ResourceManager::GetInstance()->Put(GAME_BACKGROUND_BITMAP, bitmap);

		if (wcscmp(filename, L"board.png") == 0)
			ResourceManager::GetInstance()->Put(GAME_BOARD_BITMAP, bitmap);

		if (wcscmp(filename, L"dice.png") == 0)
			ResourceManager::GetInstance()->Put(GAME_DICE_BITMAP, bitmap);

		if (wcscmp(filename, L"GameViewModal.png") == 0)
			ResourceManager::GetInstance()->Put(GAME_MODAL_VIEW_BITMAP, bitmap);

		if (wcscmp(filename, L"mono.png") == 0)
			ResourceManager::GetInstance()->Put(GAME_MONO_BITMAP, bitmap);

		if (wcscmp(filename, L"money.png") == 0)
			ResourceManager::GetInstance()->Put(GAME_MONEY_BITMAP, bitmap);

		if (wcscmp(filename, L"diceNumber.png") == 0)
			ResourceManager::GetInstance()->Put(DICE_NUMBER_BITMAP, bitmap);

		if (wcscmp(filename, L"ready.png") == 0)
			ResourceManager::GetInstance()->Put(READY_BITMAP, bitmap);

		if (wcscmp(filename, L"user1.png") == 0)
			ResourceManager::GetInstance()->Put(USERINFO1_BITMAP, bitmap);

		if (wcscmp(filename, L"user2.png") == 0)
			ResourceManager::GetInstance()->Put(USERINFO2_BITMAP, bitmap);

		if (wcscmp(filename, L"user3.png") == 0)
			ResourceManager::GetInstance()->Put(USERINFO3_BITMAP, bitmap);

		if (wcscmp(filename, L"user4.png") == 0)
			ResourceManager::GetInstance()->Put(USERINFO4_BITMAP, bitmap);

		if (wcscmp(filename, L"diceBtn.png") == 0)
			ResourceManager::GetInstance()->Put(GAME_DICE_BTN_BITMAP, bitmap);

		if (wcscmp(filename, L"alertText.png") == 0)
			ResourceManager::GetInstance()->Put(GAME_ALERT_TEXT_BITMAP, bitmap);

		if (wcscmp(filename, L"marker.png") == 0)
			ResourceManager::GetInstance()->Put(GAME_MARKER_BITMAP, bitmap);

		lac->SetLoadFilename(filename);
		lac->Add(percent);
		Sleep(50);
	}

	for (int i = 0; i < soundPathVector.size(); i++)
	{
		WCHAR fullPath[1000] = L"";
		WCHAR* filename = soundPathVector[i];
		wstrconcat(fullPath, const_cast<WCHAR*>(rootSPathList[loadscene]), filename);
		Sound* sound = new Sound(fullPath);
		if (wcscmp(filename, L"login.wav") == 0)
			ResourceManager::GetInstance()->Put(LOGIN_BGM, sound);

		if (wcscmp(filename, L"diceDrop.wav") == 0)
			ResourceManager::GetInstance()->Put(DICE_DROP_SOUND, sound);

		if (wcscmp(filename, L"one.wav") == 0)
			ResourceManager::GetInstance()->Put(ONE_SOUND, sound);

		if (wcscmp(filename, L"two.wav") == 0)
			ResourceManager::GetInstance()->Put(TWO_SOUND, sound);

		if (wcscmp(filename, L"three.wav") == 0)
			ResourceManager::GetInstance()->Put(THREE_SOUND, sound);

		if (wcscmp(filename, L"four.wav") == 0)
			ResourceManager::GetInstance()->Put(FOUR_SOUND, sound);

		if (wcscmp(filename, L"five.wav") == 0)
			ResourceManager::GetInstance()->Put(FIVE_SOUND, sound);

		if (wcscmp(filename, L"six.wav") == 0)
			ResourceManager::GetInstance()->Put(SIX_SOUND, sound);

		if (wcscmp(filename, L"seven.wav") == 0)
			ResourceManager::GetInstance()->Put(SEVEN_SOUND, sound);

		if (wcscmp(filename, L"eight.wav") == 0)
			ResourceManager::GetInstance()->Put(EIGHT_SOUND, sound);

		if (wcscmp(filename, L"nine.wav") == 0)
			ResourceManager::GetInstance()->Put(NINE_SOUND, sound);

		if (wcscmp(filename, L"ten.wav") == 0)
			ResourceManager::GetInstance()->Put(TEN_SOUND, sound);

		if (wcscmp(filename, L"eleven.wav") == 0)
			ResourceManager::GetInstance()->Put(ELEVEN_SOUND, sound);

		if (wcscmp(filename, L"twleve.wav") == 0)
			ResourceManager::GetInstance()->Put(TWELVE_SOUND, sound);

		if (wcscmp(filename, L"myTurn.wav") == 0)
			ResourceManager::GetInstance()->Put(MYTURN_SOUND, sound);

		lac->SetLoadFilename(filename);
		lac->Add(percent);	
		Sleep(50);
	}

	for (int i = 0; i < animationVector.size(); i++)
	{
		WCHAR loadPath[1000] = L"";
		WCHAR fullPath[1000] = L"";
		WCHAR* filename = animationVector[i];
		wstrconcat(fullPath, const_cast<WCHAR*>(rootAPathList[loadscene]), filename);
		_wfullpath(loadPath, fullPath, _MAX_PATH);

		if (wcscmp(filename, L"hony_mushroom_idel.spr") == 0)
			ResourceManager::GetInstance()->Put(HORN_MURSHROOM_IDLE_ANIMATION, reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"orange_mushroom_idel.spr") == 0)
			ResourceManager::GetInstance()->Put(ORANGE_MURSHROOM_IDLE_ANIMATION, reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"pig_idel.spr") == 0)
			ResourceManager::GetInstance()->Put(PIG_IDLE_ANIMATION, reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"hony_mushroom_move.spr") == 0)
			ResourceManager::GetInstance()->Put(HORN_MURSHROOM_MOVE_ANIMATION, reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"orange_mushroom_move.spr") == 0)
			ResourceManager::GetInstance()->Put(ORANGE_MURSHROOM_MOVE_ANIMATION, reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"pig_move.spr") == 0)
			ResourceManager::GetInstance()->Put(PIG_MOVE_ANIMATION, reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"dice_one.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_DICE_ONE_ANIMATION, reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"dice_two.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_DICE_TWO_ANIMATION, reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"dice_three.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_DICE_THREE_ANIMATION, reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"dice_four.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_DICE_FOUR_ANIMATION, reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"dice_five.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_DICE_FIVE_ANIMATION, reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"dice_six.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_DICE_SIX_ANIMATION, reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		lac->SetLoadFilename(filename);
		lac->Add(percent);
		Sleep(50);
	}


	for (int i = 0; i < spriteVector.size(); i++)
	{
		WCHAR loadPath[1000] = L"";
		WCHAR fullPath[1000] = L"";
		WCHAR* filename = spriteVector[i];
		wstrconcat(fullPath, const_cast<WCHAR*>(rootSpPathjList[loadscene]), filename);
		_wfullpath(loadPath, fullPath, _MAX_PATH);

		if (wcscmp(filename, L"onepickHouse.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_ONEPICK_HOUSE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"onepickHotel.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_ONEPICK_HOTEL, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"twopickHouse.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_TWOPICK_HOUSE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"twopickHotel.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_TWOPICK_HOTEL, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"threepickHouse.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_THREEPICK_HOUSE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"threepickHotel.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_THREEPICK_HOTEL, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"fourpickHouse.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_FOURPICK_HOUSE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"fourpickHotel.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_FOURPICK_HOTEL, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"diceOne.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_ONE_DICE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"diceTwo.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_TWO_DICE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"diceThree.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_THREE_DICE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"diceFour.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_FOUR_DICE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"diceFive.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_FIVE_DICE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"diceSix.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_SIX_DICE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"diceSeven.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_SEVEN_DICE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"diceEight.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_EIGHT_DICE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"diceNine.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_NINE_DICE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"diceTen.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_TEN_DICE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"diceEleven.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_ELEVEN_DICE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"diceTwoelve.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_TWELVE_DICE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"buttonPress.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_DICE_BTN_PRESS_SPRITE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"buttonPressUp.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_DICE_BTN_PRESS_UP_SPRITE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"marker.spr") == 0)
			ResourceManager::GetInstance()->Put(GAME_DICE_BTN_PRESS_UP_SPRITE, reinterpret_cast<Sprite*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		lac->SetLoadFilename(filename);
		lac->Add(percent);
		Sleep(50);
	}
	lac->Flush();
	return 0;
}

void wstrconcat(WCHAR* _ret, WCHAR* _str1, WCHAR* _str2)
{
	int len1 = wcslen(_str1);
	int index = 0;
	for (index = 0; index < len1; index++)
		_ret[index] = _str1[index];

	int len2 = wcslen(_str2);
	for (int j = 0; j < len2; j++)
		_ret[index + j] = _str2[j];
}
