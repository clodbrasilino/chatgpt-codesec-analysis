#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_closest_smaller(int n, const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return INT_MIN;
    }
    
    int closest = INT_MIN;
    int found = 0;
    
    for (size_t i = 0; i < size; i++) {
        if (arr[i] < n) {
            if (!found || arr[i] > closest) {
                closest = arr[i];
                found = 1;
            }
        }
    }
    
    return found ? closest : INT_MIN;
}

int main(void) {
    int numbers[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int n = 5;
    
    int result = find_closest_smaller(n, numbers, size);
    
    if (result != INT_MIN) {
        printf("Closest smaller number to %d: %d\n", n, result);
    } else {
        printf("No smaller number found for %d\n", n);
    }
    
    return 0;
}