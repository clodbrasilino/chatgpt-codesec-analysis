#include <stdio.h>
#include <stdlib.h>

int findProductOfFirstEvenAndOdd(const int* arr, size_t size, int* result) {
    if (arr == NULL || result == NULL || size == 0) {
        return -1;
    }

    int firstEven = 0;
    int firstOdd = 0;
    int foundEven = 0;
    int foundOdd = 0;

    for (size_t i = 0; i < size; i++) {
        if (!foundEven && arr[i] % 2 == 0) {
            firstEven = arr[i];
            foundEven = 1;
        }
        if (!foundOdd && arr[i] % 2 != 0) {
            firstOdd = arr[i];
            foundOdd = 1;
        }
        if (foundEven && foundOdd) {
            break;
        }
    }

    if (foundEven && foundOdd) {
        *result = firstEven * firstOdd;
        return 0;
    }

    return -1;
}

int main(void) {
    int arr[] = {3, 5, 4, 7, 8, 2};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result = 0;
    
    if (findProductOfFirstEvenAndOdd(arr, size, &result) == 0) {
        printf("Product: %d\n", result);
    } else {
        printf("Could not find both an even and an odd number in the list.\n");
    }

    return 0;
}