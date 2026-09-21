#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;

    if (getline(&buffer, &bufsize, stdin) == -1) {
        printf("[]\n");
        free(buffer);
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
    
    free(buffer);
    return 0;
}