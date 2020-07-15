// L1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "L1.h"
#include <vector>
#include "TransportDll/dllmain.h"
#include <fstream>
#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CRITICAL_SECTION cs;

string message;

HANDLE hMutex;
HANDLE hEventStop;
HANDLE hEventStart;
HANDLE hEventConfirm;
HANDLE hEventQuit;
HANDLE hEventMessageSent;
HANDLE mFile;


HANDLE hInfo = GetStdHandle(STD_ERROR_HANDLE);
HANDLE hRead = GetStdHandle(STD_INPUT_HANDLE);

DWORD hSignal;


vector<HANDLE> hEvents;
vector<HANDLE> hThreads;

DWORD WINAPI newThread(LPVOID lpParameter)
{
	int ID = (int)lpParameter;
	WaitForSingleObject(hMutex, INFINITE);
	cout << "Thread " << ID << " created" << endl;
	ReleaseMutex(hMutex);

	WaitForSingleObject(hEvents[ID], INFINITE);
	WaitForSingleObject(hMutex, INFINITE);
	cout << "Thread " << ID << " done" << endl;
	ReleaseMutex(hMutex);

	return 0;
}

UINT __cdecl newAfxThread(LPVOID lpParameter)
{
	int ID = (int)lpParameter;
	WaitForSingleObject(hMutex, INFINITE);
	cout << "Thread " << ID << " created" << endl;
	ReleaseMutex(hMutex);

	WaitForSingleObject(hEvents[ID], INFINITE);
	WaitForSingleObject(hMutex, INFINITE);
	cout << "Thread " << ID << " done" << endl;
	ReleaseMutex(hMutex);

	return 0;
}

void messageToFile(string filename)
{
	ofstream fout(filename);
	fout << message;
	fout.close();
}

UINT __cdecl messageOutput(LPVOID threadNumFromMessage)
{
	int threadNum = (int)threadNumFromMessage;
	if (threadNum == -1) {
		cout << "Message arrived to main thread" << endl;
		cout << message << endl;
	} else {
		cout << "Message arrived to " + to_string(threadNum) + " thread" << endl;
		messageToFile("Thread" + to_string(threadNum) + ".txt");
	}

	return 0;
}

void start()
{

	hMutex = CreateMutex(NULL, FALSE, "MyMutex");
	int k = 0;

	while (true)
	{
		int action = getAction(hInfo);
		switch (action) {
		case 0: {
			//hThreads.push_back(CreateThread(NULL, 0, newThread, (LPVOID)k, 0, NULL));
			hThreads.push_back(AfxBeginThread(newAfxThread, (LPVOID)k, 0, 0, 0, 0));
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
			header messageHeader;
			message = GetText(messageHeader, hRead);

			//int threadNum = messageHeader.threadNum - 2;
			int threadNum = messageHeader.threadNum - 2;
			if (threadNum == -2) {
				AfxBeginThread(messageOutput, (LPVOID)(-1), 0, 0, 0, 0);
				for (int i = 0; i < hThreads.size(); i++) {
					AfxBeginThread(messageOutput, (LPVOID)i, 0, 0, 0, 0);
				}
			}
			else {
				AfxBeginThread(messageOutput, (LPVOID)(threadNum), 0, 0, 0, 0);
				SetEvent(hEventConfirm);
			}
			break;
		}
		case 3: {
			return;
			break;
		}
		}

	}

	CloseHandle(hRead);
	CloseHandle(hInfo);
	CloseHandle(hMutex);
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
