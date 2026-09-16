#include <stdio.h>
#include <stdlib.h>

int **merge_first_last(int **lists, const int *sizes, int num_lists, int *res_size) {
    if (lists == NULL || sizes == NULL || res_size == NULL || num_lists <= 0) {
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < num_lists; i++) {
        if (sizes[i] == 1) {
            count += 1;
        } else if (sizes[i] > 1) {
            count += 2;
        }
    }

    if (count == 0) {
        *res_size = 0;
        return NULL;
    }

    int *merged_data = (int *)malloc(count * sizeof(int));
    if (merged_data == NULL) {
        return NULL;
    }

    int idx = 0;
    for (int i = 0; i < num_lists; i++) {
        if (sizes[i] == 1) {
            merged_data[idx++] = lists[i][0];
        } else if (sizes[i] > 1) {
            merged_data[idx++] = lists[i][0];
            merged_data[idx++] = lists[i][sizes[i] - 1];
        }
    }

    int **result = (int **)malloc(count * sizeof(int *));
    if (result == NULL) {
        free(merged_data);
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        result[i] = &merged_data[i];
    }

    *res_size = count;
    return result;
}

void free_merged(int **merged, int size) {
    if (merged != NULL && size > 0) {
        free(merged[0]);
        free(merged);
    }
}

int main(void) {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5};
    int list3[] = {6};
    int list4[] = {7, 8, 9, 10};

    int num_lists = 4;
    int *lists[] = {list1, list2, list3, list4};
    /* Possible weaknesses found:
     *  Variable 'sizes' can be declared as const array [constVariable]
     */
    int sizes[] = {3, 2, 1, 4};

    int res_size = 0;
    int **merged = merge_first_last(lists, sizes, num_lists, &res_size);

    if (merged != NULL) {
        for (int i = 0; i < res_size; i++) {
            printf("%d ", *merged[i]);
        }
        printf("\n");

        free_merged(merged, res_size);
    }

    return 0;
}