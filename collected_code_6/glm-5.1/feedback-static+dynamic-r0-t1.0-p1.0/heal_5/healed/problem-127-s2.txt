#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long safe_multiply(int a, int b) {
    long long result = (long long)a * b;
    if (result > INT_MAX || result < INT_MIN) {
        abort();
    }
    return result;
}

int main(void) {
    int a = 0;
    int b = 0;

    if (scanf("%d", &a) != 1) {
        abort();
    }
    if (scanf("%d", &b) != 1) {
        abort();
    }

    int product = (int)safe_multiply(a, b);
    printf("%d\n", product);

    return 0;
}