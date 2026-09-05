#include <stdio.h>
#include <stdlib.h>

unsigned long long count_squares(unsigned int m, unsigned int n) {
    if (m == 0 || n == 0) {
        return 0;
    }
    
    unsigned int min = m < n ? m : n;
    unsigned int max = m < n ? n : m;
    
    unsigned long long count = 0;
    
    for (unsigned int i = 1; i <= min; i++) {
        count += (unsigned long long)(max - i + 1) * (min - i + 1);
    }
    
    return count;
}

int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <m> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr1;
    char *endptr2;
    unsigned long val1 = strtoul(argv[1], &endptr1, 10);
    unsigned long val2 = strtoul(argv[2], &endptr2, 10);
    
    if (*endptr1 != '\0' || *endptr2 != '\0' || val1 > 4294967295UL || val2 > 4294967295UL) {
        fprintf(stderr, "Error: Arguments must be non-negative integers.\n");
        return EXIT_FAILURE;
    }
    
    unsigned int m = (unsigned int)val1;
    unsigned int n = (unsigned int)val2;
    
    printf("%llu\n", count_squares(m, n));
    
    return EXIT_SUCCESS;
}