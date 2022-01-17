#include <windows.h>
#include "functions.h"

int main() {

    /*                                  VARS                                                          */

    DWORD procId = GetProcId(L"ac_client.exe"); // get Process Id
    uintptr_t moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe"); // get modulebaseaddr

    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

    uintptr_t dynamicPtrBaseAddr = moduleBase + 0 + 0x10f4f4;

    // Health

    std::vector<unsigned int> healthOffsets{0xF8};
    uintptr_t healthAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, healthOffsets);

    // Zoom 

    std::vector<unsigned int> zoomOffsets{0x80};
    uintptr_t zoomAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, zoomOffsets);

    // Recoil

    std::vector<unsigned int> recoilOffsets{0x384,0xc,0x122};
    uintptr_t recoilAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, recoilOffsets);



    unsigned int newHealth = 9999;
    unsigned int newZoomON = 20;
    unsigned int newZoomOff = 0;
    unsigned int recoilOff = 0;
    unsigned int recoilOn = 50;

    // main 

    while (true)
    {
        system("cls");

        unsigned int userin;

        std::cout <<

            "Enter Option  \t\t\t\tAssault Cube Script: Made by noodl\n\n"
            "1: Ammo 9999\n"
            "2: Avaliable Ammo 9999\n"
            "3: Health 9999\n"
            "4: ZOOM (On, W To stop)\n"
            "5: Recoil Off\n"
            "6: Recoil On\n"
            ": ";


        std::cin >> userin;

        if (userin == 1)
        {
            std::vector<unsigned int> ammoOffsets{ 0x384,0x14,0x0 };
            uintptr_t ammoAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);

            unsigned int newAmmo = 9999;

            WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);

        }

        if (userin == 2)
        {
            std::vector<unsigned int> avaliableammoOffsets{ 0x384,0x10,0x0 };
            uintptr_t avaliableammoAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, avaliableammoOffsets);

            unsigned int newavaliableammo = 9999;

            WriteProcessMemory(hProcess, (BYTE*)avaliableammoAddr, &newavaliableammo, sizeof(newavaliableammo), nullptr);

        }

        if (userin == 3)
        {

            WriteProcessMemory(hProcess, (BYTE*)healthAddr, &newHealth, sizeof(newHealth), nullptr);

        }

        if (userin == 4)
        {

            WriteProcessMemory(hProcess, (BYTE*)zoomAddr, &newZoomON, sizeof(newZoomON), nullptr);

        }
        if (userin == 5)
        {

            WriteProcessMemory(hProcess, (BYTE*)recoilAddr, &recoilOff, sizeof(recoilOff), nullptr);

        }
        if (userin == 6)
        {

            WriteProcessMemory(hProcess, (BYTE*)recoilAddr, &recoilOn, sizeof(recoilOn), nullptr);

        }
        
    }

   
    return EXIT_SUCCESS;
}