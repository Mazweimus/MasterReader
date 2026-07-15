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
    wprintf(L"Enter a directory to be watched\n");
    if(fgetws(memoryDir, 1024, stdin)==NULL) {
        wprintf(L"Couldn't read memory directory\n");
        return 1;
    }
    memoryDir[wcslen(memoryDir) - 1] = '\0';
    HANDLE openDirectory = CreateFileW(dir, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);
    if (openDirectory == INVALID_HANDLE_VALUE) {
        wprintf(L"Couldn't open memory directory\n");
        return 1;
    }
    BYTE buffer[4096]; // kdyz je to pole, tak je to vzdy pointer na ten prvni prvek
    DWORD dwBufferReturn = 0;
    OVERLAPPED ov = {0};
    ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL); // manual reset event
    ReadDirectoryChangesW(openDirectory, buffer, sizeof(buffer), TRUE, FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_CREATION, &dwBufferReturn, &ov, NULL);
    while (true) {
        ResetEvent(ov.hEvent);
        printf("We are seeking for any changes\n");
        DWORD wait = WaitForSingleObject(ov.hEvent, INFINITE);
        if (wait == WAIT_OBJECT_0) {
            GetOverlappedResult(openDirectory, &ov, &dwBufferReturn, TRUE);
            FILE_NOTIFY_INFORMATION *fni = (FILE_NOTIFY_INFORMATION *)buffer;
            if (fni->Action == FILE_ACTION_ADDED) {
                printf("Added file\n");
            } else if (fni->Action == FILE_ACTION_REMOVED) {
                printf("File removed\n");
            } else if (fni->Action == FILE_ACTION_RENAMED_NEW_NAME) {
                printf("Name renamed\n");
            } else if (fni->Action == FILE_ACTION_MODIFIED) {
                printf("Change was spotted\n");
            }
        }
        ReadDirectoryChangesW(openDirectory, buffer, sizeof(buffer), TRUE, FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_CREATION, &dwBufferReturn, &ov, NULL);
    }
}
