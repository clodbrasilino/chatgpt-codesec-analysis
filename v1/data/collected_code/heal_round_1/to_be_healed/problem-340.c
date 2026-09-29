#include <stdio.h>

int findSumOfThreeLowestPositiveNumbers(int arr[], int size) {
    int positiveNumbers[size];
    int positiveCount = 0;

    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] > 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
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
            /* Possible weaknesses found:
             *  use of uninitialized value '*positiveNumbers[j]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             */
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