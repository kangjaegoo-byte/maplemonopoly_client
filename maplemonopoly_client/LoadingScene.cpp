#include "pch.h"
#include "LoadingScene.h"
#include "ResourceManager.h"
#include "Bitmap.h"
#include "MaplemonopolyApp.h"
#include "Sound.h"
const int LoadingBarWidht = 395;
unsigned int _stdcall LaodProc(void* Args);
void wstrconcat(WCHAR* _ret, WCHAR* _str1, WCHAR* _str2);

LoadingScene::LoadingScene(Scenetype _loading) : Scene(Scenetype::LOADING_SCENE), m_loadSceneType(_loading)
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

	unsigned int theradId = ThreadId::LOAD;
	_beginthreadex(NULL, 0, &LaodProc, this, 0, &theradId);
}

void LoadingScene::Update()
{
	
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
	ResourceManager::GetInstance()->Delete(LOADING_BACKGROUND_BITMAP);
}

void LoadingScene::MouseMoveEvent(int _x, int _y)
{
}

void LoadingScene::MouseClickEnvet(int _x, int _y)
{
}

void LoadingScene::CharEvent(WPARAM _key)
{
}

void LoadingScene::Add(int _percent)
{
	m_percent += _percent;
}

void LoadingScene::Flush()
{
	m_percent = LoadingBarWidht;
}

unsigned int _stdcall LaodProc(void* Args)
{
	LoadingScene* lac = reinterpret_cast<LoadingScene*>(Args);

	std::vector<WCHAR*> bitmapPathVector;
	std::vector<WCHAR*> soundPathVector;
	std::vector<WCHAR*> animationVector;

	const WCHAR* bitmapPathList[] = { L"",L"..\\imgpack\\login\\*",L"..\\imgpack\\lobby\\*",L"..\\imgpack\\game\\*"};
	const WCHAR* soundPathList[] = { L"",L"..\\soundpack\\login\\*",L"..\\soundpack\\lobby\\*",L"..\\soundpack\\game\\*"};
	const WCHAR* animationPathList[] = { L"",L"",L"..\\animation\\lobby\\*",L"..\\animation\\game\\*"};

	const WCHAR* rootBPathList[] = { L"",L"..\\imgpack\\login\\", L"..\\imgpack\\lobby\\",L"..\\imgpack\\game\\"};
	const WCHAR* rootSPathList[] = { L"",L"..\\soundpack\\login\\", L"..\\soundpack\\lobby\\",L"..\\imgpack\\game\\"};
	const WCHAR* rootAPathList[] = { L"",L"", L"..\\animation\\lobby\\",L"..\\animation\\game\\"};

	Scenetype loadscene = lac->GetLoadSceneType();

	ResourceManager::GetInstance()->GetFileList(bitmapPathVector, bitmapPathList[loadscene]);
	ResourceManager::GetInstance()->GetFileList(soundPathVector, soundPathList[loadscene]);
	ResourceManager::GetInstance()->GetFileList(animationVector, animationPathList[loadscene]);

	const int totalDataCount = bitmapPathVector.size() + soundPathVector.size() + animationVector.size();

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
			ResourceManager::GetInstance()->Put(HORNY_MURSHROOM_BITMAP, bitmap);

		if (wcscmp(filename, L"orange_mushroom.png") == 0)
			ResourceManager::GetInstance()->Put(ORANGE_MURSHROOM_BITMAP, bitmap);

		if (wcscmp(filename, L"pig.png") == 0)
			ResourceManager::GetInstance()->Put(PIG_BITMAP, bitmap);

		if (wcscmp(filename, L"game.png") == 0)
			ResourceManager::GetInstance()->Put(GAME_BACKGROUND_BITMAP, bitmap);

		if (wcscmp(filename, L"board.png") == 0)
			ResourceManager::GetInstance()->Put(GAME_BOARD_BITMAP, bitmap);

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
			ResourceManager::GetInstance()->Put(HORNY_MURSHROOM_IDLE_ANIMATION,reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));
	
		if (wcscmp(filename, L"orange_mushroom_idel.spr") == 0)
			ResourceManager::GetInstance()->Put(ORANGE_MURSHROOM_IDLE_ANIMATION, reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		if (wcscmp(filename, L"pig_idel.spr") == 0)
			ResourceManager::GetInstance()->Put(PIG_IDLE_ANIMATION, reinterpret_cast<Animation*>(ResourceManager::GetInstance()->LoadBinaryData(loadPath)));

		lac->SetLoadFilename(filename);
		lac->Add(percent);
		Sleep(50);
	}

	lac->Flush();
	Sleep(1000);

	Network::GetInstance()->SendPacket((char*)&loadscene, CLIENT_NEXTSCENE_REQUEST, sizeof(Scenetype) + PACKET_HEADER_SIZE, 0);
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
