#include <stdio.h>
#include <stdlib.h>

unsigned long find_nth_not_multiple(unsigned long n, unsigned long k) {
    if (n == 0 || k == 0) {
        return 0;
    }

    unsigned long blocks = (n - 1) / (k - 1);
    unsigned long offset = (n - 1) % (k - 1);

    return blocks * k + offset + 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    unsigned long n = 0;
    unsigned long k = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_n = NULL;
    char *endptr_k = NULL;
    n = strtoul(argv[1], &endptr_n, 10);
    k = strtoul(argv[2], &endptr_k, 10);

    if (endptr_n == argv[1] || *endptr_n != '\0' || endptr_k == argv[2] || *endptr_k != '\0') {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }

    if (n == 0 || k == 0) {
        fprintf(stderr, "Input values must be greater than 0\n");
        return EXIT_FAILURE;
    }

    unsigned long result = find_nth_not_multiple(n, k);
    printf("%lu\n", result);

    return EXIT_SUCCESS;
}