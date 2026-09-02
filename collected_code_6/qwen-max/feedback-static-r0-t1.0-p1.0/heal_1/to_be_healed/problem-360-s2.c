#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_carol_number(unsigned int n) {
    unsigned long long result = 1;
    for (unsigned int i = 0; i < n; ++i) {
        result *= 2;
    }
    result--;
    result *= result;
    result--;
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned int n = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    unsigned long long carol_number = calculate_carol_number(n);
    printf("The %u-th Carol number is: %llu\n", n, carol_number);

    return EXIT_SUCCESS;
}