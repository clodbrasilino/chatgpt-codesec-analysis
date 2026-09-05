#include <stdio.h>
#include <stdlib.h>

int* remove_two_duplicates(int* const* lists, const int* sizes, int num_lists, int** out_sizes) {
    int total_capacity = 0;
    for (int i = 0; i < num_lists; i++) {
        total_capacity += sizes[i];
    }
    
    if (total_capacity == 0) {
        *out_sizes = (int*)calloc(num_lists, sizeof(int));
        if (!*out_sizes) return NULL;
        return NULL;
    }

    int* result = (int*)malloc(total_capacity * sizeof(int));
    *out_sizes = (int*)calloc(num_lists, sizeof(int));
    
    if (!result || !*out_sizes) {
        free(result);
        free(*out_sizes);
        *out_sizes = NULL;
        return NULL;
    }

    int res_idx = 0;

    for (int i = 0; i < num_lists; i++) {
        int current_size = sizes[i];
        int* current_list = lists[i];
        int write_idx = 0;

        for (int j = 0; j < current_size; j++) {
            int is_dup = 0;
            for (int k = 0; k < current_size; k++) {
                if (k != j && current_list[k] == current_list[j]) {
                    is_dup = 1;
                    break;
                }
            }
            if (!is_dup) {
                current_list[write_idx++] = current_list[j];
            }
        }
        
        for (int j = 0; j < write_idx; j++) {
            result[res_idx++] = current_list[j];
        }
        
        (*out_sizes)[i] = write_idx;
    }

    return result;
}

int main() {
    int list1[] = {1, 2, 3, 2, 4};
    int list2[] = {5, 5, 6, 7, 6};
    int list3[] = {8, 9, 10};
    
    int* lists[] = {list1, list2, list3};
    int sizes[] = {5, 5, 3};
    int num_lists = 3;
    int* out_sizes = NULL;

    int* result = remove_two_duplicates(lists, sizes, num_lists, &out_sizes);

    if (result) {
        int offset = 0;
        for (int i = 0; i < num_lists; i++) {
            for (int j = 0; j < out_sizes[i]; j++) {
                printf("%d ", result[offset + j]);
            }
            printf("\n");
            offset += out_sizes[i];
        }
    }

    free(result);
    free(out_sizes);

    return 0;
}