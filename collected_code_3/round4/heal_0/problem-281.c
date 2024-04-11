#include <stdio.h>
#include <stdbool.h>

bool check_unique(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(arr[i] == arr[j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    if(check_unique(arr, n)) {
        printf("The elements are unique.\n");
    } else {
        printf("The elements are not unique.\n");
    }

    return 0;
}