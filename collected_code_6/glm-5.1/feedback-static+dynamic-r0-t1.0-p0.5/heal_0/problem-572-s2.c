#include <stdio.h>
#include <stdlib.h>

int* remove_two_duplicates(int** lists, int* sizes, int num_lists, int* result_size) {
    int total_capacity = 0;
    for (int i = 0; i < num_lists; i++) {
        total_capacity += sizes[i];
    }

    if (total_capacity == 0) {
        *result_size = 0;
        return NULL;
    }

    int* combined = (int*)malloc(total_capacity * sizeof(int));
    if (!combined) {
        *result_size = 0;
        return NULL;
    }

    int combined_size = 0;
    for (int i = 0; i < num_lists; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            combined[combined_size++] = lists[i][j];
        }
    }

    for (int i = 0; i < combined_size - 1; i++) {
        for (int j = i + 1; j < combined_size; j++) {
            if (combined[i] > combined[j]) {
                int temp = combined[i];
                combined[i] = combined[j];
                combined[j] = temp;
            }
        }
    }

    int* result = (int*)malloc(combined_size * sizeof(int));
    if (!result) {
        free(combined);
        *result_size = 0;
        return NULL;
    }

    int res_idx = 0;
    int i = 0;
    while (i < combined_size) {
        if (i + 1 < combined_size && combined[i] == combined[i + 1]) {
            result[res_idx++] = combined[i];
            i += 2;
        } else {
            result[res_idx++] = combined[i];
            i += 1;
        }
    }

    free(combined);
    *result_size = res_idx;
    
    int* final_result = (int*)realloc(result, res_idx * sizeof(int));
    if (final_result) {
        return final_result;
    }
    return result;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 2, 6, 7};
    int list3[] = {8, 9, 9, 10};
    
    int* lists[] = {list1, list2, list3};
    int sizes[] = {5, 4, 4};
    int num_lists = 3;
    int result_size = 0;

    int* result = remove_two_duplicates(lists, sizes, num_lists, &result_size);

    if (result) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}