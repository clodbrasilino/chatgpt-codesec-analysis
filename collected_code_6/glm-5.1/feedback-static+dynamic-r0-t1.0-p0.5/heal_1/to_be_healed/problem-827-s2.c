#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'sizes' can be declared as pointer to const [constParameterPointer]
 */
int sum_column(int **lists, int *sizes, int num_lists, int col) {
    int total = 0;
    if (lists == NULL || sizes == NULL) {
        return 0;
    }
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] != NULL && col >= 0 && col < sizes[i]) {
            total += lists[i][col];
        }
    }
    return total;
}

int main(void) {
    int num_lists = 3;
    int sizes[] = {4, 4, 2};
    
    int **lists = (int **)malloc(num_lists * sizeof(int *));
    if (lists == NULL) {
        return 1;
    }

    lists[0] = (int *)malloc(sizes[0] * sizeof(int));
    lists[1] = (int *)malloc(sizes[1] * sizeof(int));
    lists[2] = (int *)malloc(sizes[2] * sizeof(int));

    if (lists[0] == NULL || lists[1] == NULL || lists[2] == NULL) {
        free(lists[0]);
        free(lists[1]);
        free(lists[2]);
        free(lists);
        return 1;
    }

    lists[0][0] = 1; lists[0][1] = 2; lists[0][2] = 3; lists[0][3] = 4;
    lists[1][0] = 5; lists[1][1] = 6; lists[1][2] = 7; lists[1][3] = 8;
    lists[2][0] = 9; lists[2][1] = 10;

    int col = 1;
    int result = sum_column(lists, sizes, num_lists, col);
    printf("%d\n", result);

    free(lists[0]);
    free(lists[1]);
    free(lists[2]);
    free(lists);

    return 0;
}