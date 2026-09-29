#include <stdio.h>

int countIntegers(int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] >= 0 && arr[i] <= 9) {
            count++;
        }
    }
    return count;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    int numIntegers = countIntegers(numbers, size);

    printf("Number of integers in the list: %d\n", numIntegers);

    return 0;
}