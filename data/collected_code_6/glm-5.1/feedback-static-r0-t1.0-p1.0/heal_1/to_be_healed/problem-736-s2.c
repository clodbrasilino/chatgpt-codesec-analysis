#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
size_t left_insertion_point(int *arr, size_t len, int value) {
    if (arr == NULL || len == 0) {
        return 0;
    }
    size_t low = 0;
    size_t high = len;
    while (low < high) {
        size_t mid = low + (high - low) / 2;
        if (arr[mid] < value) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

int main(void) {
    int arr[] = {1, 2, 4, 4, 4, 5, 7, 9};
    size_t len = sizeof(arr) / sizeof(arr[0]);
    size_t i;
    
    int targets[] = {0, 4, 6, 10};
    size_t targets_len = sizeof(targets) / sizeof(targets[0]);
    
    for (i = 0; i < targets_len; i++) {
        size_t ins = left_insertion_point(arr, len, targets[i]);
        printf("Left insertion point for %d: %zu\n", targets[i], ins);
    }
    
    return 0;
}