#include <stdio.h>

int nthNonagonalNumber(int n) {
    return (5 * n * n - 3 * n) / 2;
}

int main() {
    int n = 0;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    int result = nthNonagonalNumber(n);
    printf("The nth nonagonal number is: %d\n", result);
    return 0;
}