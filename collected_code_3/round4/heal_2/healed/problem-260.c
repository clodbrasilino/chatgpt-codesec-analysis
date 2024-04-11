#include <stdio.h>

long long newmanShanksWilliams(int n) {
    long long current = 1;
    if (n > 1) {
        long long prevPrev = 1;
        long long prev = 1;
        for (int i = 2; i <= n; i++) {
            current = 2 * prev + prevPrev;
            prevPrev = prev;
            prev = current;
        }
    }
    return current;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth Newman-Shanks-Williams prime number is %lld\n", n, newmanShanksWilliams(n));
    return 0;
}