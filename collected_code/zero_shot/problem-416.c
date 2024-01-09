#include <stdio.h>

int maxSumDividing(int n) {
    // Base case
    if (n <= 1)
        return n;

    int maxSum = n;

    // Consider all possible ways to divide the number
    for (int i = 1; i < n; i++) {
        int currSum = i * (n - i);

        // Recursively calculate the sum of the remaining parts
        currSum += maxSumDividing(n - i);

        // Update the maximum sum if necessary
        if (currSum > maxSum)
            maxSum = currSum;
    }

    return maxSum;
}

int main() {
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    int maxSum = maxSumDividing(num);
    printf("Maximum sum by dividing %d into three parts recursively: %d\n", num, maxSum);

    return 0;
}