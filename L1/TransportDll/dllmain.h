#pragma once

struct header {
	int size;
	int threadNum;
};

extern "C" _declspec(dllexport) void __stdcall Init();
void Cleanup();
extern "C" _declspec(dllexport) void __stdcall SendText(char* pStr, int threadNum);
extern "C" _declspec(dllexport) void __stdcall SendInfo(int actionId);
extern "C" _declspec(dllexport) int __stdcall getAction(HANDLE & hInfo);
extern "C" _declspec(dllexport) char* __stdcall GetText(header & messageHeader, HANDLE & hReadMessage);