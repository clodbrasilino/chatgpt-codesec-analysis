#include <stdio.h>

int maxSumDividing(int n) {
    if (n <= 1)
        return n;

    int maxSum = n;

    for (int i = 1; i < n; i++) {
        int currSum = i * (n - i);

        currSum += maxSumDividing(n - i);

        if (currSum > maxSum)
            maxSum = currSum;
    }

    return maxSum;
}

int main() {
    int num = 0;

    printf("Enter a number: ");
    scanf("%d", &num);

    if (num < 0) {
        printf("Invalid Input. Please Enter a Positive Number.\n");
        return 1;
    }

    int maxSum = maxSumDividing(num);
    printf("Maximum sum by dividing %d into three parts recursively: %d\n", num, maxSum);

    return 0;
}