#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'sizes' can be declared as pointer to const [constParameterPointer]
 */
int findMaxSum(int **lists, int n, int *sizes) {
    int max_sum = 0;
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < sizes[i]; ++j) {
            sum += lists[i][j];
        }
        if (sum > max_sum) {
            max_sum = sum;
        }
    }
    return max_sum;
}

int main() {
    int n = 3;
    int *sizes = (int *)malloc(n * sizeof(int));
    int **lists = (int **)malloc(n * sizeof(int *));
    
    sizes[0] = 3;
    lists[0] = (int *)malloc(sizes[0] * sizeof(int));
    lists[0][0] = 1;
    lists[0][1] = 2;
    lists[0][2] = 3;

    sizes[1] = 4;
    lists[1] = (int *)malloc(sizes[1] * sizeof(int));
    lists[1][0] = 4;
    lists[1][1] = 5;
    lists[1][2] = 6;
    lists[1][3] = 7;

    sizes[2] = 2;
    lists[2] = (int *)malloc(sizes[2] * sizeof(int));
    lists[2][0] = 8;
    lists[2][1] = 9;

    int result = findMaxSum(lists, n, sizes);
    printf("Maximum sum: %d\n", result);

    for (int i = 0; i < n; ++i) {
        free(lists[i]);
    }
    free(lists);
    free(sizes);

    return 0;
}