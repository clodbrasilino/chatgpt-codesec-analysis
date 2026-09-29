#include <stdio.h>
#include <stdlib.h>

unsigned long long count_squares(unsigned int m, unsigned int n) {
    unsigned long long count = 0;
    unsigned int min = m < n ? m : n;
    for (unsigned int i = 1; i <= min; i++) {
        count += (unsigned long long)(m - i + 1) * (n - i + 1);
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <width> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    unsigned long val1 = strtoul(argv[1], NULL, 10);
    unsigned long val2 = strtoul(argv[2], NULL, 10);
    
    if (val1 == 0 || val2 == 0 || val1 > UINT_MAX || val2 > UINT_MAX) {
        fprintf(stderr, "Error: Dimensions must be positive integers within valid range.\n");
        return EXIT_FAILURE;
    }
    
    unsigned int m = (unsigned int)val1;
    unsigned int n = (unsigned int)val2;
    
    printf("%llu\n", count_squares(m, n));
    
    return EXIT_SUCCESS;
}