#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

int check_odd_parity(unsigned int num)
{
    int parity = 0;
    
    while (num != 0U) {
        parity ^= 1;
        num &= (num - 1U);
    }
    
    return parity;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read;
    char *endptr;
    unsigned long value;
    unsigned int num;
    int result;
    
    bytes_read = getline(&buffer, &buffer_size, stdin);
    
    if (bytes_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (bytes_read > 0 && buffer[bytes_read - 1] == '\n') {
        buffer[bytes_read - 1] = '\0';
    }
    
    errno = 0;
    value = strtoul(buffer, &endptr, 10);
    
    if (errno != 0) {
        fprintf(stderr, "Error converting input\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer) {
        fprintf(stderr, "No digits found\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            fprintf(stderr, "Invalid characters in input\n");
            free(buffer);
            return EXIT_FAILURE;
        }
        endptr++;
    }
    
    if (value > UINT_MAX) {
        fprintf(stderr, "Value out of range\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    num = (unsigned int)value;
    result = check_odd_parity(num);
    
    if (result == 1) {
        printf("Number %u has odd parity\n", num);
    } else {
        printf("Number %u has even parity\n", num);
    }
    
    free(buffer);
    return EXIT_SUCCESS;
}