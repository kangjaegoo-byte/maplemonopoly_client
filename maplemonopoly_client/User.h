#pragma once
class User
{
private:
	unsigned int m_userId = 0;
	unsigned int m_roomSq = 0;
	bool		 m_ready = false;
	WCHAR		 m_username[15] = L"";
	Location     m_location = Location::LOBBY_ROOM;
	Pick		 m_pick = HORN_MURSHROOM;
public:
	WCHAR* GetUsername() { return m_username; }
	Location GetLocation() { return m_location; }
	int      GetUserId() { return m_userId; }
	int      GetRoomSq() { return m_roomSq; }

	void     SetUsername(WCHAR* _username) { wcscpy_s(m_username, _username); }
	void	 SetLocation(Location _location) { m_location = _location; }
	void     SetUserID(int _id) { m_userId = _id; }
	void	 SetRoomSq(int _roomSq) { m_roomSq = _roomSq; }
	Pick	 GetPick() { return m_pick; }
	void	 SetPick(Pick _pick) { m_pick = _pick; }
	bool	 GetReady() { return m_ready; }
};

