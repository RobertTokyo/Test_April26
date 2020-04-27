#include "CommandHTTP.h"
#include <sstream>
#include<iostream>
#include <ws2tcpip.h>
#include <cassert>

CommandHTTP::CommandHTTP()
{
#ifdef WINDOWS
	WSADATA wsaData;

	int startupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (startupResult != 0)
		throw std::exception("Can't start socket layer");
#elif LINUX
#endif
}

CommandHTTP::CommandHTTP(const std::string& req)
	: Request(req)
{
#ifdef WINDOWS
	WSADATA wsaData;

	int startupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (startupResult != 0)
		throw std::exception("Can't start socket layer");
#elif
#ifdef LINUX
#endif
#endif
}

std::string CommandHTTP::get(const std::string& url)
{
	if (!Request.setRequest(url))
		throw std::exception("Invalid URL");

	return get();
}

std::string CommandHTTP::get()
{
	std::string source = "";
	char buffer[1024];
						
	if (makeConnection())
	{
		std::stringstream ss;
		ss << "GET /" << Request.getReqPath() << " HTTP/1.0\r\n";
		ss << "HOST: ip2c.org\r\n\r\n";
		std::string req = ss.str();
		int bytesSent = send(sock, req.c_str(), (int)req.length(), 0); // send out a fake message and store the byte size

		int  i = 0;
		do
		{
			memset(buffer, 0, 1024);
			i = recv(sock, buffer, sizeof(buffer), 0); // receive data from server (buffer size 1024)
			source += buffer;
		} while (i != 0);
		closesocket(sock);
	}
	size_t index = source.find("\r\n\r\n");
	if (index != std::string::npos)
		source = source.substr(index + 4);
	return source;
}

bool getAddressFromDomain(const std::string& host, const std::string& port)
{
	struct addrinfo *result = NULL;
	struct addrinfo *ptr = NULL;
	struct addrinfo hints;
#ifdef WINDOWS
	ZeroMemory(&hints, sizeof(hints));
#elif LINUX

#endif
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	bool GotAddress{ false };
	DWORD dwRetval = getaddrinfo(host.c_str(), port.c_str(), &hints, &result);
	if (dwRetval != 0) {
	}
	else
		GotAddress = true;

	return GotAddress;
}

bool CommandHTTP::makeConnection()
{	
	bool Connected{ false };
	std::string Host = Request.getHost();
	int port = Request.getPort();
	if (Host.length() > 0)
	{
		sock = socket(AF_INET, SOCK_STREAM, 0);

		int connectResult{ -1 };
		SOCKADDR_IN socketAddr;
		std::string DQHost{ Host };
		if (!isdigit(DQHost[0]))
		{
			hostent* hostname = gethostbyname(Host.c_str());
			if (hostname)
				DQHost = std::string(inet_ntoa(**(in_addr**)hostname->h_addr_list));
		}
		socketAddr.sin_addr.s_addr = inet_addr(DQHost.c_str()); // Start Address in dotted quad
		socketAddr.sin_family = AF_INET;
		socketAddr.sin_port = htons(Request.getPort());
		connectResult = connect(sock, (SOCKADDR *)&socketAddr, sizeof(socketAddr));
				
		if (connectResult == 0)
			Connected = true;
		else
		{
#ifdef WINDOWS
			DWORD dwErr = GetLastError();
			LPVOID lpMsgBuf;
			DWORD bufLen = FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				dwErr,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&lpMsgBuf,
				0, NULL);
			if (bufLen)
			{
				LPCTSTR lpMsgStr = (LPCTSTR)lpMsgBuf;
				std::wcout << lpMsgStr << std::endl;

				LocalFree(lpMsgBuf);
			}
#elif LINUX

#endif 
		}
	}
	return Connected;
}

