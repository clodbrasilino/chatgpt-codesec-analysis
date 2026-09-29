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
    size_t buffer_size = 256;
    char *buffer = malloc(buffer_size);
    
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter a string: ");
    
    if (fgets(buffer, buffer_size, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }
    
    size_t len = strnlen(buffer, buffer_size);
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == buffer_size - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    remove_spaces(buffer);
    
    printf("Result: %s\n", buffer);
    
    free(buffer);
    
    return 0;
}