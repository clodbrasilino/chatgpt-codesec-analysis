#include <stdio.h>

int left_insert_point(int arr[], int size, int target) {
    int start = 0;
    int end = size - 1;
    int mid_point;

    while (start <= end) {
        mid_point = start + (end - start) / 2;
        if(target > arr[mid_point]) {
            start = mid_point + 1;
        } else {
            end = mid_point - 1;
        }
    }
    return start;
}

int main() {
    int arr[] = {1, 3, 5, 7, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 4;

    int index = left_insert_point(arr, size, target);

    printf("Left insert point for %d is: %d\n", target, index);
    
    return 0;
}