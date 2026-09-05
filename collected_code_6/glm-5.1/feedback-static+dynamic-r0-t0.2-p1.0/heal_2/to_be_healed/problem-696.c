#include <stdio.h>
#include <stdlib.h>

int** zip_lists(int** list1, const int* sizes1, int count1, int** list2, const int* sizes2, int count2, int** out_sizes, int* out_count) {
    if (count1 != count2) {
        return NULL;
    }

    int** result = (int**)malloc(count1 * sizeof(int*));
    if (!result) {
        return NULL;
    }

    int* res_sizes = (int*)malloc(count1 * sizeof(int));
    if (!res_sizes) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < count1; i++) {
        int s1 = sizes1[i];
        int s2 = sizes2[i];
        res_sizes[i] = s1 + s2;

        result[i] = (int*)malloc(res_sizes[i] * sizeof(int));
        if (!result[i]) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(res_sizes);
            free(result);
            return NULL;
        }

        for (int k = 0; k < s1; k++) {
            result[i][k] = list1[i][k];
        }
        for (int k = 0; k < s2; k++) {
            result[i][s1 + k] = list2[i][k];
        }
    }

    *out_sizes = res_sizes;
    *out_count = count1;
    return result;
}

void free_zipped(int** list, int* sizes, int count) {
    if (!list) return;
    for (int i = 0; i < count; i++) {
        free(list[i]);
    }
    free(sizes);
    free(list);
}

int main(void) {
    int row1_1[] = {1, 2};
    int row1_2[] = {3, 4, 5};
    int* list1[] = {row1_1, row1_2};
    /* Possible weaknesses found:
     *  Variable 'sizes1' can be declared as const array [constVariable]
     */
    int sizes1[] = {2, 3};

    int row2_1[] = {6};
    int row2_2[] = {7, 8};
    int* list2[] = {row2_1, row2_2};
    /* Possible weaknesses found:
     *  Variable 'sizes2' can be declared as const array [constVariable]
     */
    int sizes2[] = {1, 2};

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