#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'sizes' can be declared as pointer to const [constParameterPointer]
 */
int max_sum_sublist(int **lists, int *sizes, int n) {
    int max_sum = 0;
    for (int i = 0; i < n; ++i) {
        int sublist_sum = 0;
        for (int j = 0; j < sizes[i]; ++j) {
            sublist_sum += lists[i][j];
        }
        if (i == 0 || sublist_sum > max_sum) {
            max_sum = sublist_sum;
        }
    }
    return max_sum;
}

int main() {
    int n = 3;
    int *sizes = (int[]){3, 4, 2};
    int **lists = (int**)(malloc(n * sizeof(int*)));
    lists[0] = (int[]){1, 2, 3};
    lists[1] = (int[]){4, 5, 6, 7};
    lists[2] = (int[]){8, 9};

    int result = max_sum_sublist(lists, sizes, n);
    printf("Maximum sum of elements in a sublist: %d\n", result);

    free(lists);
    return 0;
}