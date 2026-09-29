#include <stdio.h>
#include <stdbool.h>

bool check_same_type(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        if (sizeof(arr[i]) != sizeof(arr[0])) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (check_same_type(arr, n)) {
        printf("All elements are of the same type.\n");
    } else {
        printf("All elements are not of the same type.\n");
    }

    return 0;
}