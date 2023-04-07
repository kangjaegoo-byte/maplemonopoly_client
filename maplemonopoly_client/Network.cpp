#include "pch.h"
#include "Network.h"
#include "SceneManager.h"
#include "GameService.h"
Network* Network::m_instance = nullptr;

Network* Network::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new Network();
	return m_instance;
}

bool Network::Init()
{
	if (WSAStartup(MAKEWORD(2, 2), &m_wsaData) != 0)
		return false;

	m_connectSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_connectSocket == INVALID_SOCKET)
		return false;

	memset(&m_sockAddr, 0, sizeof(m_sockAddr));
	m_sockAddr.sin_family = AF_INET;
	inet_pton(AF_INET, IPADDRESS, &m_sockAddr.sin_addr);
	m_sockAddr.sin_port = htons(PORT);

	return true;
}

bool Network::Connect()
{
	if (connect(m_connectSocket, (SOCKADDR*)&m_sockAddr, sizeof(m_sockAddr)) == SOCKET_ERROR)
		return false;

	_beginthreadex(NULL, 0, &RecvPacketProc, nullptr, 0, &m_recvThreadId);
}

unsigned int Network::RecvPacketProc(void* Args)
{
	Network::GetInstance()->RecvPakcet();
	return 0;
}

void Network::RecvPakcet()
{
	char recvBuffer[1000];
	int recvedSize = 0;

	while (true)
	{
		int recvSize = recv(m_connectSocket, recvBuffer + recvedSize, sizeof(recvBuffer) - recvedSize, 0);

		if (recvSize <= 0)
			break;

		recvedSize += recvSize;

		while (recvedSize >= 2)
		{

			WORD* header = (WORD*)recvBuffer;
			int packetSize = *header;

			if (recvedSize < packetSize)
				break;

			recvedSize -= packetSize;

			GameService::GetInstance()->Recv(recvBuffer);

			if (recvedSize > 0)
				::memcpy(recvBuffer, recvBuffer + packetSize, recvedSize);
		}
	}
}

void Network::SendPacket(char* _buffer, int _type, int _size, int _dataCnt)
{
	Packet packet;
	memset(&packet, 0, sizeof(packet));
	packet._size = _size + PACKET_HEADER_SIZE;
	packet._cnt = _dataCnt;
	packet._type = _type;
	if (_buffer != nullptr)
		memcpy(packet._data, _buffer, _size);
	::send(m_connectSocket, (char*)&packet, packet._size, 0);
}

void Network::Send(char* buffer, int size)
{
	::send(m_connectSocket, buffer, size, 0);
}
