// TransportDllMFC.cpp : Defines the initialization routines for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "TransportDllMFC.h"
#include <afxsock.h>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE hPipe;

CSocket Socket;
CSocket Server;


extern "C" _declspec(dllexport) void __stdcall Init()
{
	AfxSocketInit();
	Server.Create(5000);
}

extern "C" _declspec(dllexport) void __stdcall SendText(char* pStr)
{
	DWORD dwDone;
	int n = strlen(pStr) + 1;

	Socket.Send(&n, sizeof(int));
	Socket.Send(pStr, n);
}

extern "C" _declspec(dllexport) char* __stdcall GetText()
{
	DWORD dwDone;
	int n;

	Socket.Receive(&n, sizeof(int));

	char* h = new char[n];

	Socket.Receive(h, n);
	return h;
}


extern "C" _declspec(dllexport) void __stdcall SendInfo(int actionId)
{
	//Коды:
	//0: start
	//1: stop
	//2: send
	Socket.Send(&actionId, sizeof(int));
}


extern "C" _declspec(dllexport) int __stdcall getAction()
{
	int action = 9;
	Socket.Receive(&action, sizeof(int));

	return action;
}

extern "C" _declspec(dllexport) void __stdcall WorkWithClients()
{
	while (true)
	{
		if (!Server.Listen())
			break;
		Server.Accept(Socket);
	}
}


extern "C"	_declspec(dllexport) void __stdcall ListenForConnections()
{
	Server.Listen();
	Server.Accept(Socket);
}

extern "C"	_declspec(dllexport) bool __stdcall ConnectToServer()
{
	AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);
	AfxSocketInit();

	Socket.Create();

	return Socket.Connect(_T("127.0.0.1"), 5000);
}

extern "C"	_declspec(dllexport) void __stdcall Disconnect()
{
	Socket.Close();
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

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CTransportDllMFCApp

BEGIN_MESSAGE_MAP(CTransportDllMFCApp, CWinApp)
END_MESSAGE_MAP()


// CTransportDllMFCApp construction

CTransportDllMFCApp::CTransportDllMFCApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTransportDllMFCApp object

CTransportDllMFCApp theApp;


// CTransportDllMFCApp initialization

BOOL CTransportDllMFCApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	return TRUE;
}
