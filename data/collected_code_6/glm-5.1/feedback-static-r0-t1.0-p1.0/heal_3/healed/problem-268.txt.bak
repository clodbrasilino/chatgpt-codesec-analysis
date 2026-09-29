#include <stdio.h>
#include <stdlib.h>

unsigned long long star_number(int n) {
    if (n < 1) {
        return 0;
    }
    unsigned long long term = 6 * (unsigned long long)n - 5;
    return term * (term + 1) / 2;
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || val < 1) {
        return EXIT_FAILURE;
    }
    
    unsigned long long result = star_number((int)val);
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}