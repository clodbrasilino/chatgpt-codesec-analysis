#include <stdio.h>

void repeat_elements(int* arr, int n) {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < arr[i]; j++) {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    repeat_elements(arr, n);
    return 0;
}