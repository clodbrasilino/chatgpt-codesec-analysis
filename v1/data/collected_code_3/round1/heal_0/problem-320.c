#include <stdio.h>

int squaredSumDifference(int n) {
    int sumOfSquares = n * (n + 1) * (2 * n + 1) / 6;
    int squareOfSum = (n * (n + 1) / 2) * (n * (n + 1) / 2);
    return squareOfSum - sumOfSquares;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The difference between the squared sum and the sum of squares of first %d natural numbers is %d\n", n, squaredSumDifference(n));
    return 0;
}