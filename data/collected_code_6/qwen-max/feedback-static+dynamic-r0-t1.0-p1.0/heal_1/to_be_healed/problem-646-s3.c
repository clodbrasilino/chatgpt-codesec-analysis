#include <stdio.h>
#include <stdlib.h>

size_t count_cubes(size_t n, size_t k) {
    if (n < k) return 0;
    return (n - k + 1) * (n - k + 1) * (n - k + 1);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    size_t n = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid value for n\n");
        return EXIT_FAILURE;
    }

    size_t k = strtoul(argv[2], &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid value for k\n");
        return EXIT_FAILURE;
    }

    size_t result = count_cubes(n, k);
    printf("Number of cubes of size %zu in a cube of size %zu: %zu\n", k, n, result);

    return EXIT_SUCCESS;
}