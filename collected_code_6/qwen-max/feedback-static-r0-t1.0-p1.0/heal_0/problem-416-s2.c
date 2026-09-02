#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int solve(int n) {
    if (n <= 2) {
        return 1;
    }
    if (n == 3) {
        return 2;
    }
    return n / 2 * (n - n / 2);
}

int main() {
    int n = 15;
    int result = solve(n);
    printf("Maximum sum: %d\n", result);
    return 0;
}