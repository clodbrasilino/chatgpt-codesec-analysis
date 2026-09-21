#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <limits.h>

#define INITIAL_BUFFER_SIZE 128

void count_digits_and_letters(const char *str, int *digit_count, int *letter_count) {
    *digit_count = 0;
    *letter_count = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isdigit((unsigned char)str[i])) {
            (*digit_count)++;
        } else if (isalpha((unsigned char)str[i])) {
            (*letter_count)++;
        }
    }
}

char *read_line(FILE *stream) {
    if (stream == NULL) {
        return NULL;
    }
    
    size_t capacity = INITIAL_BUFFER_SIZE;
    size_t length = 0;
    char *buffer = malloc(capacity);
    
    if (buffer == NULL) {
        return NULL;
    }
    
    int c;
    while ((c = fgetc(stream)) != EOF && c != '\n') {
        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                errno = ENOMEM;
                return NULL;
            }
            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
        buffer[length++] = (char)c;
    }
    
    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }
    
    if (c == EOF && length == 0) {
        free(buffer);
        return NULL;
    }
    
    buffer[length] = '\0';
    return buffer;
}

int main(void) {
    int digit_count, letter_count;
    
    printf("Enter a string: ");
    fflush(stdout);
    
    char *str = read_line(stdin);
    
    if (str == NULL) {
        fprintf(stderr, "Error reading input or memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    count_digits_and_letters(str, &digit_count, &letter_count);
    printf("Number of digits: %d\n", digit_count);
    printf("Number of letters: %d\n", letter_count);
    
    free(str);
    return EXIT_SUCCESS;
}