#include <stdio.h>
#include <stdlib.h>

void rearrange_alternating(int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return;
    }
    
    int *temp = malloc(n * sizeof(int));
    if (temp == NULL) {
        return;
    }
    
    size_t pos_idx = 0;
    size_t neg_idx = 0;
    
    for (size_t i = 0; i < n; i++) {
        if (arr[i] >= 0) {
            pos_idx++;
        } else {
            neg_idx++;
        }
    }
    
    size_t pos_start = 0;
    size_t neg_start = pos_idx;
    size_t i = 0;
    size_t p = 0;
    size_t ne = 0;
    
    while (i < n) {
        if (i % 2 == 0 && p < pos_idx) {
            temp[i++] = arr[p++];
        } else if (i % 2 == 1 && ne < neg_idx) {
            temp[i++] = arr[neg_start + ne++];
        } else if (p < pos_idx) {
            temp[i++] = arr[p++];
        } else if (ne < neg_idx) {
            temp[i++] = arr[neg_start + ne++];
        }
    }
    
    for (size_t j = 0; j < n; j++) {
        arr[j] = temp[j];
    }
    
    free(temp);
    temp = NULL;
}

int main(void) {
    int arr[] = {-5, -2, 5, 2, 4, 7, 1, 8, 0, -8};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    rearrange_alternating(arr, n);
    
    printf("Rearranged array: ");
    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return EXIT_SUCCESS;
}