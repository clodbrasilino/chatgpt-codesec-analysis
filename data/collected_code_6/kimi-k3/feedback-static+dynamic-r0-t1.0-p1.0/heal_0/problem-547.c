#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned int hamming_distance(unsigned int a, unsigned int b)
{
    unsigned int xor_val = a ^ b;
    unsigned int distance = 0;
    
    while (xor_val != 0U) {
        distance += xor_val & 1U;
        xor_val >>= 1;
    }
    
    return distance;
}

unsigned long long sum_hamming_distances(unsigned int n)
{
    unsigned long long sum = 0ULL;
    unsigned int i;
    
    if (n == 0U) {
        return 0ULL;
    }
    
    for (i = 0U; i < n; i++) {
        sum += (unsigned long long)hamming_distance(i, i + 1U);
    }
    
    return sum;
}

int main(void)
{
    char input_buffer[32];
    char *end_ptr = NULL;
    unsigned long parsed_value;
    unsigned int n;
    unsigned long long result;
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    parsed_value = strtoul(input_buffer, &end_ptr, 10);
    
    if (errno != 0) {
        fprintf(stderr, "Error parsing input\n");
        return EXIT_FAILURE;
    }
    
    if (end_ptr == input_buffer) {
        fprintf(stderr, "No digits found in input\n");
        return EXIT_FAILURE;
    }
    
    if (*end_ptr != '\n' && *end_ptr != '\0') {
        fprintf(stderr, "Invalid characters in input\n");
        return EXIT_FAILURE;
    }
    
    if (parsed_value > UINT_MAX) {
        fprintf(stderr, "Input value too large\n");
        return EXIT_FAILURE;
    }
    
    n = (unsigned int)parsed_value;
    
    result = sum_hamming_distances(n);
    
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}