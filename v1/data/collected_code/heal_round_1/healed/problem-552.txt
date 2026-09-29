#include <stdio.h>
#include <stdbool.h>

bool isLinear(const int arr[], int size) {
    if (size == 0 || size == 1) {
        return true;
    }

    int difference = arr[1] - arr[0];
    
    for (int i = 2; i < size; i++) {
        if (arr[i] - arr[i-1] != difference) {
            return false;
        }
    }
    
    return true;
}

int main() {
    const int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    if (isLinear(arr, size)) {
        printf("The given sequence is linear.\n");
    } else {
        printf("The given sequence is not linear.\n");
    }
    
    return 0;
}