#include <stdio.h>

long long newmanShanksWilliams(int n) {
    long long current;
    if (n == 0 || n == 1) {
        current = 1;
    }
    else {
        long long prevPrev = 1;
        long long prev = 1;
        for (int i = 2; i <= n; i++) {
            current = 2 * prev + prevPrev;
            prevPrev = prev;
            prev = current;
        }
    }
    /* Possible weaknesses found:
     *  use of uninitialized value 'current' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    return current;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth Newman-Shanks-Williams prime number is %lld\n", n, newmanShanksWilliams(n));
    return 0;
}