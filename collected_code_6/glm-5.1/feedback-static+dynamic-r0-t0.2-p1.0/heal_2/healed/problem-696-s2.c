#include <stdio.h>
#include <stdlib.h>

int** zip_lists(int* const* list1, const int* sizes1, int count1, int* const* list2, const int* sizes2, int count2, int** out_sizes, int* out_count) {
    if (count1 != count2) {
        return NULL;
    }

    int** result = (int**)malloc(count1 * sizeof(int*));
    if (!result) {
        return NULL;
    }

    *out_sizes = (int*)malloc(count1 * sizeof(int));
    if (!*out_sizes) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < count1; i++) {
        int total_size = sizes1[i] + sizes2[i];
        result[i] = (int*)malloc(total_size * sizeof(int));
        if (!result[i]) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            free(*out_sizes);
            *out_sizes = NULL;
            return NULL;
        }

        (*out_sizes)[i] = total_size;

        for (int j = 0; j < sizes1[i]; j++) {
            result[i][j] = list1[i][j];
        }

        for (int j = 0; j < sizes2[i]; j++) {
            result[i][sizes1[i] + j] = list2[i][j];
        }
    }

    *out_count = count1;
    return result;
}

void free_zipped(int** zipped, int* sizes, int count) {
    if (!zipped) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(zipped[i]);
    }
    free(zipped);
    free(sizes);
}

int main(void) {
    int row1_1[] = {1, 2};
    int row1_2[] = {3, 4, 5};
    int* list1[] = {row1_1, row1_2};
    const int sizes1[] = {2, 3};

    int row2_1[] = {6};
    int row2_2[] = {7, 8};
    int* list2[] = {row2_1, row2_2};
    const int sizes2[] = {1, 2};

    int* out_sizes = NULL;
    int out_count = 0;

    int** zipped = zip_lists(list1, sizes1, 2, list2, sizes2, 2, &out_sizes, &out_count);

    if (!zipped) {
        return 1;
    }

    for (int i = 0; i < out_count; i++) {
        for (int j = 0; j < out_sizes[i]; j++) {
            printf("%d ", zipped[i][j]);
        }
        printf("\n");
    }

    free_zipped(zipped, out_sizes, out_count);

    return 0;
}