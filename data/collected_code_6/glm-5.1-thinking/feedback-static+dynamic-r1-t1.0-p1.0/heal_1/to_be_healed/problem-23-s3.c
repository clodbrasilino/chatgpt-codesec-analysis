#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'sizes' can be declared as pointer to const [constParameterPointer]
 */
int find_max_sum(int **lists, int *sizes, int num_lists) {
    if (lists == NULL || sizes == NULL || num_lists <= 0) {
        return 0;
    }

    int max_sum = INT_MIN;
    int has_valid_list = 0;

    for (int i = 0; i < num_lists; i++) {
        if (sizes[i] > 0 && lists[i] != NULL) {
            has_valid_list = 1;
            int current_sum = 0;
            for (int j = 0; j < sizes[i]; j++) {
                current_sum += lists[i][j];
            }
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
    }

    if (!has_valid_list) {
        return 0;
    }

    return max_sum;
}

int main(void) {
    int num_lists = 3;
    int *sizes = NULL;
    int **lists = NULL;
    int result = 0;
    int i;

    sizes = (int *)malloc(num_lists * sizeof(int));
    if (sizes == NULL) {
        goto cleanup;
    }

    sizes[0] = 3;
    sizes[1] = 4;
    sizes[2] = 2;

    lists = (int **)malloc(num_lists * sizeof(int *));
    if (lists == NULL) {
        goto cleanup;
    }

    for (i = 0; i < num_lists; i++) {
        lists[i] = NULL;
    }

    for (i = 0; i < num_lists; i++) {
        lists[i] = (int *)malloc(sizes[i] * sizeof(int));
        if (lists[i] == NULL) {
            goto cleanup;
        }
    }

    lists[0][0] = 1;
    lists[0][1] = 2;
    lists[0][2] = 3;

    lists[1][0] = 4;
    lists[1][1] = 5;
    lists[1][2] = 6;
    lists[1][3] = 7;

    lists[2][0] = 8;
    lists[2][1] = 9;

    result = find_max_sum(lists, sizes, num_lists);
    printf("%d\n", result);

cleanup:
    if (lists != NULL) {
        for (i = 0; i < num_lists; i++) {
            if (lists[i] != NULL) {
                free(lists[i]);
            }
        }
        free(lists);
    }

    if (sizes != NULL) {
        free(sizes);
    }

    if (lists == NULL || sizes == NULL) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}