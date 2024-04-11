#include <stdio.h>

int calculateDifference(int n) {
    int sumOfSquares = 0;
    int squareOfSum = 0;
    int i;

    for (i = 1; i <= n; i++) {
        sumOfSquares += i * i;
        squareOfSum += i;
    }

    squareOfSum *= squareOfSum;

    return squareOfSum - sumOfSquares;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    int result = calculateDifference(n);
    printf("The difference is: %d\n", result);

    return 0;
}