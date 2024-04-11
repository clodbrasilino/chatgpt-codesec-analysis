#include <stdio.h>
#include <stdbool.h>

bool isDecreasing(int arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        if(arr[i] < arr[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {10, 9, 8, 7, 6, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    if(isDecreasing(arr, n)) {
        printf("The sequence is decreasing.\n");
    } else {
        printf("The sequence is not decreasing.\n");
    }

    return 0;
}