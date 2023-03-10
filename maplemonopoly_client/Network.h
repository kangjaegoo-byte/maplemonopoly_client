#pragma once
/**************************************************
	Network : 서버와 통신하는 인터페이스입니다.
**************************************************/
class Network
{
private:
	static Network*		m_instance;
	WSADATA				m_wsaData;
	SOCKET				m_connectSocket;
	SOCKADDR_IN			m_sockAddr;
	unsigned int		m_recvThreadId = ThreadId::RECV;

public:
	static Network*		GetInstance();
	bool				Init();
	bool				Connect();
	static unsigned int RecvPacketProc(void* Args);		// Recv 처리 위임 인터페이스
	void				RecvPakcet();					// Recv 처리 
	void				SendPacket(char* _buffer, int _type, int _size, int _dataCnt);
};

