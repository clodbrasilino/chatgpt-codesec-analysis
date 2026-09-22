#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int maxProduct(Tuple *tuples, int n) {
    if (n <= 0) return 0;
    int max = tuples[0].first * tuples[0].second;
    for (int i = 1; i < n; ++i) {
        int product = tuples[i].first * tuples[i].second;
        if (product > max) max = product;
    }
    return max;
}

int main() {
    Tuple list[] = {{1, 2}, {3, 4}, {5, 6}};
    int n = sizeof(list) / sizeof(list[0]);
    int result = maxProduct(list, n);
    printf("Maximum product: %d\n", result);
    return 0;
}