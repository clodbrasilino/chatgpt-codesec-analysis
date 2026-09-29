#include <stdio.h>

int checkSameType(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        if(sizeof(arr[i]) != sizeof(arr[i+1])) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);

    if(checkSameType(arr, n)) {
        printf("All elements are of the same type.\n");
    } else {
        printf("All elements are not of the same type.\n");
    }

    return 0;
}