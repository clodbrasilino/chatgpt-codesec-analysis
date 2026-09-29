#include <stdio.h>
#include <stdlib.h>

unsigned long long tetrahedral_number(int n) {
    if (n < 1) {
        return 0;
    }
    unsigned long long un = (unsigned long long)n;
    return (un * (un + 1) * (un + 2)) / 6;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || val < 1) {
        return EXIT_FAILURE;
    }
    unsigned long long result = tetrahedral_number((int)val);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}