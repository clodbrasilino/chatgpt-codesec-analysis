#include <stdio.h>

void accessElements(int arr[], int index[], int n, int m) {
    for(int i = 0; i < m; i++) {
        if(index[i] < n && index[i] >= 0) {
            printf("%d ", arr[index[i]]);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int index[] = {1, 3, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int m = sizeof(index) / sizeof(index[0]);
    accessElements(arr, index, n, m);
    return 0;
}