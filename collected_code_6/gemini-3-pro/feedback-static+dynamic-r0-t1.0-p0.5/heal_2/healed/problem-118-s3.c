#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char *line = NULL;
    size_t len = 0;
    
    if (getline(&line, &len, stdin) == -1) {
        free(line);
        return 0;
    }
    
    printf("[");
    int first = 1;
    char *p = line;
    
    while (*p) {
        while (*p && isspace((unsigned char)*p)) {
            p++;
        }
        if (!*p) {
            break;
        }
        
        char *start = p;
        while (*p && !isspace((unsigned char)*p)) {
            p++;
        }
        
        if (!first) {
            printf(", ");
        }
        
        printf("'");
        for (char *c = start; c < p; c++) {
            putchar(*c);
        }
        printf("'");
        
        first = 0;
    }
    printf("]\n");
    
    free(line);
    return 0;
}