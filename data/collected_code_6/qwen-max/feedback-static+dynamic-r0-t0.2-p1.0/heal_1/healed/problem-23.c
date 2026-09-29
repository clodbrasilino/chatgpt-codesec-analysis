#include <stdio.h>
#include <stdlib.h>

int max_sum_list(const int **lists, const int *sizes, int n) {
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
    int *sizes = (int[]){3, 2, 4, 1};
    const int *list1[4] = {
        (const int[]){1, 2, 3},
        (const int[]){4, 5},
        (const int[]){6, 7, 8, 9},
        (const int[]){10}
    };
    const int **lists = (const int *[]){list1[0], list1[1], list1[2], list1[3]};

    int result = max_sum_list(lists, sizes, n);
    printf("The maximum sum is: %d\n", result);

    return 0;
}