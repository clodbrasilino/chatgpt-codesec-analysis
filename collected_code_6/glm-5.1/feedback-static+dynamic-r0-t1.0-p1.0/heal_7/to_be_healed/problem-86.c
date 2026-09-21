#include <stdio.h>
#include <stdlib.h>

unsigned long long centered_hexical(int n) {
    if (n < 1) {
        return 0;
    }
    return 3ULL * n * (n - 1) + 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val < 1) {
        return EXIT_FAILURE;
    }

    unsigned long long result = centered_hexical((int)val);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}