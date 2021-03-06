// dllmain.cpp: определяет точку входа для приложения DLL.
#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <thread>
#include <chrono>
#pragma warning(disable : 4996)
using namespace std;

struct sharedData  //Структура для отображения в память
{
	bool isrunning;
	int count;
};

sharedData* datash = NULL;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	
	
	switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
	
		setlocale(LC_ALL, "Russian");

		HANDLE hMapping; //Ссылка на обЪект отображения

		hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(sharedData), L"mymem"); //Создем обЪект отображения в память
		if (!hMapping)
		{
			cout << "Ошибка открытия обьекта отображения в память\n";
			return 0;
		}
		datash = (sharedData*)MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0); //Создаем вид файла
		
	}
	case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
