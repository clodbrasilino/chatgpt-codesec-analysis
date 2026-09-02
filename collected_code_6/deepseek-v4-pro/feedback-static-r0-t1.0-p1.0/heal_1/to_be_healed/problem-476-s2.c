#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int sum_of_extremes(int arr[], int size) {
    if (size <= 0) {
        return 0;
    }
    
    int min = INT_MAX;
    int max = INT_MIN;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    return min + max;
}

int main() {
    int arr[] = {5, 2, 9, 1, 7, 6, 3};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int result = sum_of_extremes(arr, size);
    printf("Sum of largest and smallest: %d\n", result);
    
    return 0;
}