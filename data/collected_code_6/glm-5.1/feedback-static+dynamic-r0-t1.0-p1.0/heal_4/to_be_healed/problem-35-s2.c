#include <stdio.h>
#include <stdlib.h>

unsigned long long find_rectangular_number(int n) {
    return (unsigned long long)n * (n + 1);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    int n;
    
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    if (sscanf(argv[1], "%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n < 1) {
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", find_rectangular_number(n));
    
    return EXIT_SUCCESS;
}