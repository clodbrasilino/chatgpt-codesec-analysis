#include <stdio.h>
#include <stdbool.h>

bool checkElement(int arr[], int size, int element) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == element) {
            return true;
        }
    }
    return false;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int element = 3;

    if(checkElement(arr, size, element)) {
        printf("Element is present in the list.\n");
    } else {
        printf("Element is not present in the list.\n");
    }

    return 0;
}