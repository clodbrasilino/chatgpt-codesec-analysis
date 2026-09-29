#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *line = NULL;
    size_t capacity = 0;
    ssize_t len;

    len = getline(&line, &capacity, stdin);
    if (len == -1) {
        free(line);
        return 0;
    }

    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }

    printf("[");
    int first = 1;
    char *token = strtok(line, " \t\r\n");
    
    while (token != NULL) {
        if (!first) {
            printf(", ");
        }
        printf("'%s'", token);
        first = 0;
        token = strtok(NULL, " \t\r\n");
    }
    
    printf("]\n");

    free(line);
    return 0;
}