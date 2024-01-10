#include <stdio.h>
#include <limits.h>

int findSumOfThreeLowestPositiveNumbers(const int arr[], int size) {
    int positiveNumbers[size];
    int positiveCount = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            positiveNumbers[positiveCount] = arr[i];
            positiveCount++;
        }
    }

    if (positiveCount < 3) {
        return 0;
    }

    int sum = 0;
    for (int i = 0; i < 3; i++) {
        int min = INT_MAX;
        int minIndex = 0;

        for (int j = i; j < positiveCount; j++) {
            if (positiveNumbers[j] < min) {
                min = positiveNumbers[j];
                minIndex = j;
            }
        }

        sum += min;
        positiveNumbers[minIndex] = positiveNumbers[i];
    }

    return sum;
}

int main() {
    const int numbers[] = {2, -5, 7, -3, 9, 1, -8, 6, -4};
    const int size = sizeof(numbers) / sizeof(numbers[0]);

    const int sum = findSumOfThreeLowestPositiveNumbers(numbers, size);
    printf("Sum of the three lowest positive numbers: %d\n", sum);

    return 0;
}