#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buffer[4096];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("[]\n");
        return 0;
    }
    
    printf("[");
    char *token = strtok(buffer, " \t\r\n");
    int first = 1;
    while (token != NULL) {
        if (!first) {
            printf(", ");
        }
        printf("'%s'", token);
        first = 0;
        token = strtok(NULL, " \t\r\n");
    }
    printf("]\n");
    
    return 0;
}