#include <stdio.h>
#include <stdlib.h>

int max_sum_list(int **lists, const int *sizes, int n) {
    if (n == 0) return 0;
    int max_sum = 0;
    for (int i = 0; i < n; ++i) {
        int current_sum = 0;
        for (int j = 0; j < sizes[i]; ++j) {
            current_sum += lists[i][j];
        }
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }
    return max_sum;
}

int main() {
    int n = 4;
    const int sizes[] = {3, 2, 4, 1};
    int *list_data[] = {
        (int[]){1, 2, 3},
        (int[]){4, 5},
        (int[]){6, 7, 8, 9},
        (int[]){10}
    };
    int **lists = (int**)list_data;

    int result = max_sum_list(lists, sizes, n);
    printf("The maximum sum is: %d\n", result);

    return 0;
}