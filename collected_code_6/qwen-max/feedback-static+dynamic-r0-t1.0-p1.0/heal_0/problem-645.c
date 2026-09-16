#include <stdio.h>
#include <stdlib.h>

int product_of_kth(int k, int tuples[][2], int n) {
    if (k < 0 || k >= 2 || n <= 0) return -1;
    int result = 1;
    for (int i = 0; i < n; ++i) {
        result *= tuples[i][k];
    }
    return result;
}

int main() {
    int tuples[][2] = {{1, 2}, {3, 4}, {5, 6}};
    int n = 3;
    int k = 0;
    int result = product_of_kth(k, tuples, n);
    printf("%d\n", result);
    return 0;
}