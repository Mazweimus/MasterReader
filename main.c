#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <winbase.h>



int main(void) {

    #ifndef _WIN32
        #error "Tento system nelze provozovat z duvodu nepodporovaneho systemu"
    #endif

    wchar_t memoryDir[1024];
    LPCWSTR dir = memoryDir;
    printf("Enter a directory to be watched\n");
    fgetws(memoryDir, sizeof(memoryDir), stdin);
    memoryDir[wcslen(memoryDir) - 1] = '\0';
    HANDLE openDirectory = CreateFileW(dir, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);
    BYTE buffer[4096]; // kdyz je to pole, tak je to vzdy pointer na ten prvni prvek
    DWORD dwBufferReturn = 0;
    OVERLAPPED ov = {0};
    ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL); // manual reset event
    ReadDirectoryChangesW(openDirectory, buffer, sizeof(buffer), TRUE, FILE_NOTIFY_CHANGE_LAST_WRITE, &dwBufferReturn, &ov, NULL);
    while (true) {
        DWORD wait = WaitForSingleObject(ov.hEvent, INFINITE);
        if (wait == WAIT_OBJECT_0) {
            GetOverlappedResult(ov.hEvent, &ov, &dwBufferReturn, TRUE);
            ResetEvent(ov.hEvent);
            FILE_NOTIFY_INFORMATION *fni = (FILE_NOTIFY_INFORMATION *)buffer;
            if (fni->Action == FILE_ACTION_ADDED) {
                printf("Added file\n");
            } else if (fni->Action == FILE_ACTION_REMOVED) {
                printf("File removed\n");
            } else if (fni->Action == FILE_ACTION_MODIFIED) {
                printf("Change was spotted\n");
            } else if (fni->Action == FILE_ACTION_RENAMED_NEW_NAME) {
                printf("Name renamed\n");
            }
        }
    }
}
