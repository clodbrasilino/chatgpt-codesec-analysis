#include <stdio.h>
#include <stdlib.h>

int **merge_first_last(int **lists, const int *list_sizes, int num_lists, int *result_sizes, int *num_result_lists) {
    if (num_lists < 2) {
        *num_result_lists = num_lists;
        int **result = (int **)malloc(num_lists * sizeof(int *));
        if (!result) {
            return NULL;
        }
        for (int i = 0; i < num_lists; ++i) {
            result[i] = (int *)malloc(list_sizes[i] * sizeof(int));
            if (!result[i]) {
                for (int j = 0; j < i; ++j) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            for (int k = 0; k < list_sizes[i]; ++k) {
                result[i][k] = lists[i][k];
            }
            result_sizes[i] = list_sizes[i];
        }
        return result;
    }

    *num_result_lists = 2;
    int *first_merged = NULL;
    int *last_merged = NULL;
    int first_count = 0;
    int last_count = 0;

    for (int i = 0; i < num_lists; ++i) {
        if (list_sizes[i] == 0) {
            continue;
        }
        first_count++;
        last_count++;
    }

    first_merged = (int *)malloc(first_count * sizeof(int));
    last_merged = (int *)malloc(last_count * sizeof(int));

    if (!first_merged || !last_merged) {
        free(first_merged);
        free(last_merged);
        return NULL;
    }

    int first_idx = 0;
    int last_idx = 0;
    for (int i = 0; i < num_lists; ++i) {
        if (list_sizes[i] == 0) {
            continue;
        }
        first_merged[first_idx++] = lists[i][0];
        last_merged[last_idx++] = lists[i][list_sizes[i] - 1];
    }

    int **result = (int **)malloc(2 * sizeof(int *));
    if (!result) {
        free(first_merged);
        free(last_merged);
        return NULL;
    }

    result[0] = first_merged;
    result[1] = last_merged;
    result_sizes[0] = first_count;
    result_sizes[1] = last_count;

    return result;
}

int main(void) {
    int list0[] = {1, 2, 3};
    int list1[] = {4, 5};
    int list2[] = {6, 7, 8, 9};

    int *lists[] = {list0, list1, list2};
    int list_sizes[] = {3, 2, 4};
    int num_lists = 3;

    int result_sizes[2];
    int num_result_lists = 0;

    int **result = merge_first_last(lists, list_sizes, num_lists, result_sizes, &num_result_lists);

    if (!result) {
        return 1;
    }

    for (int i = 0; i < num_result_lists; ++i) {
        if (result_sizes[i] == 0) {
            continue;
        }
        for (int j = 0; j < result_sizes[i]; ++j) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
        free(result[i]);
    }
    free(result);

    return 0;
}