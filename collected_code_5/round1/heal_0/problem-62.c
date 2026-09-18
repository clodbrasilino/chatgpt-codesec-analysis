#include <stdio.h>

int find_smallest(int arr[], int n) {
    int i, min;

    if(n <= 0)
        return -1;

    min = arr[0];

    for(i = 1; i < n; i++) {
        if(arr[i] < min)
            min = arr[i];
    }

    return min;
}

int main() {
    int arr[] = {10, 20, 30, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int smallest = find_smallest(arr, n);

    if(smallest == -1)
        printf("Array is empty or has invalid size.\n");
    else
        printf("Smallest number in array is %d\n", smallest);

    return 0;
}