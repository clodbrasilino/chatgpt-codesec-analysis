#include <stdio.h>
#include <stdlib.h>

int perrin_recursive(int n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;
    return perrin_recursive(n - 2) + perrin_recursive(n - 3);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long n = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || n < 0 || n > 1000000) {
        fprintf(stderr, "Error: n must be a non-negative integer\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", perrin_recursive((int)n));
    return EXIT_SUCCESS;
}