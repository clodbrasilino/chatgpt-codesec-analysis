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
    int arr[] = {2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    if(checkEvenIndexEvenNumbers(arr, n)) {
        printf("All even indices contain even numbers.\n");
    } else {
        printf("All even indices do not contain even numbers.\n");
    }

    return 0;
}