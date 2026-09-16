#include <stdio.h>
#include <stdlib.h>

unsigned long long fibonacci(unsigned int n);

unsigned long long fibonacci(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(void) {
    unsigned int n = 0;
    unsigned long long result = 0;

    if (scanf("%u", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n > 93) {
        return EXIT_FAILURE;
    }

    result = fibonacci(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}