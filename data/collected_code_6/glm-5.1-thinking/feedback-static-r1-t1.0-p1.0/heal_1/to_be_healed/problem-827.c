#include <stdio.h>
#include <stdlib.h>

long long sum_column(int **lists, size_t num_lists, const size_t *list_lengths, size_t col_index) {
    if (lists == NULL || list_lengths == NULL) {
        return 0;
    }

    long long total = 0;
    for (size_t i = 0; i < num_lists; i++) {
        if (lists[i] != NULL && col_index < list_lengths[i]) {
            total += lists[i][col_index];
        }
    }
    return total;
}

int main(void) {
    size_t num_lists = 3;
    /* Possible weaknesses found:
     *  Variable 'list_lengths' can be declared as const array [constVariable]
     */
    size_t list_lengths[] = {3, 2, 4};

    int **lists = malloc(num_lists * sizeof(int *));
    if (lists == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < num_lists; i++) {
        lists[i] = malloc(list_lengths[i] * sizeof(int));
        if (lists[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(lists[j]);
            }
            free(lists);
            return EXIT_FAILURE;
        }
    }

    lists[0][0] = 1; lists[0][1] = 2; lists[0][2] = 3;
    lists[1][0] = 4; lists[1][1] = 5;
    lists[2][0] = 6; lists[2][1] = 7; lists[2][2] = 8; lists[2][3] = 9;

    size_t target_col = 1;
    long long result = sum_column(lists, num_lists, list_lengths, target_col);
    printf("%lld\n", result);

    for (size_t i = 0; i < num_lists; i++) {
        free(lists[i]);
    }
    free(lists);

    return EXIT_SUCCESS;
}