#include <stdio.h>
#include <stdbool.h>

#define SIZE 5

bool checkNone(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        if(arr[i] == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    int arr[SIZE] = {1, 2, 3, 0, 5};
    if(checkNone(arr, SIZE)) {
        printf("The tuple has None value.\n");
    } else {
        printf("The tuple has no None value.\n");
    }
    return 0;
}