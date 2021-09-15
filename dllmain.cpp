// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

//Round 1
//Stage | 65 (h41)      | (0x00A08198) mgs2_sse.exe+608198
//O2    | 2600 (hF0 0A) | (0x0118AEBE) mgs2_sse.exe+D8AEBE
//
//Round 2
//Stage | 64 (h40)      | (0x00A08198) mgs2_sse.exe+608198
//O2    | 360 (h68 01)  | (0x0118AEBE) mgs2_sse.exe+D8AEBE

bool bWantsExit;

void mgs2_Solidus_Torture() {
    BYTE* StageID = (BYTE*)0x00A08198;
    BYTE* isCutscene = (BYTE*)0x00A15644;
    WORD* O2Value = (WORD*)0x0118AEBE;

    while (bWantsExit == false) {
        if (*StageID == 65) {
            if (*isCutscene == 0) {
                if (*O2Value > 0) {
                    if (*O2Value < 2600) {
                        *O2Value = 2600;
                        Sleep(100);
                    }
                }
            }
        }

        if (*StageID == 64) {
            if (*isCutscene == 0) {
                if (*O2Value > 0) {
                    if (*O2Value < 360) {
                        *O2Value = 360;
                        Sleep(100);
                    }
                }
            }
        }
    }
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  fdwReason, LPVOID lpReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        bWantsExit = false;
#if DEBUG
        MessageBox(0, L"Sucessfully loaded DLL. Will force O2 Value of \"2600\" for Round 1 and \"360\" for Round 2.", L"DLL Injector", MB_ICONEXCLAMATION | MB_OK);
#endif
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&mgs2_Solidus_Torture, NULL, 0, NULL);
    }

    if (fdwReason == DLL_PROCESS_DETACH) {
        bWantsExit = true;
#if DEBUG
        MessageBox(0, L"Successfully unloaded DLL. Thanks for testing.", L"DLL Injector", MB_ICONEXCLAMATION | MB_OK);
#endif
    }

    return TRUE;
}
