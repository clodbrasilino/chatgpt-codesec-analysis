#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int find_min(int a, int b) {
    return a < b ? a : b;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int> <int>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr1;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (errno == ERANGE || *endptr1 != '\0' || val1 < INT_MIN || val1 > INT_MAX) {
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr2;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (errno == ERANGE || *endptr2 != '\0' || val2 < INT_MIN || val2 > INT_MAX) {
        return EXIT_FAILURE;
    }

    int a = (int)val1;
    int b = (int)val2;

    printf("%d\n", find_min(a, b));

    return EXIT_SUCCESS;
}