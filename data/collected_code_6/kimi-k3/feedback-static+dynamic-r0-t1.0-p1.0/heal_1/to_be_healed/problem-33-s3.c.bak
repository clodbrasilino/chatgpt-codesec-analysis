#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

#define BINARY_BUFFER_SIZE (sizeof(long long) * CHAR_BIT + 1)

void decimal_to_binary(long long decimal, char *buffer, size_t buffer_size) {
    size_t index;
    size_t i;
    int started;
    
    /* Possible weaknesses found:
     *  Assuming that condition 'buffer_size<2' is not redundant
     */
    if (buffer == NULL || buffer_size < 2) {
        return;
    }
    
    if (decimal == 0) {
        /* Possible weaknesses found:
         *  Condition 'buffer_size>=2' is always true [knownConditionTrueFalse]
         *  Condition 'buffer_size>=2' is always true
         */
        if (buffer_size >= 2) {
            buffer[0] = '0';
            buffer[1] = '\0';
        }
        return;
    }
    
    index = 0;
    started = 0;
    
    for (i = sizeof(long long) * CHAR_BIT; i > 0; i--) {
        if ((decimal >> (i - 1)) & 1) {
            started = 1;
        }
        if (started) {
            if (index < buffer_size - 1) {
                buffer[index++] = ((decimal >> (i - 1)) & 1) ? '1' : '0';
            }
        }
    }
    
    buffer[index] = '\0';
}

int main(void) {
    char input_buffer[256];
    char binary_buffer[BINARY_BUFFER_SIZE];
    long long decimal_number;
    char *endptr;
    
    printf("Enter a decimal number: ");
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
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
    
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
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