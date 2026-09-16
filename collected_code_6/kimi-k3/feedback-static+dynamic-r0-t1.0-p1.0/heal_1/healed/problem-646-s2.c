#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long count_cubes(unsigned long long n, unsigned long long k)
{
    if (k == 0 || n < k) {
        return 0;
    }
    
    unsigned long long positions = n - k + 1;
    
    if (positions <= ULLONG_MAX / positions) {
        unsigned long long square = positions * positions;
        if (square <= ULLONG_MAX / positions) {
            return square * positions;
        }
    }
    
    return 0;
}

int main(void)
{
    unsigned long long n, k;
    
    if (scanf("%llu %llu", &n, &k) != 2) {
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", count_cubes(n, k));
    
    return EXIT_SUCCESS;
}