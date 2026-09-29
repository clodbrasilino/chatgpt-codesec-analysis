#include <stdio.h>

long long nthStarNumber(int n) {
    return 6 * n * (n - 1) + 1;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth star number is: %lld\n", n, nthStarNumber(n));
    return 0;
}