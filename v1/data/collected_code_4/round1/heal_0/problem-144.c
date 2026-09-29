#include <stdio.h>
#include <stdlib.h>

int sumOfAbsoluteDifferences(int* arr, int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        for(int j = i+1; j < size; j++) {
            sum += abs(arr[i] - arr[j]);
        }
    }
    return sum;
}

int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int *arr = malloc(size * sizeof(int));
    if(!arr) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter the elements of the array:\n");
    for(int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    int sum = sumOfAbsoluteDifferences(arr, size);

    printf("The sum of absolute differences is: %d\n", sum);

    free(arr);
    return 0;
}