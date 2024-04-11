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
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int index[] = {0, 2, 4, 6, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int m = sizeof(index) / sizeof(index[0]);
    accessElements(arr, index, n, m);
    return 0;
}