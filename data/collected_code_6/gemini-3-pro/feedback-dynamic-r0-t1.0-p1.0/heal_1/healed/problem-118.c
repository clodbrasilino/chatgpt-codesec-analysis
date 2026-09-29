#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char line[1024];
    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 0;
    }
    
    line[strcspn(line, "\r\n")] = '\0';
    
    printf("[");
    char *token = strtok(line, " ");
    int first = 1;
    while (token != NULL) {
        if (!first) {
            printf(", ");
        }
        printf("'%s'", token);
        first = 0;
        token = strtok(NULL, " ");
    }
    printf("]\n");
    
    return 0;
}