#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int maxProductFromPairs(Tuple *list, int size) {
    if (size < 2) return -1;
    int maxProduct = list[0].first * list[0].second;
    for (int i = 1; i < size; ++i) {
        int product = list[i].first * list[i].second;
        if (product > maxProduct) {
            maxProduct = product;
        }
    }
    return maxProduct;
}

int main() {
    Tuple list[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    int size = sizeof(list) / sizeof(list[0]);
    int result = maxProductFromPairs(list, size);
    printf("Maximum product: %d\n", result);
    return 0;
}