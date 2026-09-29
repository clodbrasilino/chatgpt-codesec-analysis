#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findMaxSumList(int **lists, const int *sizes, int n) {
    int max_sum = 0;
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < sizes[i]; ++j) {
            sum += lists[i][j];
        }
        max_sum = max(max_sum, sum);
    }
    return max_sum;
}

int main() {
    int n = 3;
    const int *sizes = (const int *)malloc(n * sizeof(const int));
    int **lists = (int **)malloc(n * sizeof(int *));
    
    /* Possible weaknesses found:
     *  assignment of read-only location '*sizes'
     *  read-only variable is not assignable
     */
    sizes[0] = 3;
    lists[0] = (int *)malloc(sizes[0] * sizeof(int));
    lists[0][0] = 1;
    lists[0][1] = 2;
    lists[0][2] = 3;

    /* Possible weaknesses found:
     *  read-only variable is not assignable
     *  assignment of read-only location '*(sizes + 4)'
     */
    sizes[1] = 2;
    lists[1] = (int *)malloc(sizes[1] * sizeof(int));
    lists[1][0] = 4;
    lists[1][1] = 5;

    /* Possible weaknesses found:
     *  read-only variable is not assignable
     *  assignment of read-only location '*(sizes + 8)'
     */
    sizes[2] = 4;
    lists[2] = (int *)malloc(sizes[2] * sizeof(int));
    lists[2][0] = 6;
    lists[2][1] = 7;
    lists[2][2] = 8;
    lists[2][3] = 9;

    int result = findMaxSumList(lists, sizes, n);

    printf("Maximum sum of elements in a list: %d\n", result);

    for (int i = 0; i < n; ++i) {
        free(lists[i]);
    }
    free(lists);
    free((void *)sizes);

    return 0;
}