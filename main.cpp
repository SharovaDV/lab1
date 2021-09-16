#include <iostream>
#include <stdio.h>
#include <windows.h>

#define INFO_BUFFER_SIZE 32767
#define MAX_DATA_LENGTH 255
using namespace std;

int main()
{
//1.1
   OSVERSIONINFO os_ver = {0};
    os_ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    GetVersionEx(&os_ver);

    printf("Version is %d.%d (%d)\n",
                os_ver.dwMajorVersion,
                os_ver.dwMinorVersion,
                os_ver.dwBuildNumber);
//1.2
    TCHAR infoBuffer[INFO_BUFFER_SIZE];
    DWORD bufferCharCount = INFO_BUFFER_SIZE;

    GetSystemDirectory(infoBuffer, INFO_BUFFER_SIZE);

    printf("System directory: %s \n", infoBuffer);

//1.3
    bufferCharCount = INFO_BUFFER_SIZE;
    GetComputerName(infoBuffer, &bufferCharCount);

    printf("Computer name: %s\n", infoBuffer );

    bufferCharCount = INFO_BUFFER_SIZE;
    GetUserName(infoBuffer, &bufferCharCount);

    printf("User name: %s\n", infoBuffer );

//1.4
    TCHAR buffer[MAX_PATH];
    DWORD  cchBufferLength = MAX_PATH;
    TCHAR Names[MAX_PATH];
    ULARGE_INTEGER total, free;

    HANDLE search = FindFirstVolume(buffer, sizeof(buffer));

    do {
        GetVolumePathNamesForVolumeName(buffer, Names, cchBufferLength, &cchBufferLength);
        printf("\n%s", Names);
        printf("\n%s", buffer);

        if (GetDiskFreeSpaceEx(Names,&total,&free,NULL)==0)
        {
            printf("\nNo information\n ");
        }
        else
        {
        printf("\n  Total size:%lld bytes", total.QuadPart);
        printf("\n  Free space:%lld bytes\n", free.QuadPart); << free.QuadPart << " bytes";
        }   
  } 
    while (FindNextVolume(search, buffer, sizeof(buffer)));
    FindVolumeClose(search);
//1.5
     HKEY Key;
    DWORD dwIndex = 0;
    TCHAR tcValue[MAX_PATH] = { 0 };
    TCHAR lpValueName[MAX_DATA_LENGTH];
    DWORD lpcchValueName = MAX_DATA_LENGTH;
    DWORD lpDataLength = MAX_DATA_LENGTH;

 if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,
    KEY_ALL_ACCESS, &Key)== ERROR_SUCCESS)
        {
            while (RegEnumValue(Key, dwIndex, lpValueName, &lpcchValueName, NULL, REG_NONE, NULL, NULL) == ERROR_SUCCESS)
            {
                lpcchValueName = sizeof(lpValueName);
                RegQueryValueEx(Key, lpValueName, NULL, REG_NONE, (LPBYTE)tcValue, &lpDataLength);
            cout << "Program : \n" << dwIndex+1 << " ";
            wcout << lpValueName;
            cout << " ";
            wcout << tcValue;
            cout << " " << "\n";
            dwIndex++;
            }
   
    RegCloseKey(hKey);
//2
    LARGE_INTEGER freq;
    LARGE_INTEGER t1;
    LARGE_INTEGER t2;

    QueryPerformanceCounter(&t1);
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&t2);

    double tact = t2.QuadPart - t1.QuadPart;
    double frequency = freq.QuadPart;;
    double us = 1000000 * tact / frequency;

    printf("Frequency = %u Hz\n",  freq);
    printf("clock = %f us\n",  us);

}
