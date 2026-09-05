#include <stdio.h>
#include <stdlib.h>

long long find_nth_decagonal_number(int n) {
    if (n <= 0) {
        return -1;
    }
    long long ln = n;
    return 4 * ln * ln - 3 * ln;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int n;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    long long result = find_nth_decagonal_number(n);
    if (result == -1) {
        fprintf(stderr, "n must be a positive integer\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}