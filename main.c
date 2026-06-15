#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <winbase.h>



int main(void) {

    #ifndef _WIN32 || _WIN64
        printf("Tento system nelze provozovat z duvodu nepodporovaneho systemu\n");
        return -1;
    #endif

    char dir[1024];
    printf("Enter a directory to be watched\n");
    fgets(dir, sizeof(dir), stdin);
    dir[strlen(dir) - 1] = '\0';
    HANDLE openDirectory = CreateFileW(dir, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
    LPVOID buffer[4096];
    LPVOID *lpBuffer = &buffer;
    DWORD dwBufferReturn = 0;
    while (true) {
        BOOL directoryChanges = ReadDirectoryChangesW(openDirectory, buffer, sizeof(lpBuffer), TRUE, FILE_NOTIFY_CHANGE_LAST_WRITE, &dwBufferReturn, NULL, NULL);
        if (directoryChanges == 0) {
            printf("Nezdarilo se");
        } else {
            printf("Neco se znemnio");
        }
    }
}
