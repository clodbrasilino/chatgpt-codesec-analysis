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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[256];
    char *end_ptr;
    char *second_start;
    unsigned long val1;
    unsigned long val2;
    int result;
    size_t len;
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = 0;
    while (len < sizeof(input_buffer) && input_buffer[len] != '\0') {
        len++;
    }
    
    if (len == sizeof(input_buffer)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (len > 0 && input_buffer[len - 1] != '\n' && !feof(stdin)) {
        fprintf(stderr, "Input too long\n");
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
    
    second_start = end_ptr;
    
    errno = 0;
    val2 = strtoul(second_start, &end_ptr, 10);
    if (errno != 0 || end_ptr == second_start || val2 > UINT_MAX) {
        fprintf(stderr, "Invalid second integer\n");
        return EXIT_FAILURE;
    }
    
    result = hamming_distance((unsigned int)val1, (unsigned int)val2);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}