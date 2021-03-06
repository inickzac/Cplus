// Dll1.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <psapi.h>
#include <string>


using namespace std;
bool isrunnig = 0;
DWORD oldpid;
STARTUPINFO si = { 0 };
PROCESS_INFORMATION piApp = { 0 };
HANDLE proc;

struct sharedData  //Структура для отображения в память
{
	bool isrunning;
	int count;
	
};

extern  sharedData* datash;

extern "C" _declspec(dllexport) LRESULT CALLBACK GetMsgProc(int code, WPARAM wParam, LPARAM lParam)  //Создаем извлекаемую функцию
{
	setlocale(LC_ALL, "Russian");
	
	if (code == HCBT_CREATEWND && !isrunnig) //Перехватываем создание окна процессом
	{
		//Определяем какой процесс создал окно
		DWORD pid = NULL;
		GetWindowThreadProcessId((HWND)wParam, &pid);
		char buff[MAX_PATH - 1] = "";
		proc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, pid); 
		GetModuleFileNameExA(proc, 0, buff, MAX_PATH);		
		
		//Если открылся нужный процесс то создаем новый процесс 
		if (!strcmp(buff, "D:\\ipr1.exe"))
		{
			datash->isrunning = true;
			datash->count++;			
			CreateProcess(L"D:\\Openprocess.exe", NULL, NULL, NULL, false, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp);
				isrunnig = true;	
		}
	
	}
	//Перехватываем уничтожение  окна процессом
	if (code == HCBT_DESTROYWND) 
	{
		DWORD pid = NULL;
		GetWindowThreadProcessId((HWND)wParam, &pid);
		//Определяем какой процесс убил окно	
			char buff[MAX_PATH - 1] = "";
			HANDLE proc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, pid);
			GetModuleFileNameExA(proc, 0, buff, MAX_PATH);
			//Если окно убил нужный процесс то убиваем новый процесс 
			if (!strcmp(buff, "D:\\ipr1.exe"))
			{
				if (pid != oldpid) {
					if (datash->count == 1) { datash->isrunning = false; }
					TerminateProcess(piApp.hProcess,0);
					datash->count--;
					oldpid = pid;
				
				}
			}
		
	}
	return CallNextHookEx(NULL, code, wParam, lParam); //Передаем управление следующим ловушкам
}

