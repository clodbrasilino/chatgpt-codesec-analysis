#include <stdio.h>

int sequential_search(int arr[], int len, int target) {
    for( int i = 0; i < len; i++) {
        if(arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[] = {15, 32, 27, 65, 12, 87, 78, 90};
    int len = sizeof(arr) / sizeof(arr[0]);
    int target = 87;
    int result = sequential_search(arr, len, target);
    if(result != -1) {
        printf("The target is found at index: %d\n", result);
    } else {
        printf("The target is not found in the array.\n");
    }
    return 0;
}