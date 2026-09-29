#include <stdio.h>
#include <stdlib.h>

int find_minimum(int a, int b) {
    return a < b ? a : b;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    int a, b;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int> <int>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%d", &a) != 1) {
        return EXIT_FAILURE;
    }

    if (sscanf(argv[2], "%d", &b) != 1) {
        return EXIT_FAILURE;
    }

    printf("%d\n", find_minimum(a, b));

    return EXIT_SUCCESS;
}