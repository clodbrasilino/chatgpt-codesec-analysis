#include <stdio.h>

int nthHexagonalNumber(int n) {
    return n * (2 * n - 1);
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("The %dth hexagonal number is: %d\n", n, nthHexagonalNumber(n));
    return 0;
}