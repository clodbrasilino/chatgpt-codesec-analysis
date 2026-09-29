#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_even_chars(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t read_idx = 0;
    size_t write_idx = 0;
    size_t len = strlen(str);
    
    while (read_idx < len) {
        if (read_idx % 2 == 0) {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }
    str[write_idx] = '\0';
}

int main(void) {
    char *buffer = malloc(256 * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter a string (max 255 characters): ");
    if (fgets(buffer, 256, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    remove_even_chars(buffer);
    printf("Result: %s\n", buffer);
    
    free(buffer);
    return EXIT_SUCCESS;
}