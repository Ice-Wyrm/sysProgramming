// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <process.h>
#include <string>
#include "dllmain.h"


HANDLE hPipe;

extern "C" _declspec(dllexport) void __stdcall Init()
{

}

extern "C" _declspec(dllexport) void __stdcall Cleanup()
{

}

extern "C" _declspec(dllexport) void __stdcall SendText(char* pStr)
{
	DWORD dwDone;
	int n = strlen(pStr) + 1;
	WriteFile(hPipe, &n, sizeof(n), &dwDone, NULL);
	WriteFile(hPipe, pStr, n, &dwDone, NULL);
	FlushFileBuffers(hPipe);  
}

extern "C" _declspec(dllexport) char* __stdcall GetText()
{
	DWORD dwDone;
	int n;
	
	ReadFile(hPipe, &n, sizeof(int), &dwDone, NULL);
	
	char* h = new char[n];
	ReadFile(hPipe, h, n, &dwDone, NULL);
	return h;
}


extern "C" _declspec(dllexport) void __stdcall SendInfo(int actionId)
{
	//Коды:
	//0: start
	//1: stop
	//2: send
	DWORD dwWrite;
	WriteFile(hPipe, &actionId, sizeof(int), &dwWrite, nullptr);
	FlushFileBuffers(hPipe);
}


extern "C" _declspec(dllexport) int __stdcall getAction()
{
	int action = 9;
	DWORD dwRead;
	ReadFile(hPipe, &action, sizeof(int), &dwRead, nullptr);

	return action;
}

extern "C" _declspec(dllexport) void _stdcall WorkWithClients()
{
	hPipe = CreateNamedPipe("\\\\.\\pipe\\MyPipe",
	PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES,
	1024, 1024, 0, NULL);
	ConnectNamedPipe(hPipe, NULL);
}

extern "C"	_declspec(dllexport) void _stdcall ConnectToServer() 
{
	if (WaitNamedPipe("\\\\.\\pipe\\MyPipe", 3000))
	{
		hPipe = CreateFile("\\\\.\\pipe\\MyPipe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	}
}

extern "C"	_declspec(dllexport) void _stdcall Disconnect()
{
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
}

extern "C" _declspec(dllexport) inline int _stdcall Response()
{
	while (true) {
		int response = getAction();
		if (response != 0) {
			return response;
		}
	}
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}