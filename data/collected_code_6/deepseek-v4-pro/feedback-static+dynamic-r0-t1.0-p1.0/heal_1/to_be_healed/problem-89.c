#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_closest_smaller(int *arr, int size, int n) {
    int closest = INT_MIN;
    int found = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] < n && arr[i] > closest) {
            closest = arr[i];
            found = 1;
        }
    }
    
    return found ? closest : -1;
}

int main(void) {
    int arr[] = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int n = 5;
    int result = find_closest_smaller(arr, size, n);
    
    if (result != -1) {
        printf("Closest smaller number than %d: %d\n", n, result);
    } else {
        printf("No smaller number found than %d\n", n);
    }
    
    return 0;
}