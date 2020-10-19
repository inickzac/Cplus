#include <windows.h> 
#include <iostream>
using namespace std;
HOOKPROC hkprc;

int main()
{

	HMODULE Hlib = LoadLibrary("d://os/ipr2/Dll1.dll"); //���������� ����������
	if (Hlib == NULL)
	{
		cout << "���������� ������� dll";
	}


	hkprc = (HOOKPROC)GetProcAddress(Hlib, "_GetMsgProc@12");  //��������� ������� �� ���������� 
	if (hkprc == NULL)
	{
		cout << "������ ���������� dll ";
	}

	HHOOK hook = SetWindowsHookEx(WH_CBT, hkprc, Hlib, 0); //�������������� ��� ��� ������������ ������� ��������
	


	struct sharedData  //��������� ��� ����������� � ������
	{
		bool isrunning;
		int count;
	};

	sharedData* datash = NULL;

	setlocale(LC_ALL, "Russian");

	HANDLE hMapping; //������ �� ������ �����������

	hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(sharedData), "mymem"); //������ ������ ����������� � ������
	if (!hMapping)
	{
		cout << "������ �������� ������� ����������� � ������\n";
		return 0;
	}
	datash = (sharedData*)MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0); //������� ��� �����
	datash->isrunning = false;
	datash->count = 0;
	int count = 0;
	cout << "������������ �������� D:\\ipr1.exe \n";
	while (true)
	{	
		
		if (count != datash->count)  //����������� ��������� ��������� �� ����� ������
		{
			if (datash->isrunning) { cout << "������������� ��������� �������� \n "; }

			cout << "���-�� ��������� �������� " << datash->count <<"\n";
			count = datash->count;
		}
		
		
	}
}