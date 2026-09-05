#include <stdio.h>
#include <stdlib.h>

long long fibonacci(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    long long a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    if (n < 0) {
        return EXIT_FAILURE;
    }
    long long result = fibonacci(n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}