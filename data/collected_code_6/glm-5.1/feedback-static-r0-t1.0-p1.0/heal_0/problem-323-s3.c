#include <stdio.h>
#include <stdlib.h>

int* rearrange_alternating(int* arr, int n, int* out_len) {
    if (arr == NULL || out_len == NULL) {
        return NULL;
    }
    
    if (n <= 0) {
        *out_len = 0;
        return NULL;
    }
    
    int positive_count = 0;
    int negative_count = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0) {
            positive_count++;
        } else {
            negative_count++;
        }
    }
    
    int p_size = positive_count > 0 ? positive_count : 1;
    int n_size = negative_count > 0 ? negative_count : 1;
    
    int* positive = (int*)malloc(p_size * sizeof(int));
    int* negative = (int*)malloc(n_size * sizeof(int));
    
    if (positive == NULL || negative == NULL) {
        free(positive);
        free(negative);
        *out_len = 0;
        return NULL;
    }
    
    int p_idx = 0;
    int n_idx = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0) {
            positive[p_idx++] = arr[i];
        } else {
            negative[n_idx++] = arr[i];
        }
    }
    
    int* result = (int*)malloc(n * sizeof(int));
    if (result == NULL) {
        free(positive);
        free(negative);
        *out_len = 0;
        return NULL;
    }
    
    p_idx = 0;
    n_idx = 0;
    int r_idx = 0;
    
    while (p_idx < positive_count && n_idx < negative_count) {
        result[r_idx++] = positive[p_idx++];
        result[r_idx++] = negative[n_idx++];
    }
    
    while (p_idx < positive_count) {
        result[r_idx++] = positive[p_idx++];
    }
    
    while (n_idx < negative_count) {
        result[r_idx++] = negative[n_idx++];
    }
    
    *out_len = n;
    
    free(positive);
    free(negative);
    
    return result;
}

int main() {
    int arr[] = {9, 4, -2, -1, 5, 0, -5, -3, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int out_len = 0;
    
    int* result = rearrange_alternating(arr, n, &out_len);
    
    if (result != NULL) {
        for (int i = 0; i < out_len; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        if (n > 0) {
            printf("Memory allocation failed.\n");
        }
    }
    
    return 0;
}