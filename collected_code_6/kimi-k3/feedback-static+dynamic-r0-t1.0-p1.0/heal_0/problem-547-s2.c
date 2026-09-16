#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long sum_hamming_consecutive(unsigned long long n)
{
    unsigned long long total = 0;
    unsigned long long i;
    
    if (n == 0) {
        return 0;
    }
    
    for (i = 0; i < n; i++) {
        unsigned long long xor_val = i ^ (i + 1);
        unsigned int dist = 0;
        
        while (xor_val != 0) {
            xor_val &= (xor_val - 1);
            dist++;
        }
        
        if (ULLONG_MAX - total < dist) {
            return ULLONG_MAX;
        }
        total += dist;
    }
    
    return total;
}

int main(void)
{
    char input_buffer[256];
    char *end_ptr;
    unsigned long long n;
    unsigned long long result;
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    errno = 0;
    n = strtoull(input_buffer, &end_ptr, 10);
    
    if (errno == ERANGE || end_ptr == input_buffer || (*end_ptr != '\n' && *end_ptr != '\0')) {
        return EXIT_FAILURE;
    }
    
    result = sum_hamming_consecutive(n);
    
    if (printf("%llu\n", result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}