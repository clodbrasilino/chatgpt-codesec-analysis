#include <stdio.h>
#include <stdlib.h>

unsigned long long get_star_number(int n) {
    if (n < 1) {
        return 0;
    }

    unsigned long long term = 6ULL * (n - 1);
    unsigned long long result = 1ULL + term * (term + 1) / 2;

    if (result == 0) {
        return 0;
    }

    return result;
}

int main(int argc, char * const argv[]) {
    int n;

    if (argc != 2) {
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    unsigned long long s = get_star_number(n);

    if (s == 0 && n > 0) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", s);

    return EXIT_SUCCESS;
}