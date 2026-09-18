#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int compare(const void *a, const void *b) {
    return *(int*) a - *(int*) b;
}

int sumOfThreeSmallest(int* numbers, int arraySize) {
    if (arraySize < 3) {
        printf("Insufficient elements in the array\n");
        return -1;
    }

    qsort(numbers, arraySize, sizeof(int), compare);

    int sum = 0;
    for(int i = 0; i < 3; i++) {
        if(numbers[i] < 0) {
            printf("Number %d is not positive\n", numbers[i]);
            return -1;
        }

        sum += numbers[i];
    }

    return sum;
}

int main() {
    int numbers[SIZE] = {10, 2, 3, 4, -5, 6, 7, 8, 9, 11};

    int sum = sumOfThreeSmallest(numbers, SIZE);
    if (sum != -1) {
        printf("Sum of three smallest positive numbers: %d\n", sum);
    }

    return 0;
}