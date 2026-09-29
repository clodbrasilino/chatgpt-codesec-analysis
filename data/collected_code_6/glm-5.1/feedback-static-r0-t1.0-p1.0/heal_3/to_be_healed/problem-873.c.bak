#include <stdio.h>
#include <stdlib.h>

unsigned long long fibonacci(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    unsigned long long result = fibonacci(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}