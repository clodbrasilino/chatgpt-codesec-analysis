#include <stdio.h>

long long int rectangularNumber(int n) {
    return n * (n + 1);
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %d-th rectangular number is: %lld\n", n, rectangularNumber(n));
    return 0;
}