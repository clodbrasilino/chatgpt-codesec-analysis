#include <stdio.h>
#include <limits.h>

int largest_negative(const int *arr, int size) {
    int largest = INT_MIN;
    int found = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0 && arr[i] > largest) {
            largest = arr[i];
            found = 1;
        }
    }
    
    if (!found) {
        return 0;
    }
    
    return largest;
}

int main(void) {
    int numbers[] = {-5, -12, -3, -8, -1, -15, -7};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    int result = largest_negative(numbers, size);
    
    if (result == 0) {
        printf("No negative numbers found.\n");
    } else {
        printf("Largest negative number: %d\n", result);
    }
    
    return 0;
}