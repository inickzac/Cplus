
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
	
	HANDLE hMapping; //������ �� ������ �����������
	HANDLE hMutex; //������ �� ������ �������
	
	char MappingName[] = "Mychannel";
	struct sharedData  //��������� ��� ����������� � ������
	{
		char procName[10];
		int data;
	} ;
	
	sharedData* datash=NULL;
	
	
	hMutex =CreateMutex(NULL, false, "mymutex");  //������� ������ �������
	if (hMutex == NULL)
	{
		cout << "������ �������� ������� " << GetLastError();
		return 0;
	}

	hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL,  PAGE_READWRITE, 0, sizeof(sharedData),MappingName); //������ ������ ����������� � ������
	if (!hMapping)
	{
		cout << "������ �������� ������� ����������� � ������\n";
		return 0;
	}
	datash = (sharedData*)MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0); //������� ��� �����
	
   //-------------------------------��� ������������� ��������--------------------------------------------

#ifdef proc1  
	cout << "������������ �������\n";
	datash->data = 0;
	
	STARTUPINFO si = {0};
	PROCESS_INFORMATION piApp = { 0 };

	if (!CreateProcess("D://kr1 op2.exe", NULL, NULL, NULL, false, NULL, NULL, NULL, &si, &piApp)) //������� ����� �������

	{
		cout << "������ ������� ��������\n";
		cout << "��� ������ ";
	    cout<< GetLastError();
	}
	
	
	WaitForSingleObject(hMutex, INFINITE); //��������� ��� ������� �������
	for (int i = 0; i < 10; i++)
	{		//��������� � ����� 
		datash->data += 10;
		strcpy(datash->procName, "proc1");
		cout << datash->data << "-" << datash->procName << " ";		
		this_thread::sleep_for(chrono::milliseconds(150));
	}
	cout << "\n";
	ReleaseMutex(hMutex); //����������� �������
	WaitForSingleObject(piApp.hProcess, INFINITE); //���� ���������� ��������� ��������
	  //����������� �������
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	CloseHandle(hMutex);
	cin >> t;


#endif  


	//-------------------------------------------��� ��������� ��������----------------------------------------

#ifdef proc2
	
	WaitForSingleObject(hMutex, INFINITE); //��������� ��� ������� �������
	cout << "�������� �������\n";
	for (int i = 0; i < 10; i++)
	{	
		//��������� � �����
		datash->data -= 10;
		strcpy(datash->procName, "proc2");
		cout << datash->data << "-" << datash->procName <<" " ;
		this_thread::sleep_for(chrono::milliseconds(100));			
}
	
	ReleaseMutex(hMutex); //����������� �������
	CloseHandle(hMutex); //����������� �������
	return 0;
#endif 

}