#include <stdio.h>
#include <stdlib.h>

int max_sum_sublist(const int *const *lists, int n, const int *sizes) {
    int max_sum = 0;
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < sizes[i]; ++j) {
            sum += lists[i][j];
        }
        if (i == 0 || sum > max_sum) {
            max_sum = sum;
        }
    }
    return max_sum;
}

int main() {
    int n = 3;
    const int *sizes = (int *)malloc(n * sizeof(int));
    const int *const *lists = (const int *const *)malloc(n * sizeof(const int*));

    sizes[0] = 4;
    lists[0] = (const int *)malloc(sizes[0] * sizeof(int));
    lists[0][0] = 1; lists[0][1] = 2; lists[0][2] = 3; lists[0][3] = 4;

    sizes[1] = 3;
    lists[1] = (const int *)malloc(sizes[1] * sizeof(int));
    lists[1][0] = -1; lists[1][1] = -2; lists[1][2] = -3;

    sizes[2] = 5;
    lists[2] = (const int *)malloc(sizes[2] * sizeof(int));
    lists[2][0] = 5; lists[2][1] = 3; lists[2][2] = -5; lists[2][3] = 2; lists[2][4] = -3;

    int result = max_sum_sublist(lists, n, sizes);
    printf("The maximum sum of elements in a sublist: %d\n", result);

    for (int i = 0; i < n; ++i) {
        free((void *)lists[i]);
    }
    free((void *)lists);
    free((void *)sizes);

    return 0;
}