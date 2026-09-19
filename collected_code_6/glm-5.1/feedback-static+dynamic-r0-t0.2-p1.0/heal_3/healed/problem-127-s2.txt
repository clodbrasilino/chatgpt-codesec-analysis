#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int multiply(int a, int b) {
    long long result = (long long)a * b;

    if (result > INT_MAX || result < INT_MIN) {
        abort();
    }

    return (int)result;
}

int main(void) {
    int a, b;

    if (scanf("%d %d", &a, &b) != 2) {
        return EXIT_FAILURE;
    }

    int res = multiply(a, b);
    printf("%d\n", res);

    return EXIT_SUCCESS;
}