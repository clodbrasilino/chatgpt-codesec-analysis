#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t find_length(const char *str) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t len = getline(&buffer, &buffer_size, stdin);
    
    if (len == -1) {
        free(buffer);
        return 1;
    }
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len = find_length(buffer);
    }
    
    printf("Length: %zu\n", (size_t)len);
    free(buffer);
    return 0;
}