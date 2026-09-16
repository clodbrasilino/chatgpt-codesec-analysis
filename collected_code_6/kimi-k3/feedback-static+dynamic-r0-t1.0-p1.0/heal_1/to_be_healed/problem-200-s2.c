#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_max_indices(const int *arr, size_t size, size_t **indices, size_t *count) {
    size_t i;
    int max_val;
    size_t max_count;
    size_t *temp_indices;
    
    if (arr == NULL || indices == NULL || count == NULL || size == 0) {
        return -1;
    }
    
    max_val = arr[0];
    max_count = 1;
    
    for (i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
            max_count = 1;
        } else if (arr[i] == max_val) {
            max_count++;
        }
    }
    
    temp_indices = (size_t *)malloc(max_count * sizeof(size_t));
    if (temp_indices == NULL) {
        return -1;
    }
    
    *count = 0;
    for (i = 0; i < size; i++) {
        if (arr[i] == max_val) {
            temp_indices[*count] = i;
            (*count)++;
        }
    }
    
    *indices = temp_indices;
    return 0;
}

int main(void) {
    int arr[] = {3, 7, 2, 7, 1, 7, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t *indices = NULL;
    size_t count = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;
    int result;
    
    result = find_max_indices(arr, size, &indices, &count);
    
    if (result == 0) {
        printf("Maximum value indices: ");
        for (i = 0; i < count; i++) {
            printf("%zu ", indices[i]);
        }
        printf("\n");
        printf("Count: %zu\n", count);
        
        free(indices);
        indices = NULL;
    } else {
        fprintf(stderr, "Error: Failed to find maximum indices\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}