#include <stdio.h>
#include <stdbool.h>
#include <string.h>


int main(void) {
    while (true) {
        char interface[1024];
        printf("Vas dotaz\n");
        fgets(interface, sizeof(interface), stdin);
        interface[strlen(interface) - 1] = '\0';
        if (strcmp(interface, "q") == 0) {
            break;
        }
    }
    return 0;
}
