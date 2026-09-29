#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int find_first_digit(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0 || n == 1) {
        return 1;
    }

    double d = 0;
    for (int i = 2; i <= n; i++) {
        d += log10(i);
    }

    double fractional_part = d - floor(d);
    double first_digit = pow(10, fractional_part);

    return (int)first_digit;
}

int main(void) {
    int n, first_digit;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    first_digit = find_first_digit(n);
    if (first_digit == -1) {
        return EXIT_FAILURE;
    }

    printf("%d\n", first_digit);

    return EXIT_SUCCESS;
}