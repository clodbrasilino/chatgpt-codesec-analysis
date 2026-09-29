#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

bool is_even(int num) {
    return (num & 1) == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    long val = strtol(argv[1], NULL, 10);
    if (val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int num = (int)val;
    if (is_even(num)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return EXIT_SUCCESS;
}