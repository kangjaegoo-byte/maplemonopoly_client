#include "pch.h"
#include "LoginScene.h"
#include "ResourceManager.h"
#include "Bitmap.h"
#include "Sound.h"
#include "UIComponent.h"
#include "InputEditor.h"
#include "Button.h"
#include "AlertModal.h"
#include "UserDTO.h"
#include "MaplemonopolyApp.h"
LoginScene::LoginScene() : Scene(LOADING_SCENE)
{
	Init();
}

LoginScene::~LoginScene()
{
	Clean();
}

void LoginScene::Init()
{
	m_crt = D2D1Core::GetInstance()->GetCRT();
	m_rt = D2D1Core::GetInstance()->GetRT();
	D2D1Core::GetInstance()->SetFontFormat(&m_textFormat, L"나눔고딕", 12);
	D2D1Core::GetInstance()->CreateColorBrush(&m_whiteBrush, D2D1::ColorF::White);
	m_bgm = ResourceManager::GetInstance()->GetSound(LOGIN_BGM);
	m_bgm->Playing(true);
	m_uiVector.resize(LOGIN_UI_COUNT, nullptr);

	m_uiVector[LOGIN_INPUT] = new InputEditor(438, 234, 148, 22, 10, true, m_whiteBrush, m_textFormat);
	m_uiVector[LOGIN_BUTTON] = new Button(604,243,74,34,false);
	m_uiVector[LOGIN_ALERTMODAL] = new AlertModal(300,180,300,250,false,L"닉네임을 다시 확인해주세요 닉네임은 공백제외 10자리 미만입니다.", m_whiteBrush, m_textFormat);
}

void LoginScene::Update()
{
	if (m_uiVector[LOGIN_BUTTON]) 
	{
		Button* loginButton = reinterpret_cast<Button*> (m_uiVector[LOGIN_BUTTON]);
		if (loginButton->GetClicked())
		{
			InputEditor* loginText = reinterpret_cast<InputEditor*> (m_uiVector[LOGIN_INPUT]);
			
			if (loginText->Validation() == false)
				reinterpret_cast<AlertModal*> (m_uiVector[LOGIN_ALERTMODAL])->Show();
			else
			{
				WCHAR* username = loginText->GetText();
				UserDTO* dto = new UserDTO(username, Location::LOBBY_ROOM);
				MaplemonopolyApp::GetInstance()->SetUserInfo(dto);
				Network::GetInstance()->SendPacket((char*)dto, CLIENT_LOGIN_PROCESS_REQUEST, sizeof(UserDTO) + PACKET_HEADER_SIZE, 1);
			}
		}
	}
}

void LoginScene::Render()
{
	m_crt->DrawBitmap(ResourceManager::GetInstance()->GetBitmap(LOGIN_BACKGROUND_BITMAP)->GetBitmap());
	for (int zindex = 0; zindex < LOGIN_UI_COUNT; zindex++)
	{
		auto uiItem = m_uiVector[zindex];
		if (uiItem)
			uiItem->Render();
	}
	
}

void LoginScene::Clean()
{
	m_textFormat->Release();
	m_whiteBrush->Release();
	ResourceManager::GetInstance()->Delete(LOGIN_ALERTMODAL_BITMAP);
	ResourceManager::GetInstance()->Delete(LOGIN_BACKGROUND_BITMAP);
	ResourceManager::GetInstance()->DeleteSound(LOGIN_BGM);
	for (int i = 0; i < LOGIN_UI_COUNT; i++)
		delete m_uiVector[i];
}

void LoginScene::MouseMoveEvent(int _x, int _y)
{
}

void LoginScene::MouseClickEnvet(int _x, int _y)
{
	for (int zindex = 0; zindex < LOGIN_UI_COUNT; zindex++)
	{
		auto uiItem = m_uiVector[zindex];
		if (uiItem)
			uiItem->ISFocus(_x, _y);
	}
}

void LoginScene::CharEvent(WPARAM _key)
{
	for (int zindex = 0; zindex < LOGIN_UI_COUNT; zindex++)
	{
		auto uiItem = m_uiVector[zindex];
		if (uiItem && uiItem->FocuseCheck())
			uiItem->Update(_key);
	}
}
