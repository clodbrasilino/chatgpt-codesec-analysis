#include <stdio.h>
#include <stdlib.h>

unsigned long long factorial(unsigned int n) {
    unsigned long long result = 1;
    for (unsigned int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

unsigned int findFirstDivisibleByX(unsigned int x) {
    unsigned int n = 1;
    while (1) {
        unsigned long long fact = factorial(n);
        if (fact % x == 0) {
            return n;
        }
        ++n;
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <x>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned int x = atoi(argv[1]);
    if (x <= 1) {
        fprintf(stderr, "x must be a natural number greater than 1\n");
        return EXIT_FAILURE;
    }

    unsigned int result = findFirstDivisibleByX(x);
    printf("The first natural number whose factorial is divisible by %u is %u\n", x, result);

    return EXIT_SUCCESS;
}