#include "pch.h"
#include "GameUserInfoUI.h"
#include "D2D1Core.h"
#include "UserPickView.h"
#include "StaticText.h"
#include "UserDTO.h"
GameUserInfoUI::GameUserInfoUI(int _x, int _y, int _width, int _height, bool _focused, ID2D1SolidColorBrush* _brush, ID2D1SolidColorBrush* _out, ID2D1SolidColorBrush* _black, IDWriteTextFormat* _textForamt) : UIComponent(_x, _y, _width, _height, _focused), m_brushFill(_brush), m_brushOut(_out), m_blackBrush(_black), m_textformat(_textForamt)
{
    Init();
}

GameUserInfoUI::~GameUserInfoUI()
{
    delete m_pickView;
}

void GameUserInfoUI::Init()
{
    m_pickView = new UserPickView(m_x, m_y, 72, 72, false, NOUSER);
    m_usernameText = new StaticText(m_x+72, m_y, m_width,30, false, m_blackBrush, m_textformat);
    m_moneyRect = D2D1_RECT_F { m_x + 72.0f, m_y + 30.0f, m_width + 0.0f + m_x, m_height +0.0f + m_y };
}

void GameUserInfoUI::Update(WPARAM _key)
{

}

void GameUserInfoUI::Render()
{
    if (m_visiable == false) return;

    D2D1Core::GetInstance()->GetCRT()->FillRectangle(D2D1_RECT_F{ (FLOAT)m_x, (FLOAT)m_y, (FLOAT)m_width + m_x, (FLOAT)m_height + m_y }, m_brushFill);
    D2D1Core::GetInstance()->GetCRT()->FillRectangle(m_moneyRect, m_brushOut);
    D2D1Core::GetInstance()->GetCRT()->DrawRectangle(D2D1_RECT_F{ (FLOAT)m_x, (FLOAT)m_y, (FLOAT)m_width + m_x, (FLOAT)m_height + m_y }, m_brushOut);
    m_pickView->Render();
    m_usernameText->Render();
}

bool GameUserInfoUI::ISFocus(int _x, int _y)
{
    return false;
}

void GameUserInfoUI::Init(UserDTO& _dt)
{
    m_pickView->Refresh(static_cast<CPick>(_dt.GetPick()));
    m_visiable = true;
    m_usernameText->SetText(_dt.GetUsername(), wcslen(_dt.GetUsername()) * 2);
    m_userId = _dt.GetUserId();
}
