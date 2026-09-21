#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int contains_z(const char *word) {
    if (word == NULL) {
        return 0;
    }
    while (*word != '\0') {
        if (*word == 'z') {
            return 1;
        }
        word++;
    }
    return 0;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t length;

    length = getline(&buffer, &buffer_size, stdin);
    
    if (length != -1) {
        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        }
        
        if (contains_z(buffer)) {
            printf("Match found\n");
        } else {
            printf("No match\n");
        }
        
        free(buffer);
    }
    
    return 0;
}