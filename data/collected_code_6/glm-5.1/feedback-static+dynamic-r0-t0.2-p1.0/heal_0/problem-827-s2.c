#include <stdio.h>
#include <stdlib.h>

int sum_column(int **lists, int *sizes, int num_lists, int col) {
    int total = 0;
    for (int i = 0; i < num_lists; i++) {
        if (col < sizes[i]) {
            total += lists[i][col];
        }
    }
    return total;
}

int main(void) {
    int num_lists = 3;
    int sizes[] = {4, 3, 5};
    
    int **lists = malloc(num_lists * sizeof(int *));
    if (lists == NULL) {
        return 1;
    }

    for (int i = 0; i < num_lists; i++) {
        lists[i] = malloc(sizes[i] * sizeof(int));
        if (lists[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(lists[j]);
            }
            free(lists);
            return 1;
        }
    }

    int val = 1;
    for (int i = 0; i < num_lists; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            lists[i][j] = val++;
        }
    }

    int col = 2;
    int result = sum_column(lists, sizes, num_lists, col);
    printf("%d\n", result);

    for (int i = 0; i < num_lists; i++) {
        free(lists[i]);
    }
    free(lists);

    return 0;
}