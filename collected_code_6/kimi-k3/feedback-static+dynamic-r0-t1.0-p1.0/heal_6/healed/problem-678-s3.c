#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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
    ssize_t chars_read;
    
    printf("Enter a string: ");
    
    chars_read = getline(&buffer, &buffer_size, stdin);
    
    if (chars_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }
    
    if (chars_read > 0 && buffer[chars_read - 1] == '\n') {
        buffer[chars_read - 1] = '\0';
    }
    
    remove_spaces(buffer);
    
    printf("Result: %s\n", buffer);
    
    free(buffer);
    
    return 0;
}