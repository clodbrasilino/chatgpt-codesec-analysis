#include <stdio.h>
#include <limits.h>

int find_largest_negative(const int *arr, int size, int *result) {
    if (arr == NULL || size <= 0 || result == NULL) {
        return -1;
    }
    
    int found = 0;
    *result = INT_MIN;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            if (!found || arr[i] > *result) {
                *result = arr[i];
                found = 1;
            }
        }
    }
    
    return found ? 0 : -1;
}

int main(void) {
    int numbers[] = {-5, 10, -3, -8, 2, -1, 7};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int largest_negative;
    
    if (find_largest_negative(numbers, size, &largest_negative) == 0) {
        printf("Largest negative number: %d\n", largest_negative);
    } else {
        printf("No negative numbers found\n");
    }
    
    return 0;
}