// L1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "L1.h"
#include <vector>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CRITICAL_SECTION cs;

HANDLE hMutex;
HANDLE hEventStop;
HANDLE hEventStart;
HANDLE hEventConfirm;
HANDLE hEventQuit;

DWORD hSignal;

vector<HANDLE> hEvents;
vector<HANDLE> hThreads;


DWORD WINAPI newThread(LPVOID lpParameter)
{
	int ID = (int)lpParameter;
	WaitForSingleObject(hMutex, INFINITE);
	cout << "Thread " << ID << " created" << endl;
	ReleaseMutex(hMutex);
	SetEvent(hEventConfirm);

	
	WaitForSingleObject(hEvents[ID], INFINITE);
	WaitForSingleObject(hMutex, INFINITE);
	cout << "Thread " << ID << " done" << endl;
	ReleaseMutex(hMutex);
	SetEvent(hEventConfirm);

	return 0;
}

void start()
{

	hMutex = CreateMutex(NULL, FALSE, "MyMutex");
	hEventStop = CreateEvent(NULL, TRUE, FALSE, "eventStop");
	hEventStart = CreateEvent(NULL, TRUE, FALSE, "eventStart");
	hEventConfirm = CreateEvent(NULL, TRUE, FALSE, "eventConfirm");
	hEventQuit = CreateEvent(NULL, TRUE, FALSE, "eventQuit");

	HANDLE hPossibleEvents[3] = {hEventStart, hEventStop, hEventQuit};

	int k = 0;
	

	while (true)
	{
		hSignal = WaitForMultipleObjects(3, hPossibleEvents, FALSE, INFINITE);
		switch ((int)hSignal - (int)WAIT_OBJECT_0) {
		case 0: {
			hThreads.push_back(CreateThread(NULL, 0, newThread, (LPVOID)k, 0, NULL));
			hEvents.push_back(CreateEvent(NULL, FALSE, FALSE, NULL));
			k++;
			break;
		}
		case 1: {
			SetEvent(hEvents[hEvents.size() - 1]);
			hEvents.pop_back();
			k--;

			break;
		}
		case 2: {
			SetEvent(hEventConfirm);
			return;
			break;
		}
		}

	}
	
	

	CloseHandle(hMutex);

	cout << "all done" << endl;
}

// The one and only application object

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: code your application's behavior here.
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {
            start();
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

    return nRetCode;
}
