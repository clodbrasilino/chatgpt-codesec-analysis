#include <stdio.h>
#include <stdlib.h>

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    unsigned long long n = 10;
    if (argc == 2) {
        char *endptr;
        unsigned long long parsed_n = strtoull(argv[1], &endptr, 10);
        if (*endptr != '\0' || parsed_n == 0) {
            fprintf(stderr, "Error: Invalid input. Must be a positive integer.\n");
            return EXIT_FAILURE;
        }
        n = parsed_n;
    }
    printf("%llu\n", find_nth_hexagonal_number(n));
    return EXIT_SUCCESS;
}