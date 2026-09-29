#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'sizes2' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'sizes1' can be declared as pointer to const [constParameterPointer]
 */
int** zip_lists(int** list1, int* sizes1, int len1, int** list2, int* sizes2, int len2, int** out_sizes, int* out_len) {
    if (len1 != len2) {
        return NULL;
    }

    int** result = (int**)malloc(len1 * sizeof(int*));
    if (!result) {
        return NULL;
    }

    *out_sizes = (int*)malloc(len1 * sizeof(int));
    if (!*out_sizes) {
        free(result);
        return NULL;
    }

    *out_len = len1;

    for (int i = 0; i < len1; i++) {
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

    return result;
}

void free_zipped(int** zipped, int* sizes, int len) {
    if (!zipped) {
        return;
    }
    for (int i = 0; i < len; i++) {
        free(zipped[i]);
    }
    free(zipped);
    free(sizes);
}

int main(void) {
    int row1_1[] = {1, 2};
    int row1_2[] = {3, 4, 5};
    int* list1[] = {row1_1, row1_2};
    int sizes1[] = {2, 3};

    int row2_1[] = {6, 7};
    int row2_2[] = {8, 9, 10};
    int* list2[] = {row2_1, row2_2};
    int sizes2[] = {2, 3};

    int* out_sizes = NULL;
    int out_len = 0;

    int** zipped = zip_lists(list1, sizes1, 2, list2, sizes2, 2, &out_sizes, &out_len);

    if (zipped) {
        for (int i = 0; i < out_len; i++) {
            for (int j = 0; j < out_sizes[i]; j++) {
                printf("%d ", zipped[i][j]);
            }
            printf("\n");
        }
        free_zipped(zipped, out_sizes, out_len);
    }

    return 0;
}