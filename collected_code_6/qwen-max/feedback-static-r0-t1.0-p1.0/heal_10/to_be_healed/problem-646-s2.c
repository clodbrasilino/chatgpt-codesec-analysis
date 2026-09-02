#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

size_t count_cubes(size_t n, size_t k) {
    if (k > n) return 0;
    size_t count = ((n - k + 1) * (n - k + 1) * (n - k + 1));
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *endptr;
    size_t n = strtoull(argv[1], (char **) &endptr, 10);
    /* Possible weaknesses found:
     *  Value stored to 'k' during its initialization is never read [deadcode.DeadStores]
     *  k is initialized
     */
    size_t k = strtoull(argv[2], (char **) &endptr, 10);
    const char *endptr_k;

    /* Possible weaknesses found:
     *  Redundant initialization for 'k'. The initialized value is overwritten before it is read. [redundantInitialization]
     *  k is overwritten
     */
    k = strtoull(argv[2], (char **) &endptr_k, 10);

    if (*endptr != '\0' || n == 0 || n < k || *endptr_k != '\0' || k == 0) {
        fprintf(stderr, "Invalid input for n or k\n");
        return EXIT_FAILURE;
    }

    size_t result = count_cubes(n, k);
    printf("Number of cubes of size %zu in a cube of size %zu: %zu\n", k, n, result);

    return EXIT_SUCCESS;
}