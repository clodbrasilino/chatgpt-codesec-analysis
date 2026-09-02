#include <stdio.h>
#include <limits.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int getMinSquares(unsigned int n) {
    if (n <= 3) return n;

    int res = n; 

    for (int x = 1; x * x <= n; x++) {
        int temp = x * x;
        res = min(res, 1 + getMinSquares(n - temp));
    }

    return res;
}

int main() {
    unsigned int n;
    printf("Enter a number: ");
    scanf("%u", &n);
    printf("Minimum number of squares: %d\n", getMinSquares(n));
    return 0;
}