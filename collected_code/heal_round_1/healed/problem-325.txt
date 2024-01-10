#include <stdio.h>
#include <math.h>

int minSquares(int n) {
    if (n <= 3)
        return n;

    int limit = (int) sqrt(n);
    int minCount = n;

    for (int x = 1; x <= limit; x++) {
        int temp = x * x;

        if (temp > n)
            break;

        int nextCount = 1 + minSquares(n - temp);
        minCount = (minCount < nextCount) ? minCount : nextCount;
    }
    return minCount;
}

int main() {
    int n = 0;

    printf("Enter a number: ");
    if (scanf("%d", &n) != 1)
        return 1;

    printf("Minimum number of squares: %d\n", minSquares(n));
    return 0;
}