#include <stdio.h>
#include <stdbool.h>

bool isPresent(int arr[], int len, int element) {
    for(int i = 0; i < len; i++) {
        if(arr[i] == element) {
            return true;
        }
    }
    return false;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);
    int element = 3;

    if(isPresent(arr, len, element)) {
        printf("Element is present in the list.\n");
    } else {
        printf("Element is not present in the list.\n");
    }

    return 0;
}