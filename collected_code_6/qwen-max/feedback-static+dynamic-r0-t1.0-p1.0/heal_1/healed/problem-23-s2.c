#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_max_sum(const int *const *lists, int n, const int *sizes) {
    int max_sum = INT_MIN;
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
    int n = 3;
    const int sizes[] = {3, 2, 4};
    const int lists[3][4] = {
        {1, 2, 3},
        {4, 5},
        {6, -1, -2, 7}
    };
    const int *lists_ptr[3] = {
        lists[0],
        lists[1],
        lists[2]
    };

    int result = find_max_sum(lists_ptr, n, sizes);
    printf("The maximum sum is: %d\n", result);

    return 0;
}