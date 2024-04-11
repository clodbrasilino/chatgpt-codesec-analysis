#include <stdio.h>

long long delannoy(int n, int m) {
    if (n == 0 || m == 0)
        return 1;
    return delannoy(n-1, m) + delannoy(n-1, m-1) + delannoy(n, m-1);
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth Delannoy number is: %lld\n", n, delannoy(n, n));
    return 0;
}