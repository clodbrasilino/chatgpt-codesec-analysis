#include <stdio.h>
#include <stdlib.h>

int max_difference(const char *binary_string, size_t length) {
    int max_diff = 0;
    int current_diff = 0;
    
    for (size_t i = 0; i < length; i++) {
        if (binary_string[i] == '0') {
            current_diff++;
        } else if (binary_string[i] == '1') {
            current_diff--;
        } else {
            return -1;
        }
        
        if (current_diff > max_diff) {
            max_diff = current_diff;
        }
        
        if (current_diff < 0) {
            current_diff = 0;
        }
    }
    
    return max_diff;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    const char *input = argv[1];
    size_t len = 0;
    
    while (input[len] != '\0') {
        len++;
        if (len == 0) {
            fprintf(stderr, "Error: Input string exceeds maximum length.\n");
            return EXIT_FAILURE;
        }
    }
    
    if (len == 0) {
        fprintf(stderr, "Error: Input string cannot be empty.\n");
        return EXIT_FAILURE;
    }
    
    int result = max_difference(input, len);
    
    if (result < 0) {
        fprintf(stderr, "Error: Input string contains invalid characters.\n");
        return EXIT_FAILURE;
    }
    
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}