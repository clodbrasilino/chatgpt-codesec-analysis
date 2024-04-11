#include <stdio.h>

long long nthRectangularNumber(int n) {
    return (long long)n * (n + 1);
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %d-th rectangular number is: %lld\n", n, nthRectangularNumber(n));
    return 0;
}