#include <stdio.h>
#include <stdlib.h>

int FindSumOfRepeatedElements(int* array, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (array[i] == array[j]) {
                sum += array[i];
                break;
            }
        }
    }
    return sum;
}

int main() {
    int array[] = {3, 2, 2, 1, 4, 3, 5, 4};
    int length = sizeof(array) / sizeof(array[0]);

    int sum = FindSumOfRepeatedElements(array, length);
    printf("Sum of repeated elements: %d\n", sum);

    return 0;
}