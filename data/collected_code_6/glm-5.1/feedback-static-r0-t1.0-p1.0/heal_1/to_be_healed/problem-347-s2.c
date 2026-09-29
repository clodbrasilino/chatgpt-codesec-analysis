#include <stdio.h>
#include <stdlib.h>

long long count_squares(int m, int n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }
    int min = m < n ? m : n;
    int max = m > n ? m : n;
    long long count = 0;
    for (int i = 1; i <= min; i++) {
        count += (long long)(max - i + 1) * (min - i + 1);
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <length> <width>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long m_long = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || m_long <= 0 || m_long > 2147483647) {
        fprintf(stderr, "Invalid length\n");
        return EXIT_FAILURE;
    }
    long n_long = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || n_long <= 0 || n_long > 2147483647) {
        fprintf(stderr, "Invalid width\n");
        return EXIT_FAILURE;
    }
    long long result = count_squares((int)m_long, (int)n_long);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}