#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

bool canBeSumOfTwoSquares(int n) {
    if (n < 0) {
        return false;
    }
    long long limit = (long long)sqrt((double)n);
    for (long long a = 0; a <= limit; a++) {
        long long b_squared = (long long)n - a * a;
        if (b_squared < 0) {
            break;
        }
        long long b = (long long)sqrt((double)b_squared);
        if (b * b == b_squared) {
            return true;
        }
    }
    return false;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid input: Not a valid integer\n");
        return EXIT_FAILURE;
    }
    if (canBeSumOfTwoSquares((int)val)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return EXIT_SUCCESS;
}