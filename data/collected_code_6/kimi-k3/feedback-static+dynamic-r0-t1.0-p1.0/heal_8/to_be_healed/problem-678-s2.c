#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

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
            if (write_idx >= max_len - 1) {
                return false;
            }
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }
    
    str[write_idx] = '\0';
    return true;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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