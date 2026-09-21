#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long find_remainder(long dividend, long divisor) {
    if (divisor == 0) {
        exit(EXIT_FAILURE);
    }
    return dividend % divisor;
}

int main(int argc, char * const argv[]) {
    long a = 10;
    long b = 3;
    
    if (argc == 3) {
        char *endptr1;
        char *endptr2;
        errno = 0;
        long val1 = strtol(argv[1], &endptr1, 10);
        long val2 = strtol(argv[2], &endptr2, 10);
        
        if (errno == ERANGE || val1 < INT_MIN || val1 > INT_MAX || *endptr1 != '\0' || endptr1 == argv[1]) {
            return EXIT_FAILURE;
        }
        if (errno == ERANGE || val2 < INT_MIN || val2 > INT_MAX || *endptr2 != '\0' || endptr2 == argv[2]) {
            return EXIT_FAILURE;
        }
        
        a = val1;
        b = val2;
    }
    
    long result = find_remainder(a, b);
    printf("%ld\n", result);
    
    return EXIT_SUCCESS;
}