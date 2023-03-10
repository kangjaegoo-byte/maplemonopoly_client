#include "pch.h"
#include "UserDTO.h"

UserDTO::UserDTO(WCHAR* _username, Location _location) : m_location(_location)
{
	wcscpy_s(m_username, _username);	
}

UserDTO::UserDTO(int _userid, WCHAR* _username, Location _location) : m_location(_location), m_userId(_userid)
{
	wcscpy_s(m_username, _username);
}

UserDTO::UserDTO(const UserDTO& _copy)
{
	wcscpy_s(m_username, _copy.m_username);
	m_sung = _copy.m_sung;
	m_location = _copy.m_location;
	m_userId = _copy.m_userId;
}

UserDTO::~UserDTO()
{

}
