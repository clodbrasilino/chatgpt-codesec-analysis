#include <stdio.h>
#include <stdbool.h>

bool check_elements(int arr[], int n) {
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

    if(check_elements(arr, n)) {
        printf("All elements are same.\n");
    } else {
        printf("All elements are not same.\n");
    }

    return 0;
}