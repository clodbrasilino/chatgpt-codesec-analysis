#include <stdio.h>
#include <stdlib.h>

long long find_nth_decagonal_number(int n) {
    if (n < 1) {
        exit(EXIT_FAILURE);
    }
    long long ln = n;
    return 4 * ln * ln - 3 * ln;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    int n;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    if (n < 1) {
        return EXIT_FAILURE;
    }
    long long result = find_nth_decagonal_number(n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}