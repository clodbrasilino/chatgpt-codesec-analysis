#include <stdio.h>
#include <stdbool.h>

bool checkOddIndexOddNumber(int arr[], int size) {
    for(int i = 1; i < size; i += 2) {
        if(arr[i] % 2 == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {1, 3, 2, 5, 4, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    if(checkOddIndexOddNumber(arr, size)) {
        printf("Every odd index contains odd numbers.\n");
    } else {
        printf("Every odd index does not contain odd numbers.\n");
    }

    return 0;
}