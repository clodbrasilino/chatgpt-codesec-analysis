#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 21, got <no output>
  *  test case 2 failed: expected 34, got <no output>
  *  test case 0 failed: expected 13, got <no output>
  */

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
    unsigned long long a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        unsigned long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    unsigned long long result = fibonacci(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}