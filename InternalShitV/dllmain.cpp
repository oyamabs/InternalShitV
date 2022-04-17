// dllmain.cpp : Définit le point d'entrée de l'application DLL.
#include "pch.h"
#include <iostream>

DWORD WINAPI HackThread(HMODULE hModule) {
    // creating console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Internal shit test\n";
    
    uintptr_t* tmpAmmo = (uintptr_t*)0x23E53398498;

    while (true) {
        if (GetAsyncKeyState(VK_END) & 1)
            break;
        
        if (GetAsyncKeyState(VK_LEFT) & 1)
            *tmpAmmo = 2;
        if (GetAsyncKeyState(VK_RIGHT) & 1)
            *tmpAmmo = 9999;

        // do something lol
    }
    
    FreeConsole();
    fclose(f);
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // avant
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
        
        










        // après
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

