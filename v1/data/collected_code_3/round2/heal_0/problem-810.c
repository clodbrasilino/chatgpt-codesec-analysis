#include <stdio.h>

void repeatElements(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < arr[i]; j++) {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {2, 3, 4, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    repeatElements(arr, n);
    return 0;
}