#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

void remove_odd_chars(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return;
    }
    
    size_t read_idx = 0;
    size_t write_idx = 0;
    size_t len = strnlen(str, max_len);
    
    while (read_idx < len) {
        if (read_idx % 2 == 0) {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }
    if (write_idx < max_len) {
        str[write_idx] = '\0';
    }
}

int main(void) {
    char buffer[BUFFER_SIZE];
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    remove_odd_chars(buffer, sizeof(buffer));
    
    printf("Result: %s\n", buffer);
    
    return EXIT_SUCCESS;
}