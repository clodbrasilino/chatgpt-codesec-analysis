#include <stdio.h>
#include <stdlib.h>

unsigned long long tetrahedral_number(unsigned int n) {
    unsigned long long term = (unsigned long long)n;
    return term * (term + 1) * (term + 2) / 6;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > 2147483647) {
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;
    unsigned long long result = tetrahedral_number(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}