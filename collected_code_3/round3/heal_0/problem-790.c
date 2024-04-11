#include <stdio.h>
#include <stdbool.h>

bool checkEvenIndexEvenNumbers(int arr[], int len) {
    for(int i = 0; i < len; i += 2) {
        if(arr[i] % 2 != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {2, 1, 4, 3, 6, 5, 8, 7};
    int len = sizeof(arr) / sizeof(arr[0]);

    if(checkEvenIndexEvenNumbers(arr, len)) {
        printf("Every even index contains even numbers.\n");
    } else {
        printf("Every even index does not contain even numbers.\n");
    }

    return 0;
}