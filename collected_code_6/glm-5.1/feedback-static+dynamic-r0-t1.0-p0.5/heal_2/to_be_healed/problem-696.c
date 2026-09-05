#include <stdio.h>
#include <stdlib.h>

int** zip_lists_of_lists(int** list1, int** list2, int num_lists, const int* list_sizes, int** out_sizes) {
    int** result = (int**)malloc(num_lists * sizeof(int*));
    if (result == NULL) {
        return NULL;
    }
    *out_sizes = (int*)malloc(num_lists * sizeof(int));
    if (*out_sizes == NULL) {
        free(result);
        return NULL;
    }
    for (int i = 0; i < num_lists; i++) {
        int current_size = list_sizes[i];
        result[i] = (int*)malloc(current_size * 2 * sizeof(int));
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            free(*out_sizes);
            *out_sizes = NULL;
            return NULL;
        }
        (*out_sizes)[i] = current_size * 2;
        for (int j = 0; j < current_size; j++) {
            result[i][j * 2] = list1[i][j];
            result[i][j * 2 + 1] = list2[i][j];
        }
    }
    return result;
}

void free_zipped(int** zipped, int* sizes, int num_lists) {
    if (zipped == NULL || sizes == NULL) {
        return;
    }
    for (int i = 0; i < num_lists; i++) {
        free(zipped[i]);
    }
    free(zipped);
    free(sizes);
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'sizes' can be declared as const array [constVariable]
     */
    int sizes[] = {2, 3};
    int row0_1[] = {1, 2};
    int row1_1[] = {3, 4, 5};
    int* list1[] = {row0_1, row1_1};
    int row0_2[] = {6, 7};
    int row1_2[] = {8, 9, 10};
    int* list2[] = {row0_2, row1_2};
    int num_lists = 2;
    int* out_sizes = NULL;
    int** zipped = zip_lists_of_lists(list1, list2, num_lists, sizes, &out_sizes);
    if (zipped == NULL) {
        return 1;
    }
    for (int i = 0; i < num_lists; i++) {
        for (int j = 0; j < out_sizes[i]; j++) {
            printf("%d ", zipped[i][j]);
        }
        printf("\n");
    }
    free_zipped(zipped, out_sizes, num_lists);
    return 0;
}