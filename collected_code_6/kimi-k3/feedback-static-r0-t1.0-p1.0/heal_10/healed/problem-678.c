#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>

void remove_spaces(char *str) {
    if (str == NULL) {
        return;
    }
    
    char *read_ptr = str;
    char *write_ptr = str;
    
    while (*read_ptr != '\0') {
        if (!isspace((unsigned char)*read_ptr)) {
            *write_ptr = *read_ptr;
            write_ptr++;
        }
        read_ptr++;
    }
    *write_ptr = '\0';
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read;
    
    errno = 0;
    bytes_read = getline(&buffer, &buffer_size, stdin);
    
    if (bytes_read == -1) {
        free(buffer);
        return 0;
    }
    
    if (bytes_read > 0 && buffer[bytes_read - 1] == '\n') {
        buffer[bytes_read - 1] = '\0';
    }
    
    remove_spaces(buffer);
    printf("%s\n", buffer);
    
    free(buffer);
    return 0;
}