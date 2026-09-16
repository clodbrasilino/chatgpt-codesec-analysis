#include <stdio.h>
#include <stdlib.h>

int last_digit_factorial_division(int a, int b) {
    if (a < 0 || b < 0) {
        exit(EXIT_FAILURE);
    }
    if (a > b) {
        return 0;
    }
    unsigned long long result = 1;
    for (int i = a + 1; i <= b; ++i) {
        result *= (unsigned long long)i;
        result %= 10;
    }
    return (int)result;
}

int main(void) {
    int a, b;
    if (scanf("%d %d", &a, &b) != 2) {
        return EXIT_FAILURE;
    }
    printf("%d\n", last_digit_factorial_division(a, b));
    return EXIT_SUCCESS;
}