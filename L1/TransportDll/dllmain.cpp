// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <process.h>
#include <string>
#include "dllmain.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;

}

HANDLE hMutexDll;
LPVOID fileView;

void init() 
{
	hMutexDll = CreateMutex(NULL, FALSE, "MyMutex");
}

void end()
{
	CloseHandle(hMutexDll);
}

extern "C" __declspec(dllexport) void _stdcall sendTextToMMF(char* message, int thread)
{
	header fileInfo;
	fileInfo.size = strlen(message) + 1;
	fileInfo.threadNum = thread;

	init();
	WaitForSingleObject(hMutexDll, INFINITE);
	HANDLE fileMapping = CreateFileMapping(NULL, NULL, PAGE_READWRITE, 0, sizeof(header) + fileInfo.size, "messageFile");
	BYTE* pBuff = (BYTE*)MapViewOfFile(fileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, sizeof(header) + fileInfo.size);

	memcpy(pBuff, &fileInfo, sizeof(header));
	memcpy(pBuff + sizeof(header), message, fileInfo.size);

	ReleaseMutex(hMutexDll);
	end();
}

extern "C" __declspec(dllexport) char* _stdcall readTextFromMMF(header& messageInfo)
{
	init();
	WaitForSingleObject(hMutexDll, INFINITE);
	HANDLE fileMapping = CreateFileMapping(NULL, NULL, PAGE_READWRITE, 0, sizeof(header), "messageFile");
	BYTE* pBuff = (BYTE*)MapViewOfFile(fileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, sizeof(header));

	memcpy(&messageInfo, pBuff, sizeof(header));

	UnmapViewOfFile(pBuff);
	CloseHandle(fileMapping);

	fileMapping = CreateFileMapping(NULL, NULL, PAGE_READWRITE, 0, sizeof(header) + messageInfo.size, "messageFile");
	pBuff = (BYTE*)MapViewOfFile(fileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, sizeof(header) + messageInfo.size);

	char* message = new char[messageInfo.size];
	memcpy(message, pBuff + sizeof(header), messageInfo.size);

	UnmapViewOfFile(pBuff);
	CloseHandle(fileMapping);
	
	ReleaseMutex(hMutexDll);
	end();
	return message;
}
