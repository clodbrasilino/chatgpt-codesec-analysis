#include <stdio.h>
#include <stdlib.h>

int find_element_after_rotations(const int *arr, int n, int rotations, int index) {
    if (arr == NULL || n <= 0) {
        return -1;
    }
    if (index < 0 || index >= n) {
        return -1;
    }
    
    rotations = rotations % n;
    if (rotations < 0) {
        rotations += n;
    }
    
    int original_index = (index + rotations) % n;
    return arr[original_index];
}

void rotate_left(int *arr, int n, int k) {
    if (arr == NULL || n <= 0) {
        return;
    }
    
    k = k % n;
    if (k < 0) {
        k += n;
    }
    
    if (k == 0) {
        return;
    }
    
    int *temp = (int *)malloc(k * sizeof(int));
    if (temp == NULL) {
        return;
    }
    
    for (int i = 0; i < k; i++) {
        temp[i] = arr[i];
    }
    
    for (int i = 0; i < n - k; i++) {
        arr[i] = arr[i + k];
    }
    
    for (int i = 0; i < k; i++) {
        arr[n - k + i] = temp[i];
    }
    
    free(temp);
}

void rotate_right(int *arr, int n, int k) {
    if (arr == NULL || n <= 0) {
        return;
    }
    
    k = k % n;
    if (k < 0) {
        k += n;
    }
    
    if (k == 0) {
        return;
    }
    
    int *temp = (int *)malloc(k * sizeof(int));
    if (temp == NULL) {
        return;
    }
    
    for (int i = 0; i < k; i++) {
        temp[i] = arr[n - k + i];
    }
    
    for (int i = n - 1; i >= k; i--) {
        arr[i] = arr[i - k];
    }
    
    for (int i = 0; i < k; i++) {
        arr[i] = temp[i];
    }
    
    free(temp);
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int rotations = 3;
    int index = 4;
    
    int result = find_element_after_rotations(arr, n, rotations, index);
    printf("Element at index %d after %d left rotations: %d\n", index, rotations, result);
    
    rotate_left(arr, n, rotations);
    printf("Array after %d left rotations: ", rotations);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    rotations = 3;
    index = 2;
    
    result = find_element_after_rotations(arr2, n2, rotations, index);
    printf("Element at index %d after %d right rotations: %d\n", index, rotations, result);
    
    rotate_right(arr2, n2, rotations);
    printf("Array after %d right rotations: ", rotations);
    for (int i = 0; i < n2; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");
    
    return 0;
}