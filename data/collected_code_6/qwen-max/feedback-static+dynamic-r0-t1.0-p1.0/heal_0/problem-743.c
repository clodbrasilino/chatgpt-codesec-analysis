#include <stdio.h>
#include <stdlib.h>

void rotate_list(int *arr, int len, int k) {
    int *temp, *new_arr;
    int i;

    if (len == 0 || k % len == 0) return;
    
    k = k % len;
    new_arr = (int *)malloc(len * sizeof(int));
    if (!new_arr) exit(EXIT_FAILURE);
    
    temp = arr + len - k;
    for (i = 0; i < k; i++) {
        new_arr[i] = temp[i];
    }
    
    for (i = k; i < len; i++) {
        new_arr[i] = arr[i - k];
    }
    
    for (i = 0; i < len; i++) {
        arr[i] = new_arr[i];
    }

    free(new_arr);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);
    int k = 2;

    rotate_list(arr, len, k);

    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}