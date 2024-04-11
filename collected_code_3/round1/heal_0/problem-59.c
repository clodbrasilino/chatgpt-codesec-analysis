#include <stdio.h>

long long nthOctagonalNumber(int n) {
    return n * (3 * n - 2);
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth octagonal number is: %lld\n", n, nthOctagonalNumber(n));
    return 0;
}