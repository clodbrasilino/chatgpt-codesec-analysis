#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_odd_rotations(const char *str, size_t len) {
    int count = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '1') {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    char *input = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read;
    
    printf("Enter a binary string: ");
    bytes_read = getline(&input, &buffer_size, stdin);
    
    if (bytes_read == -1) {
        free(input);
        return 1;
    }
    
    if (bytes_read > 0 && input[bytes_read - 1] == '\n') {
        input[bytes_read - 1] = '\0';
        bytes_read--;
    }
    
    if (bytes_read == 0) {
        printf("Error: Empty input\n");
        free(input);
        return 1;
    }
    
    if (bytes_read > 256) {
        printf("Error: Input too long\n");
        free(input);
        return 1;
    }
    
    for (ssize_t i = 0; i < bytes_read; i++) {
        if (input[i] != '0' && input[i] != '1') {
            printf("Error: Invalid binary string\n");
            free(input);
            return 1;
        }
    }
    
    int result = count_odd_rotations(input, (size_t)bytes_read);
    printf("Count of odd rotations: %d\n", result);
    
    free(input);
    return 0;
}