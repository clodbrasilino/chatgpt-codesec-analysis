#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

unsigned long long find_nth_hexagonal_number(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    if (n > 1844674407370955161ULL) {
        fprintf(stderr, "Error: Input exceeds safe limits to prevent overflow\n");
        exit(EXIT_FAILURE);
    }
    return n * ((2 * n) - 1);
}

int main(int argc, char *argv[]) {
    unsigned long long n = 10;
    if (argc == 2) {
        size_t len = strnlen(argv[1], 21);
        if (len == 0 || len > 20) {
            fprintf(stderr, "Error: Invalid input. Must be a positive integer.\n");
            return EXIT_FAILURE;
        }
        for (size_t i = 0; i < len; i++) {
            if (argv[1][i] < '0' || argv[1][i] > '9') {
                fprintf(stderr, "Error: Invalid input. Must be a positive integer.\n");
                return EXIT_FAILURE;
            }
        }
        if (strcmp(argv[1], "0") == 0) {
            fprintf(stderr, "Error: Invalid input. Must be a positive integer.\n");
            return EXIT_FAILURE;
        }
        char *endptr;
        errno = 0;
        n = strtoull(argv[1], &endptr, 10);
        if (errno == ERANGE || *endptr != '\0') {
            fprintf(stderr, "Error: Invalid input. Must be a positive integer.\n");
            return EXIT_FAILURE;
        }
    }
    printf("%llu\n", find_nth_hexagonal_number(n));
    return EXIT_SUCCESS;
}