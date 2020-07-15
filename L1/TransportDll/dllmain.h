#pragma once

struct header {
	int size;
	int threadNum;
};

extern "C" _declspec(dllexport) void __stdcall Init();
extern "C" _declspec(dllexport) void __stdcall Cleanup();
extern "C" _declspec(dllexport) void __stdcall SendText(char* pStr);
extern "C" _declspec(dllexport) void __stdcall SendInfo(int actionId);
extern "C" _declspec(dllexport) int __stdcall getAction();
extern "C" _declspec(dllexport) char* __stdcall GetText();
extern "C" _declspec(dllexport) void _stdcall WorkWithClients();
extern "C" _declspec(dllexport) inline int _stdcall Response();