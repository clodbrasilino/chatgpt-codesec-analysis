#include <stdio.h>
#include <stdlib.h>

int find_max_nth_col(int *tuples, int num_tuples, int num_cols, int n) {
    if (tuples == NULL || num_tuples <= 0 || num_cols <= 0 || n < 0 || n >= num_cols) {
        return 0;
    }
    int max_val = tuples[n];
    for (int i = 1; i < num_tuples; i++) {
        int current_val = tuples[i * num_cols + n];
        if (current_val > max_val) {
            max_val = current_val;
        }
    }
    return max_val;
}

int main() {
    int num_tuples = 3;
    int num_cols = 3;
    int n = 1;
    int tuples[3][3] = {
        {1, 5, 3},
        {4, 2, 9},
        {7, 8, 6}
    };
    int max_val = find_max_nth_col((int *)tuples, num_tuples, num_cols, n);
    printf("%d\n", max_val);
    return 0;
}