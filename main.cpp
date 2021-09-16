#include <iostream>
#include <stdio.h>
#include <windows.h>

#define INFO_BUFFER_SIZE 32767
#define MAX_KEY_LENGTH 255
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
        cout << " Total size: " << total.QuadPart << " bytes" << "\nFree space: " << free.QuadPart << " bytes";
        }   
  } 
    while (FindNextVolume(search, buffer, sizeof(buffer)));
    FindVolumeClose(search);
//1.5
 HKEY     DWORD dwSize;
    TCHAR szName[MAX_KEY_LENGTH];
    HKEY hKey;
    DWORD dwIndex = 0;
    DWORD retCode;
    DWORD BufferSize = 8192;
    PPERF_DATA_BLOCK PerfData = (PPERF_DATA_BLOCK)malloc(BufferSize);
    DWORD cbData = BufferSize;

    if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        0, KEY_ALL_ACCESS, &hKey) == !ERROR_SUCCESS)
    {
        cout << "Function RegOpenKeyEx() failed!" << endl;
    }
    else cout << "\n1.5.  Startup commands:" << endl;

    while (1) {
        dwSize = sizeof(szName);
        retCode = RegEnumValue(hKey, dwIndex, szName, &dwSize, NULL, NULL, NULL, NULL);
        if (retCode == ERROR_SUCCESS)
        {
            RegQueryValueEx(hKey, szName, NULL, NULL, (LPBYTE)PerfData, &cbData);
            printf("      %d: %s:  %s\n", dwIndex + 1, szName, PerfData);
            dwIndex++;
        }
        else break;
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
