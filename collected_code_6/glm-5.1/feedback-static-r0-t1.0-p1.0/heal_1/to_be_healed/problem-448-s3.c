#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_perrin_sum(int n) {
    if (n < 0) {
        return 0;
    }

    unsigned long long *buffer = NULL;

    if (n >= 3) {
        buffer = (unsigned long long *)malloc(n * sizeof(unsigned long long));
        if (buffer == NULL) {
            return 0;
        }

        buffer[0] = 3;
        buffer[1] = 0;
        buffer[2] = 2;

        for (int i = 3; i < n; i++) {
            buffer[i] = buffer[i - 2] + buffer[i - 3];
        }

        unsigned long long total = 5;
        for (int i = 3; i < n; i++) {
            total += buffer[i];
        }

        free(buffer);
        return total;
    }

    unsigned long long total = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0) total += 3;
        else if (i == 1) total += 0;
        else if (i == 2) total += 2;
    }

    return total;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
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