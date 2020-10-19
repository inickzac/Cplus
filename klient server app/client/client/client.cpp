
#pragma comment(lib,"Ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#pragma warning(disable:4996) 
#include <sstream>

int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "rus");
	WSAData wsData;
	WORD Version = MAKEWORD(2, 1);
	if (WSAStartup(Version, &wsData) != 0)
	{
		std::cout << "Ошибка загрузки библиотеки" << std::endl;
		exit(1);
	}
	SOCKADDR_IN adress;
	adress.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	adress.sin_port = htons(1111);
	adress.sin_family = AF_INET;
	SOCKET Connect = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connect, (SOCKADDR*)& adress, sizeof(adress)) != 0)
	{
		std::cout << "Не удалось подключится к серверу" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Успешное подключение к серверу" << std::endl;
	}
	while (true)
	{
		char request[256];
		char answer[256];
		for (int i = 0; i < 256; i++) { answer[i] = ' '; }	
		recv(Connect, answer, sizeof(answer), NULL);						
		std::cout << answer << std::endl;
		std::cin >> request;
		send(Connect, request, sizeof(request), NULL);				
	}
}