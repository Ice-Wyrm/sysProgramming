// TransportDllMFC.h : main header file for the TransportDllMFC DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

struct header {
	int size;
	int threadNum;
};

extern "C" _declspec(dllexport) void __stdcall ListenForConnections();
extern "C" _declspec(dllexport) void __stdcall Init();
extern "C" _declspec(dllexport) void __stdcall Cleanup();
extern "C" _declspec(dllexport) void __stdcall SendText(char* pStr);
extern "C" _declspec(dllexport) void __stdcall SendInfo(int actionId);
extern "C" _declspec(dllexport) int __stdcall getAction();
extern "C" _declspec(dllexport) char* __stdcall GetText();
extern "C" _declspec(dllexport) void __stdcall WorkWithClients();
extern "C" _declspec(dllexport) inline int __stdcall Response();
extern "C"	_declspec(dllexport) bool __stdcall ConnectToServer();


// CTransportDllMFCApp
// See TransportDllMFC.cpp for the implementation of this class
//

class CTransportDllMFCApp : public CWinApp
{
public:
	CTransportDllMFCApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
