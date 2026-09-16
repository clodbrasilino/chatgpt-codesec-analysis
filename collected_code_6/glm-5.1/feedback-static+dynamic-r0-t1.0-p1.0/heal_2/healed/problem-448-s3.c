#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_perrin_sum(int n) {
    if (n <= 0) {
        return 0;
    }

    if (n == 1) return 3;
    if (n == 2) return 3;
    if (n == 3) return 5;

    unsigned long long *buffer = (unsigned long long *)malloc(n * sizeof(unsigned long long));
    if (buffer == NULL) {
        return 0;
    }

    buffer[0] = 3;
    buffer[1] = 0;
    buffer[2] = 2;

    unsigned long long total = 5;
    for (int i = 3; i < n; i++) {
        buffer[i] = buffer[i - 2] + buffer[i - 3];
        total += buffer[i];
    }

    free(buffer);
    return total;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    long val = strtol(argv[1], NULL, 10);
    if (val > 10000 || val < 0) {
        return EXIT_FAILURE;
    }

    unsigned long long result = calculate_perrin_sum((int)val);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}