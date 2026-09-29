#include <stdio.h>

long long tetrahedral(int n) {
    return n * (n + 1) * (n + 2) / 6;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth tetrahedral number is %lld\n", n, tetrahedral(n));
    return 0;
}