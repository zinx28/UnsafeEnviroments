#include "framework.h"
#include "./public/main.h"

/*
    TODO:
        switch between minhook and veh hooking
        find the best way to patch environments, haven't had time yet
*/

DWORD WINAPI Main(LPVOID) { Main::Init(); return 0; }

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, Main, 0, 0, 0);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

