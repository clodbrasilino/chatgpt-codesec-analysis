#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>

int tiling(int n) {
    if (n < 1) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 2;
    }

    int prev2 = 1;
    int prev1 = 2;

    for (int i = 2; i < n; i++) {
        int current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return prev1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <length>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || val <= 0 || val > INT_MAX || errno == ERANGE) {
        fprintf(stderr, "Length must be a positive integer.\n");
        return 1;
    }

    int n = (int)val;

    int result = tiling(n);
    printf("%d\n", result);

    return 0;
}