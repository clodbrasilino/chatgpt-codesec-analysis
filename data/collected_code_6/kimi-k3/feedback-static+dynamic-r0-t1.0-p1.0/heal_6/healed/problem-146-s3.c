#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int calculate_ascii_sum(const char *str, size_t max_len) {
    int sum = 0;
    size_t i;
    size_t len;
    
    if (str == NULL) {
        return -1;
    }
    
    len = strnlen(str, max_len);
    
    for (i = 0; i < len; i++) {
        sum += (int)(unsigned char)str[i];
    }
    
    return sum;
}

int main(void) {
    char *input = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read;
    int result;
    
    printf("Enter a string: ");
    
    bytes_read = getline(&input, &buffer_size, stdin);
    
    if (bytes_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }
    
    if (bytes_read > 0 && input[bytes_read - 1] == '\n') {
        input[bytes_read - 1] = '\0';
        bytes_read--;
    }
    
    result = calculate_ascii_sum(input, (size_t)bytes_read + 1);
    
    if (result == -1) {
        fprintf(stderr, "Error: Invalid string\n");
        free(input);
        return 1;
    }
    
    printf("Total ASCII value: %d\n", result);
    
    free(input);
    return 0;
}