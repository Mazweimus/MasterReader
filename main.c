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

    LPCWSTR dir[1024];
    printf("Enter a directory to be watched\n");
    fgets(dir, sizeof(dir), stdin);
    dir[strlen(dir) - 1] = '\0';
    HANDLE openDirectory = CreateFileW(dir, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);
    BYTE buffer[4096]; // kdyz je to pole, tak je to vzdy pointer na ten prvni prvek
    DWORD dwBufferReturn = 0;
    OVERLAPPED ov = {0};
    ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL); // manual reset event
    while (true) {
        BOOL directoryChanges = ReadDirectoryChangesW(openDirectory, buffer, sizeof(buffer), TRUE, FILE_NOTIFY_CHANGE_LAST_WRITE, &dwBufferReturn, NULL, NULL);
        if (directoryChanges == 0) {
            printf("Nezdarilo se");
        } else {
            printf("Neco se znemnio");
        }
    }
}
