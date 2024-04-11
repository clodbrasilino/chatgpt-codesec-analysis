#include <stdio.h>

long long nonagonalNumber(int n) {
    return n * (7 * n - 5) / 2;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth nonagonal number is: %lld\n", n, nonagonalNumber(n));
    return 0;
}