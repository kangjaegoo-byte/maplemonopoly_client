#pragma once
class Network
{
private:
	static Network* m_instance;
	WSADATA				m_wsaData;
	SOCKET				m_connectSocket;
	SOCKADDR_IN			m_sockAddr;
	unsigned int		m_recvThreadId = Threadid::RECV;

public:
	static Network*		GetInstance();
	bool				Init();
	bool				Connect();
	static unsigned int RecvPacketProc(void* Args);		// Recv ó�� ���� �������̽�
	void				RecvPakcet();					// Recv ó�� 
	void				SendPacket(char* _buffer, int _type, int _size, int _dataCnt);
	void				Send(char* buffer, int size);
};

