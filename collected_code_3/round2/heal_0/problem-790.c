#include <stdio.h>
#include <stdbool.h>

bool checkEvenIndexEvenNumbers(int arr[], int n) {
    for(int i = 0; i < n; i += 2) {
        if(arr[i] % 2 != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {2, 1, 4, 7, 6, 5, 8, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    if(checkEvenIndexEvenNumbers(arr, n)) {
        printf("Every even index contains even numbers.\n");
    } else {
        printf("Every even index does not contain even numbers.\n");
    }

    return 0;
}