#include <stdio.h>
#include <stdlib.h>

long long decagonal_number(int n) {
    if (n < 1) {
        return -1;
    }
    return (long long)n * (4 * n - 3);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || endptr == argv[1] || val < 1 || val > 2147483647) {
        fprintf(stderr, "Invalid input. Please provide a positive integer.\n");
        return EXIT_FAILURE;
    }

    int n = (int)val;
    long long result = decagonal_number(n);

    if (result < 0) {
        fprintf(stderr, "Error calculating decagonal number.\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);
    return EXIT_SUCCESS;
}