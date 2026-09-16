#include <stdio.h>
#include <stdlib.h>

int* get_elements(const int* list, size_t list_size, const size_t* indices, size_t num_indices, size_t* out_size) {
    if (list == NULL || indices == NULL || out_size == NULL || list_size == 0 || num_indices == 0) {
        if (out_size != NULL) {
            *out_size = 0;
        }
        return NULL;
    }

    size_t valid_count = 0;
    for (size_t i = 0; i < num_indices; ++i) {
        if (indices[i] < list_size) {
            valid_count++;
        }
    }

    if (valid_count == 0) {
        *out_size = 0;
        return NULL;
    }

    int* result = (int*)malloc(valid_count * sizeof(int));
    if (result == NULL) {
        *out_size = 0;
        return NULL;
    }

    size_t k = 0;
    for (size_t i = 0; i < num_indices; ++i) {
        if (indices[i] < list_size) {
            result[k++] = list[indices[i]];
        }
    }

    *out_size = valid_count;
    return result;
}

int main(void) {
    int list[] = {10, 20, 30, 40, 50, 60, 70, 80};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    
    size_t indices[] = {1, 3, 5, 10, 7};
    size_t num_indices = sizeof(indices) / sizeof(indices[0]);
    
    size_t out_size = 0;
    int* selected_elements = get_elements(list, list_size, indices, num_indices, &out_size);
    
    if (selected_elements != NULL) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%d ", selected_elements[i]);
        }
        printf("\n");
        
        free(selected_elements);
        selected_elements = NULL;
    } else {
        printf("No valid elements found or memory allocation failed.\n");
    }

    return 0;
}