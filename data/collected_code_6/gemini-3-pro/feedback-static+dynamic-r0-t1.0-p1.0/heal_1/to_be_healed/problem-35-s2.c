#include <stdio.h>
#include <stdlib.h>

unsigned long long get_rectangular_number(unsigned int n);

unsigned long long get_rectangular_number(unsigned int n) {
    return (unsigned long long)n * (n + 1U);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    unsigned int n;
    unsigned long long result;
    char *endptr;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    n = (unsigned int)strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    result = get_rectangular_number(n);

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}