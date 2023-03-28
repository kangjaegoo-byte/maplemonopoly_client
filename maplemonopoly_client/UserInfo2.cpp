#include "pch.h"
#include "UserInfo2.h"
#include "D2D1Core.h"
#include "UserPickView.h"
#include "StaticText.h"
#include "User.h"
#include "ResourceManager.h"
#include "Bitmap.h"
#include "ResourceManager.h"
UserInfo2::UserInfo2(int _x, int _y, int _width, int _height, bool _focused, ID2D1SolidColorBrush* _brush, IDWriteTextFormat* _textForamt, int _playerNumber) : UIComponent(_x, _y, _width, _height, _focused), m_blackBrush(_brush), m_textformat(_textForamt), m_playerNumber(_playerNumber)
{
    Init();
}

UserInfo2::~UserInfo2()
{
    delete m_pickView;
    delete m_usernameText;
    delete m_moneyText;
    delete m_rankText;
}

void UserInfo2::Init()
{
    m_pickView = new UserPickView(736,15, 55, 55, false, NOUSER);
    m_usernameText = new StaticText(618, 15, 100, 15, false, m_blackBrush, m_textformat);
    m_moneyText = new StaticText(618, 40, 100, 60, false, m_blackBrush, m_textformat);
    m_rankText = new StaticText(567, 18, 31, 33, false, m_blackBrush, m_textformat);
}

void UserInfo2::Update(WPARAM _key)
{

}

void UserInfo2::Render()
{
    if (m_visiable == false) return;

    Bitmap* bitmap = nullptr;

    switch (m_playerNumber)
    {
    case 0:
        bitmap = ResourceManager::GetInstance()->GetBitmap(USERINFO1_BITMAP);
        break;

    case 1:
        bitmap = ResourceManager::GetInstance()->GetBitmap(USERINFO2_BITMAP);
        break;

    case 2:
        bitmap = ResourceManager::GetInstance()->GetBitmap(USERINFO3_BITMAP);
        break;

    case 3:
        bitmap = ResourceManager::GetInstance()->GetBitmap(USERINFO4_BITMAP);
        break;
    }

    D2D1Core::GetInstance()->GetCRT()->DrawBitmap(bitmap->GetBitmap(), D2D1_RECT_F{ (FLOAT)m_x, (FLOAT)m_y, (FLOAT)m_width + m_x, (FLOAT)m_height + m_y }, m_opacity ? 0.5f : 1.0f);
    m_opacity ? m_pickView->ORender() : m_pickView->Render();
    m_usernameText->Render();
    m_moneyText->Render();

    if (m_rankText)
        m_rankText->RankRender();

}

bool UserInfo2::ISFocus(int _x, int _y)
{
    return false;
}

void UserInfo2::Init(User& _dt)
{
    m_pickView->Refresh(static_cast<Pick>(_dt.GetPick()));
    m_visiable = true;
    m_usernameText->SetText(_dt.GetUsername(), wcslen(_dt.GetUsername()) * 2);
    m_moneyText->SetText(100);
    m_userId = _dt.GetUserId();
}

void UserInfo2::SetMoney(int _money)
{
    m_moneyText->SetText(_money);
}
