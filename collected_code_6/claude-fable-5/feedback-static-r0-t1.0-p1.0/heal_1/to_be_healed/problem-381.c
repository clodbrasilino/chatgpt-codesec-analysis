#include <stdio.h>
#include <stdlib.h>

static int sort_by_index(int **lists, size_t rows, size_t cols, size_t index)
{
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'j' can be reduced. [variableScope]
     */
    size_t j;
    int *key;

    if (lists == NULL) {
        return -1;
    }
    if (index >= cols) {
        return -1;
    }
    for (i = 0; i < rows; i++) {
        if (lists[i] == NULL) {
            return -1;
        }
    }
    for (i = 1; i < rows; i++) {
        key = lists[i];
        j = i;
        while (j > 0 && lists[j - 1][index] > key[index]) {
            lists[j] = lists[j - 1];
            j--;
        }
        lists[j] = key;
    }
    return 0;
}

static void free_lists(int **lists, size_t rows)
{
    size_t i;

    if (lists == NULL) {
        return;
    }
    for (i = 0; i < rows; i++) {
        free(lists[i]);
    }
    free(lists);
}

int main(void)
{
    const size_t rows = 4;
    const size_t cols = 3;
    const size_t sort_index = 1;
    const int data[4][3] = {
        {5, 9, 2},
        {3, 1, 8},
        {7, 4, 6},
        {2, 7, 0}
    };
    int **lists;
    size_t i;
    size_t j;

    lists = malloc(rows * sizeof(int *));
    if (lists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    for (i = 0; i < rows; i++) {
        lists[i] = NULL;
    }
    for (i = 0; i < rows; i++) {
        lists[i] = malloc(cols * sizeof(int));
        if (lists[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_lists(lists, rows);
            return EXIT_FAILURE;
        }
        for (j = 0; j < cols; j++) {
            lists[i][j] = data[i][j];
        }
    }

    if (sort_by_index(lists, rows, cols, sort_index) != 0) {
        fprintf(stderr, "Sorting failed\n");
        free_lists(lists, rows);
        return EXIT_FAILURE;
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", lists[i][j]);
        }
        printf("\n");
    }

    free_lists(lists, rows);
    return EXIT_SUCCESS;
}