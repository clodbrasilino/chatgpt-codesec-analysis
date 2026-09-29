#include <stdio.h>
#include <stdlib.h>

int* find_common_indices(const int *arr1, int size1, const int *arr2, int size2, const int *arr3, int size3, int *result_size) {
    if (arr1 == NULL || arr2 == NULL || arr3 == NULL || result_size == NULL) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }
    
    if (size1 <= 0 || size2 <= 0 || size3 <= 0) {
        *result_size = 0;
        return NULL;
    }
    
    int min_size = size1;
    if (size2 < min_size) min_size = size2;
    if (size3 < min_size) min_size = size3;
    
    int *result = (int*)malloc(min_size * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }
    
    int count = 0;
    for (int i = 0; i < min_size; i++) {
        if (arr1[i] == arr2[i] && arr2[i] == arr3[i]) {
            result[count] = i;
            count++;
        }
    }
    
    if (count == 0) {
        free(result);
        *result_size = 0;
        return NULL;
    }
    
    int *final_result = (int*)realloc(result, count * sizeof(int));
    if (final_result == NULL) {
        free(result);
        *result_size = 0;
        return NULL;
    }
    
    *result_size = count;
    return final_result;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 9, 5};
    int arr3[] = {1, 2, 8, 4, 5};
    
    int result_size = 0;
    int *common_indices = find_common_indices(arr1, 5, arr2, 5, arr3, 5, &result_size);
    
    if (common_indices != NULL) {
        printf("Common indices: ");
        for (int i = 0; i < result_size; i++) {
            printf("%d ", common_indices[i]);
        }
        printf("\n");
        free(common_indices);
    } else {
        printf("No common indices found or error occurred\n");
    }
    
    return 0;
}