#include <stdio.h>

long long jacobsthal(long n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    long long a = 0, b = 1;
    for (long i = 2; i <= n; ++i) {
        long long c = a + 2 * b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    scanf("%ld", &n);
    printf("The %ldth Jacobsthal number is: %lld\n", n, jacobsthal(n));
    return 0;
}