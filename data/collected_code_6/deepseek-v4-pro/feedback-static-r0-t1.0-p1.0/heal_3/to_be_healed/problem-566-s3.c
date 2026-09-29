#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int sum_of_digits(int n) {
    int sum = 0;
    if (n == 0) {
        return 0;
    }
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long value = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || value < 0 || value > INT_MAX) {
        fprintf(stderr, "Error: Input must be a non-negative integer within range.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", sum_of_digits((int)value));
    return EXIT_SUCCESS;
}