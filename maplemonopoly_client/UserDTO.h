#pragma once
/**************************************************
	UserDTO : 사용자 정보 클래스
**************************************************/
class UserDTO
{
private:
	WCHAR    m_username[15] = L"";
	int		 m_userId = 0;
	int		 m_sung = 0;
	int		 m_pick = 0;
	WORD	 m_roomSq = 0;
	Location m_location = Location::LOBBY_ROOM;
public:
	UserDTO(WCHAR* _username, Location _location);
	UserDTO(int _userid, WCHAR* _username, Location _location);
	UserDTO() {};
	UserDTO(const UserDTO& _copy);
	~UserDTO();

	WCHAR*   GetUsername() { return m_username; }
	int	     GetSung() { return m_sung; }
	Location GetLocation() { return m_location; }
	int      GetUserId() { return m_userId; }
	void	 SetLocation(Location _location) { m_location = _location; }
	void	 SetRoomSq(WORD _sq) { m_roomSq = _sq; }
	int		 GetRoomSq() { return m_roomSq; }
	void	 SetUserPick(int _pick) { m_pick = _pick; }
	int		 GetPick() { return m_pick; }
};

