#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <winbase.h>



int main(void) {
    printf("Enter a directory to be watched\n");
    char dir[1024];
    fgets(dir, sizeof(dir), stdin);
    dir[strlen(dir) - 1] = '\0';
    HANDLE file = FindFirstChangeNotificationA(dir, TRUE, FILE_NOTIFY_CHANGE_FILE_NAME);
    if (file == INVALID_HANDLE_VALUE){
        DWORD error = GetLastError();
        return error;
    }
    printf("Iniciace %s byla uspesne udelana\n", dir);
    while (true){
        DWORD hitter = WaitForSingleObject(file, INFINITE);
        if (hitter == WAIT_OBJECT_0) {
            printf("The hitter was hitted\n");
            FindNextChangeNotification(file);
        }
    }
    return 0;
}
