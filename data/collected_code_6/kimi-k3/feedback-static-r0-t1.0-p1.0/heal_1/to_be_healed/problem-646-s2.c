#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long count_cubes(unsigned long long n, unsigned long long k)
{
    if (k == 0 || n < k) {
        return 0;
    }
    
    /* Possible weaknesses found:
     *  Assignment 'positions=n-k+1', assigned value is greater than 0
     */
    unsigned long long positions = n - k + 1;
    
    /* Possible weaknesses found:
     *  Condition 'positions>0' is always true [knownConditionTrueFalse]
     *  Condition 'positions>0' is always true
     */
    if (positions > 0 && positions <= ULLONG_MAX / positions) {
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