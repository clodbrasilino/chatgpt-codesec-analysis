#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int hamming_distance(unsigned int a, unsigned int b)
{
    unsigned int xor_val = a ^ b;
    int count = 0;
    
    while (xor_val != 0) {
        count += (int)(xor_val & 1U);
        xor_val >>= 1;
    }
    
    return count;
}

int sum_hamming_distances(unsigned int n)
{
    unsigned int i;
    int sum = 0;
    
    if (n == 0) {
        return 0;
    }
    
    for (i = 0; i < n; i++) {
        sum += hamming_distance(i, i + 1);
    }
    
    return sum;
}

int main(int argc, char *argv[])
{
    unsigned int n;
    int result;
    char *endptr;
    long val;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(argv[1], &endptr, 10);
    
    if (errno != 0 || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: not a valid number\n");
        return EXIT_FAILURE;
    }
    
    if (val < 0 || (unsigned long)val > UINT_MAX) {
        fprintf(stderr, "Invalid input: out of range\n");
        return EXIT_FAILURE;
    }
    
    n = (unsigned int)val;
    
    result = sum_hamming_distances(n);
    printf("Sum of Hamming distances from 0 to %u: %d\n", n, result);
    
    return EXIT_SUCCESS;
}