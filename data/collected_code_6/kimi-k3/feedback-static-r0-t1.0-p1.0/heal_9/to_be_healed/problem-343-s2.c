#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

void count_digits_letters(const char *str, size_t *digits, size_t *letters) {
    if (str == NULL || digits == NULL || letters == NULL) {
        return;
    }
    
    *digits = 0;
    *letters = 0;
    
    while (*str != '\0') {
        unsigned char c = (unsigned char)*str;
        if (isdigit(c)) {
            (*digits)++;
        } else if (isalpha(c)) {
            (*letters)++;
        }
        str++;
    }
}

int main(void) {
    size_t buffer_size = 256;
    size_t input_length = 0;
    char *buffer = malloc(buffer_size);
    size_t digit_count = 0;
    size_t letter_count = 0;
    int ch;
    
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter a string: ");
    
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (input_length + 1 >= buffer_size) {
            size_t new_size;
            char *new_buffer;
            
            if (buffer_size > SIZE_MAX / 2) {
                fprintf(stderr, "Input too large\n");
                free(buffer);
                return 1;
            }
            
            new_size = buffer_size * 2;
            
            if (new_size <= buffer_size) {
                fprintf(stderr, "Integer overflow detected\n");
                free(buffer);
                return 1;
            }
            
            new_buffer = realloc(buffer, new_size);
            
            if (new_buffer == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(buffer);
                return 1;
            }
            
            buffer = new_buffer;
            buffer_size = new_size;
        }
        buffer[input_length++] = (char)ch;
    }
    
    if (ferror(stdin)) {
        fprintf(stderr, "Input error occurred\n");
        free(buffer);
        return 1;
    }
    
    if (input_length >= buffer_size) {
        fprintf(stderr, "Buffer overflow detected\n");
        free(buffer);
        return 1;
    }
    
    buffer[input_length] = '\0';
    
    count_digits_letters(buffer, &digit_count, &letter_count);
    
    printf("Digits: %zu\n", digit_count);
    printf("Letters: %zu\n", letter_count);
    
    free(buffer);
    return 0;
}