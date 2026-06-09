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
    HANDLE openDirectory = CreateFileW(dir, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    // HANDLE file = FindFirstChangeNotificationA(dir, TRUE, FILE_NOTIFY_CHANGE_FILE_NAME); //Create a handler to change the specific part of it
    BOOL directoryChanges = ReadDirectoryChanges(file, );
    
    printf("Iniciace %s byla uspesne udelana\n", dir);
    while (true){
        DWORD hitter = WaitForSingleObject(file, INFINITE);
        if (hitter == WAIT_OBJECT_0) {
            printf("The hitter was hitted\n");
            printf("%s byl nalezen\n", file);
            FindNextChangeNotification(file);
        }
    }
    return 0;
}
