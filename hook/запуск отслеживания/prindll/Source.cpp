#include <windows.h> 
#include <iostream>
using namespace std;
HOOKPROC hkprc;

int main()
{

	HMODULE Hlib = LoadLibrary("d://os/ipr2/Dll1.dll"); //Подключаем библиотеку
	if (Hlib == NULL)
	{
		cout << "Невозможно открыть dll";
	}


	hkprc = (HOOKPROC)GetProcAddress(Hlib, "_GetMsgProc@12");  //Извлекаем функцию из библиотеки 
	if (hkprc == NULL)
	{
		cout << "Ошибка извлечения dll ";
	}

	HHOOK hook = SetWindowsHookEx(WH_CBT, hkprc, Hlib, 0); //Инициализируем хук для отслеживания запуска процесса
	


	struct sharedData  //Структура для отображения в память
	{
		bool isrunning;
		int count;
	};

	sharedData* datash = NULL;

	setlocale(LC_ALL, "Russian");

	HANDLE hMapping; //Ссылка на обЪект отображения

	hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(sharedData), "mymem"); //Создем обЪект отображения в память
	if (!hMapping)
	{
		cout << "Ошибка открытия обьекта отображения в память\n";
		return 0;
	}
	datash = (sharedData*)MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0); //Создаем вид файла
	datash->isrunning = false;
	datash->count = 0;
	int count = 0;
	cout << "Отслеживание процесса D:\\ipr1.exe \n";
	while (true)
	{	
		
		if (count != datash->count)  //Отслеживаем состояние процессов по общей памяти
		{
			if (datash->isrunning) { cout << "Отслеживаемая программа запущена \n "; }

			cout << "Кол-во запущеных программ " << datash->count <<"\n";
			count = datash->count;
		}
		
		
	}
}