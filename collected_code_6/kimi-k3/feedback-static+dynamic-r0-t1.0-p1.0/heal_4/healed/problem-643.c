#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>

bool contains_z_not_at_edges(const char *word, size_t len) {
    if (word == NULL || len < 3) {
        return false;
    }
    
    for (size_t i = 1; i < len - 1; i++) {
        if (word[i] == 'z' || word[i] == 'Z') {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read;
    
    read = getline(&buffer, &buffer_size, stdin);
    
    if (read != -1 && buffer != NULL) {
        size_t len = (size_t)read;
        
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        
        if (contains_z_not_at_edges(buffer, len)) {
            printf("Match\n");
        } else {
            printf("No match\n");
        }
        
        free(buffer);
    }
    
    return 0;
}