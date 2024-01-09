#include <stdio.h>
#include <math.h>

int minSquares(int n) {
    // Base cases
    if (n <= 3)
        return n;

    // Find the ceiling square root of n
    int limit = (int) sqrt(n);

    // Initialize minimum number of squares needed to infinity
    int minCount = n;

    // Try all smaller numbers
    for (int x = 1; x <= limit; x++) {
        int temp = x * x;

        // If current number squares exceeds n, then no need to check further
        if (temp > n)
            break;

        // Recursive call to find minimum count for n - temp
        minCount = fmin(minCount, 1 + minSquares(n - temp));
    }
    return minCount;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Minimum number of squares: %d\n", minSquares(n));
    return 0;
}
