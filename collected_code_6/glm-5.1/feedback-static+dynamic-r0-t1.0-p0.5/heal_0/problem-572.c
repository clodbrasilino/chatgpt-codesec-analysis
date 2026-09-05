#include <stdio.h>
#include <stdlib.h>

int* remove_two_duplicates(int* lists[], int list_sizes[], int num_lists, int result_size, int* out_size) {
    int total_elements = 0;
    for (int i = 0; i < num_lists; i++) {
        total_elements += list_sizes[i];
    }

    if (total_elements == 0) {
        *out_size = 0;
        return NULL;
    }

    int* combined = (int*)malloc(total_elements * sizeof(int));
    if (!combined) {
        *out_size = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < num_lists; i++) {
        for (int j = 0; j < list_sizes[i]; j++) {
            combined[index++] = lists[i][j];
        }
    }

    for (int i = 0; i < total_elements - 1; i++) {
        for (int j = i + 1; j < total_elements; j++) {
            if (combined[i] > combined[j]) {
                int temp = combined[i];
                combined[i] = combined[j];
                combined[j] = temp;
            }
        }
    }

    int* result = (int*)malloc(result_size * sizeof(int));
    if (!result) {
        free(combined);
        *out_size = 0;
        return NULL;
    }

    int res_index = 0;
    int i = 0;
    while (i < total_elements) {
        if (i + 1 < total_elements && combined[i] == combined[i + 1]) {
            i += 2;
        } else {
            if (res_index < result_size) {
                result[res_index++] = combined[i];
            }
            i++;
        }
    }

    free(combined);
    *out_size = res_index;
    return result;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 4, 6, 8};
    int list3[] = {1, 3, 5, 7, 9};
    
    int* lists[] = {list1, list2, list3};
    int list_sizes[] = {5, 4, 5};
    int num_lists = 3;
    int result_size = 14;
    int out_size = 0;

    int* result = remove_two_duplicates(lists, list_sizes, num_lists, result_size, &out_size);

    if (result != NULL) {
        for (int i = 0; i < out_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}