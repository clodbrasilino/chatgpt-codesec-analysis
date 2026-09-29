#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_last_digit(int number) {
    int absolute = number < 0 ? -number : number;
    return absolute % 10;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    long long num;
    
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    if (sscanf(argv[1], "%lld", &num) != 1) {
        return EXIT_FAILURE;
    }
    
    if (num < INT_MIN || num > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    int number = (int)num;
    int result = find_last_digit(number);
    
    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}