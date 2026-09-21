#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

int main(int argc, char * const argv[const]) {
    int m, n;
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    if (strlen(argv[1]) >= 32 || strlen(argv[2]) >= 32) {
        return EXIT_FAILURE;
    }
    char buf1[32], buf2[32];
    strncpy(buf1, argv[1], sizeof(buf1) - 1);
    buf1[sizeof(buf1) - 1] = '\0';
    strncpy(buf2, argv[2], sizeof(buf2) - 1);
    buf2[sizeof(buf2) - 1] = '\0';
    if (sscanf(buf1, "%d", &m) != 1) {
        return EXIT_FAILURE;
    }
    if (sscanf(buf2, "%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    if (m <= 0 || n <= 0) {
        return EXIT_FAILURE;
    }
    long long result = count_squares(m, n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}