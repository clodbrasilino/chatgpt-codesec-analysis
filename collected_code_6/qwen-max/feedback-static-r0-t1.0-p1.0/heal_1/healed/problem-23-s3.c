#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_max_sum(const int *list, int size) {
    int max = INT_MIN;
    for (int i = 0; i < size; ++i) {
        int sum = 0;
        for (int j = 0; j < list[i] && (i + 1 + j) < size; ++j) {
            sum += list[i + 1 + j];
        }
        if (sum > max) max = sum;
        i += list[i] - 1;
    }
    return max;
}

int main() {
    const int data[] = {3, 1, 2, 3, 4, 4, -1, 5, 2, 6, 7};
    int n_lists = 2;
    int result = find_max_sum(data, n_lists);
    printf("%d\n", result);
    return 0;
}