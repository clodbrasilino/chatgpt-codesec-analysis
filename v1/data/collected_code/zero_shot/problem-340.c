#include <stdio.h>

int findSumOfThreeLowestPositiveNumbers(int arr[], int size) {
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
        int min = positiveNumbers[i];
        int minIndex = i;

        for (int j = i + 1; j < positiveCount; j++) {
            if (positiveNumbers[j] < min) {
                min = positiveNumbers[j];
                minIndex = j;
            }
        }

        sum += min;
        positiveNumbers[minIndex] = positiveNumbers[i];
        positiveNumbers[i] = min;
    }

    return sum;
}

int main() {
    int numbers[] = {2, -5, 7, -3, 9, 1, -8, 6, -4};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    int sum = findSumOfThreeLowestPositiveNumbers(numbers, size);
    printf("Sum of the three lowest positive numbers: %d\n", sum);

    return 0;
}