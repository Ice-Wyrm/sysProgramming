#pragma once

struct header {
	int size;
	int threadNum;
};

extern "C" {
	__declspec(dllexport) void _stdcall sendTextToMMF(char* message, int thread);
	__declspec(dllexport) char* _stdcall readTextFromMMF(header& messageInfo);
}