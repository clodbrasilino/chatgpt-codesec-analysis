#include <stdio.h>

long long int nthHexagonalNumber(int n) {
    return n * ((2 * n) - 1);
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth hexagonal number is: %lld\n", n, nthHexagonalNumber(n));
    return 0;
}