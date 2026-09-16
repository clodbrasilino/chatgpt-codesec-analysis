#include <stdio.h>
#include <stdlib.h>

unsigned long long get_nth_octagonal(int n) {
    if (n <= 0) {
        return 0;
    }
    return (unsigned long long)n * (3ULL * (unsigned long long)n - 2ULL);
}

int main(void) {
    int n;
    unsigned long long octagonal_number;

    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        return EXIT_FAILURE;
    }

    octagonal_number = get_nth_octagonal(n);
    printf("%llu\n", octagonal_number);

    return EXIT_SUCCESS;
}