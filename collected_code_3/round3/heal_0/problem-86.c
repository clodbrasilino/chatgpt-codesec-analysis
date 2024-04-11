#include <stdio.h>

long long int centeredHexagonal(int n) {
    return 3 * n * (n - 1) + 1;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth centered hexagonal number is: %lld\n", n, centeredHexagonal(n));
    return 0;
}