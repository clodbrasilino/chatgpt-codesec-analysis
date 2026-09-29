#include <stdio.h>

int findFirstOdd(int arr[], int size, int *result) {
    if (arr == NULL || result == NULL || size <= 0) {
        return 0;
    }
    
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            *result = arr[i];
            return 1;
        }
    }
    
    return 0;
}

int main(void) {
    int numbers[] = {2, 4, 6, 8, 9, 10, 12};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int firstOdd;
    
    if (findFirstOdd(numbers, size, &firstOdd)) {
        printf("First odd number: %d\n", firstOdd);
    } else {
        printf("No odd number found.\n");
    }
    
    return 0;
}