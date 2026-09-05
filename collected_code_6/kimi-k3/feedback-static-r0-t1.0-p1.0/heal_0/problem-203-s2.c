#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int hamming_distance(unsigned int x, unsigned int y)
{
    unsigned int xor_val = x ^ y;
    int distance = 0;
    
    while (xor_val != 0U) {
        distance += (int)(xor_val & 1U);
        xor_val >>= 1;
    }
    
    return distance;
}

int main(void)
{
    char input_buffer[256];
    char *end_ptr;
    unsigned long val1;
    unsigned long val2;
    int result;
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val1 = strtoul(input_buffer, &end_ptr, 10);
    if (errno != 0 || end_ptr == input_buffer || val1 > UINT_MAX) {
        fprintf(stderr, "Invalid first integer\n");
        return EXIT_FAILURE;
    }
    
    while (*end_ptr == ' ' || *end_ptr == '\t') {
        end_ptr++;
    }
    
    errno = 0;
    val2 = strtoul(end_ptr, &end_ptr, 10);
    if (errno != 0 || val2 > UINT_MAX) {
        fprintf(stderr, "Invalid second integer\n");
        return EXIT_FAILURE;
    }
    
    result = hamming_distance((unsigned int)val1, (unsigned int)val2);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}