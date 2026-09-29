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

    /* Possible weaknesses found:
     *  assignment of read-only location '*sizes'
     *  read-only variable is not assignable
     */
    sizes[0] = 4;
    /* Possible weaknesses found:
     *  read-only variable is not assignable
     *  assignment of read-only location '*lists'
     */
    lists[0] = (const int *)malloc(sizes[0] * sizeof(int));
    /* Possible weaknesses found:
     *  assignment of read-only location '**lists'
     *  assignment of read-only location '*(*lists + 12)'
     *  assignment of read-only location '*(*lists + 4)'
     *  read-only variable is not assignable
     *  assignment of read-only location '*(*lists + 8)'
     */
    lists[0][0] = 1; lists[0][1] = 2; lists[0][2] = 3; lists[0][3] = 4;

    /* Possible weaknesses found:
     *  read-only variable is not assignable
     *  assignment of read-only location '*(sizes + 4)'
     */
    sizes[1] = 3;
    /* Possible weaknesses found:
     *  read-only variable is not assignable
     *  assignment of read-only location '*(lists + 8)'
     */
    lists[1] = (const int *)malloc(sizes[1] * sizeof(int));
    /* Possible weaknesses found:
     *  assignment of read-only location '*(*(lists + 8) + 4)'
     *  read-only variable is not assignable
     *  assignment of read-only location '**(lists + 8)'
     *  assignment of read-only location '*(*(lists + 8) + 8)'
     */
    lists[1][0] = -1; lists[1][1] = -2; lists[1][2] = -3;

    /* Possible weaknesses found:
     *  assignment of read-only location '*(sizes + 8)'
     *  read-only variable is not assignable
     */
    sizes[2] = 5;
    /* Possible weaknesses found:
     *  read-only variable is not assignable
     *  assignment of read-only location '*(lists + 16)'
     */
    lists[2] = (const int *)malloc(sizes[2] * sizeof(int));
    /* Possible weaknesses found:
     *  assignment of read-only location '**(lists + 16)'
     *  assignment of read-only location '*(*(lists + 16) + 4)'
     *  assignment of read-only location '*(*(lists + 16) + 12)'
     *  read-only variable is not assignable
     *  assignment of read-only location '*(*(lists + 16) + 8)'
     *  assignment of read-only location '*(*(lists + 16) + 16)'
     */
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