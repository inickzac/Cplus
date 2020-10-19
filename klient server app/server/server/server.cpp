 #include <winsock2.h>
 #include <iostream>
#pragma comment(lib,"Ws2_32.lib")
#pragma warning(disable:4996) 
#include <string>
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
	SOCKET listen_s = socket(AF_INET, SOCK_STREAM, NULL);
	bind(listen_s, (sockaddr*)& adress, sizeof(adress));
	while (true)
	{
		std::cout << "Ожидание соединения" << std::endl;
		listen(listen_s, SOMAXCONN);
		int size_SockAddr = sizeof(adress);
		SOCKET newConnect = accept(listen_s, (sockaddr*)& adress, &size_SockAddr);
		if (newConnect != 0) {
			std::cout << "Клиент присоединен" << std::endl;
		}
		else
		{
			std::cout << "Ошибка соединения" << std::endl;
			return 2;
		}

		char MessageMass[2][256];
		for (int i = 0; i < 2; i++)
		{						
			std::string request_str = "Введите строку " + std::to_string(i + 1);
			char* request = (char*)request_str.data();	
			send(newConnect, request, strlen(request)+1, NULL);									
			recv(newConnect, MessageMass[i], sizeof(MessageMass[i]), NULL);							
			if (MessageMass[i][0]=='\0') { 
				i--;
				std::cout << "Введена пустая строка введите еще раз" << std::endl; }
		}
		char* occur = strstr(MessageMass[0], MessageMass[1]);	
		if (occur == NULL) occur = (char*)"Вхождения не обнаруженны";
		else {
			char nstr[256] = "Строка начинающая с найденной строки ";
			occur= strcat(nstr, occur);
		}
	
		send(newConnect, occur, strlen(occur) + 1, NULL);
		closesocket(newConnect);
	}
	
		
}
