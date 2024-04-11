#include <stdio.h>

void find_difference(int arr[], int n) {
    int i;
    for(i = 0; i < n-1; i++) {
        printf("%d ", arr[i+1] - arr[i]);
    }
}

int main() {
    int arr[] = {5, 10, 15, 20, 25};
    int n = sizeof(arr)/sizeof(arr[0]);

    find_difference(arr, n);

    return 0;
}