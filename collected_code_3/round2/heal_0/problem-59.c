#include <stdio.h>

long long nthOctagonal(int n) {
    return n * (3 * n - 2);
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth octagonal number is %lld\n", n, nthOctagonal(n));
    return 0;
}