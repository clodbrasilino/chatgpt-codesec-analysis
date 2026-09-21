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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[INPUT_BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary_buffer[BINARY_BUFFER_SIZE];
    long long decimal_number;
    char *endptr;
    size_t len;
    
    printf("Enter a decimal number: ");
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    input_buffer[sizeof(input_buffer) - 1] = '\0';
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input_buffer);
    if (len > 0 && input_buffer[len - 1] == '\n') {
        input_buffer[len - 1] = '\0';
    } else if (len == sizeof(input_buffer) - 1 && !feof(stdin)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    decimal_number = strtoll(input_buffer, &endptr, 10);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == input_buffer) {
        fprintf(stderr, "Invalid input: not a number\n");
        return EXIT_FAILURE;
    }
    
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\r') {
        endptr++;
    }
    
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input: trailing characters\n");
        return EXIT_FAILURE;
    }
    
    if (decimal_number < 0) {
        fprintf(stderr, "Please enter a non-negative number\n");
        return EXIT_FAILURE;
    }
    
    decimal_to_binary(decimal_number, binary_buffer, sizeof(binary_buffer));
    
    printf("Binary representation: %s\n", binary_buffer);
    
    return EXIT_SUCCESS;
}