#include <stdio.h>
#include <stdbool.h>

#define SIZE 5

bool isPresent(int arr[], int size, int element) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == element) {
            return true;
        }
    }
    return false;
}

int main() {
    int arr[SIZE] = {1, 2, 3, 4, 5};
    int element = 3;

    if(isPresent(arr, SIZE, element)) {
        printf("Element is present in the list.\n");
    } else {
        printf("Element is not present in the list.\n");
    }

    return 0;
}