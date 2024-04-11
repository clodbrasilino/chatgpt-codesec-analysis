#include <stdio.h>
#include <stdbool.h>

bool checkValue(int arr[], int size, int value) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == value) {
            return true;
        }
    }
    return false;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int value = 3;
    int size = sizeof(arr) / sizeof(arr[0]);

    if(checkValue(arr, size, value)) {
        printf("Value exists in the sequence.\n");
    } else {
        printf("Value does not exist in the sequence.\n");
    }

    return 0;
}