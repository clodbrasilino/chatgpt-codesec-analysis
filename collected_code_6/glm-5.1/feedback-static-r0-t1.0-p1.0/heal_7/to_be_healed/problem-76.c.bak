#include <stdio.h>
#include <stdlib.h>

long long count_squares(int m, int n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }
    int min = m < n ? m : n;
    long long total = 0;
    for (int i = 1; i <= min; i++) {
        total += (long long)(m - i + 1) * (n - i + 1);
    }
    return total;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    int m, n;
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &m) != 1) {
        return EXIT_FAILURE;
    }
    if (sscanf(argv[2], "%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    if (m <= 0 || n <= 0) {
        return EXIT_FAILURE;
    }
    long long result = count_squares(m, n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}