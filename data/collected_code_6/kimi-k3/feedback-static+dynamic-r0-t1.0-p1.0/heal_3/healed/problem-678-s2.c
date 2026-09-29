#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

bool remove_spaces(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return false;
    }
    
    size_t read_idx = 0;
    size_t write_idx = 0;
    size_t len = strnlen(str, max_len);
    
    if (len == max_len) {
        return false;
    }
    
    while (read_idx < len) {
        if (str[read_idx] != ' ') {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }
    
    str[write_idx] = '\0';
    return true;
}

int main(void) {
    char buffer[BUFFER_SIZE];
    
    printf("Enter a string: ");
    
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(buffer, BUFFER_SIZE);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    if (!remove_spaces(buffer, BUFFER_SIZE)) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }
    
    printf("Result: %s\n", buffer);
    
    return EXIT_SUCCESS;
}