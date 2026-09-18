#include <stdio.h>
#include <stdbool.h>

bool are_all_different(int *arr, int len) {
    for(int i = 0; i < len; i++) {
        for(int j = i+1; j < len; j++) {
            if(arr[i] == arr[j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);

    if(are_all_different(arr, len)) {
        printf("All elements are unique\n");
    } else {
        printf("All elements are not unique\n");
    }

    return 0;
}