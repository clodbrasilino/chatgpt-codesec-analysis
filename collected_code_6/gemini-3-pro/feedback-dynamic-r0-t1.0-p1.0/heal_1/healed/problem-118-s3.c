#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buffer[1024];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    if (len > 1 && buffer[len - 2] == '\r') {
        buffer[len - 2] = '\0';
    }

    printf("[");
    
    char* token = strtok(buffer, " ");
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