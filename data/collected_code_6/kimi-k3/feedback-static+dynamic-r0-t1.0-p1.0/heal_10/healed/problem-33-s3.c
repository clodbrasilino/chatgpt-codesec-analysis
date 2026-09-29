#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

#define BINARY_BUFFER_SIZE (sizeof(long long) * CHAR_BIT + 1)
#define INPUT_BUFFER_SIZE 256

void decimal_to_binary(long long decimal, char *buffer, size_t buffer_size) {
    size_t index;
    size_t i;
    int started;
    
    if (buffer == NULL || buffer_size < 2) {
        return;
    }
    
    if (buffer_size < BINARY_BUFFER_SIZE) {
        buffer[0] = '\0';
        return;
    }
    
    if (decimal == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    
    index = 0;
    started = 0;
    
    for (i = sizeof(long long) * CHAR_BIT; i > 0; i--) {
        if ((decimal >> (i - 1)) & 1) {
            started = 1;
        }
        if (started) {
            buffer[index++] = ((decimal >> (i - 1)) & 1) ? '1' : '0';
        }
    }
    
    buffer[index] = '\0';
}

int main(void) {
    char *input_buffer = NULL;
    char *binary_buffer = NULL;
    long long decimal_number;
    char *endptr;
    size_t len;
    int c;
    size_t capacity;
    size_t used;
    
    capacity = INPUT_BUFFER_SIZE;
    input_buffer = malloc(capacity);
    if (input_buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    binary_buffer = malloc(BINARY_BUFFER_SIZE);
    if (binary_buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }
    
    printf("Enter a decimal number: ");
    
    used = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        if (used + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *temp;
            
            if (new_capacity <= capacity) {
                fprintf(stderr, "Input too long\n");
                free(input_buffer);
                free(binary_buffer);
                return EXIT_FAILURE;
            }
            
            temp = realloc(input_buffer, new_capacity);
            if (temp == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                free(input_buffer);
                free(binary_buffer);
                return EXIT_FAILURE;
            }
            
            input_buffer = temp;
            capacity = new_capacity;
        }
        input_buffer[used++] = (char)c;
    }
    
    if (c == EOF && used == 0) {
        fprintf(stderr, "Error reading input\n");
        free(input_buffer);
        free(binary_buffer);
        return EXIT_FAILURE;
    }
    
    input_buffer[used] = '\0';
    
    len = used;
    if (len > 0 && input_buffer[len - 1] == '\r') {
        input_buffer[len - 1] = '\0';
    }
    
    errno = 0;
    decimal_number = strtoll(input_buffer, &endptr, 10);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        free(input_buffer);
        free(binary_buffer);
        return EXIT_FAILURE;
    }
    
    if (endptr == input_buffer) {
        fprintf(stderr, "Invalid input: not a number\n");
        free(input_buffer);
        free(binary_buffer);
        return EXIT_FAILURE;
    }
    
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\r') {
        endptr++;
    }
    
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input: trailing characters\n");
        free(input_buffer);
        free(binary_buffer);
        return EXIT_FAILURE;
    }
    
    if (decimal_number < 0) {
        fprintf(stderr, "Please enter a non-negative number\n");
        free(input_buffer);
        free(binary_buffer);
        return EXIT_FAILURE;
    }
    
    decimal_to_binary(decimal_number, binary_buffer, BINARY_BUFFER_SIZE);
    
    printf("Binary representation: %s\n", binary_buffer);
    
    free(input_buffer);
    free(binary_buffer);
    
    return EXIT_SUCCESS;
}