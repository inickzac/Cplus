
#define proc1   
//#define proc2 
#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#pragma warning(disable : 4996)

using  namespace std;


int main()
{


	int t;
	setlocale(LC_ALL,"Russian");
	
	HANDLE hMapping; //Ссылка на обЪект отображения
	HANDLE hMutex; //Ссылка на обЬект мютекса
	
	char MappingName[] = "Mychannel";
	struct sharedData  //Структура для отображения в память
	{
		char procName[10];
		int data;
	} ;
	
	sharedData* datash=NULL;
	
	
	hMutex =CreateMutex(NULL, false, "mymutex");  //Создаем обЪект мютекса
	if (hMutex == NULL)
	{
		cout << "Ошибка создания мютекса " << GetLastError();
		return 0;
	}

	hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL,  PAGE_READWRITE, 0, sizeof(sharedData),MappingName); //Создем обЪект отображения в память
	if (!hMapping)
	{
		cout << "Ошибка открытия обьекта отображения в память\n";
		return 0;
	}
	datash = (sharedData*)MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0); //Создаем вид файла
	
   //-------------------------------Код родительского процесса--------------------------------------------

#ifdef proc1  
	cout << "Родительский процесс\n";
	datash->data = 0;
	
	STARTUPINFO si = {0};
	PROCESS_INFORMATION piApp = { 0 };

	if (!CreateProcess("D://kr1 op2.exe", NULL, NULL, NULL, false, NULL, NULL, NULL, &si, &piApp)) //Создаем новый процесс

	{
		cout << "Ошибка запуска процесса\n";
		cout << "Код ошибки ";
	    cout<< GetLastError();
	}
	
	
	WaitForSingleObject(hMutex, INFINITE); //Блокируем или ожидаем мьютекс
	for (int i = 0; i < 10; i++)
	{		//Обработка и вывод 
		datash->data += 10;
		strcpy(datash->procName, "proc1");
		cout << datash->data << "-" << datash->procName << " ";		
		this_thread::sleep_for(chrono::milliseconds(150));
	}
	cout << "\n";
	ReleaseMutex(hMutex); //Освобождаем мьютекс
	WaitForSingleObject(piApp.hProcess, INFINITE); //Ждем завершения дочернего процесса
	  //Освобождаем ресурсы
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	CloseHandle(hMutex);
	cin >> t;


#endif  


	//-------------------------------------------Код дочернего процесса----------------------------------------

#ifdef proc2
	
	WaitForSingleObject(hMutex, INFINITE); //Блокируем или ожидаем мьютекс
	cout << "Дочерний процесс\n";
	for (int i = 0; i < 10; i++)
	{	
		//Обработка и вывод
		datash->data -= 10;
		strcpy(datash->procName, "proc2");
		cout << datash->data << "-" << datash->procName <<" " ;
		this_thread::sleep_for(chrono::milliseconds(100));			
}
	
	ReleaseMutex(hMutex); //Освобождаем мьютекс
	CloseHandle(hMutex); //Освобождаем ресурсы
	return 0;
#endif 

}