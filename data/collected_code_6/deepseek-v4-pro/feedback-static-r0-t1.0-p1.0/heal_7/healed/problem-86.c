#include <stdio.h>

long long centered_hexagonal(int n) {
    if (n <= 0) {
        return -1;
    }
    return 3LL * n * (n - 1) + 1;
}

int main(void) {
    int n;
    long long result;

    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    result = centered_hexagonal(n);

    if (result == -1) {
        printf("Invalid input\n");
        return 1;
    }

    printf("%lld\n", result);
    return 0;
}