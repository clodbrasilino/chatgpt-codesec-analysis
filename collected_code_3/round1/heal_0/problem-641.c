#include <stdio.h>

long long int nthNonagonalNumber(int n) {
    return n * (7 * n - 5) / 2;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    scanf("%d", &n);
    printf("The %dth nonagonal number is: %lld\n", n, nthNonagonalNumber(n));
    return 0;
}