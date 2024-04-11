#include <stdio.h>
#include <stdbool.h>

bool checkDistinct(int arr[], int n) {
    for(int i = 1; i < n; i++) {
        if(arr[0] != arr[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {5, 5, 5, 5, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    if(checkDistinct(arr, n)) {
        printf("Array contains only one distinct element.\n");
    } else {
        printf("Array contains more than one distinct element.\n");
    }

    return 0;
}