#include <stdio.h>
#include <limits.h>

struct Tuple {
    int first;
    int second;
};

int minProduct(struct Tuple arr[], int n) {
    int minProduct = INT_MAX;
    for (int i = 0; i < n; i++) {
        int product = arr[i].first * arr[i].second;
        if (product < minProduct) {
            minProduct = product;
        }
    }
    return minProduct;
}

int main() {
    struct Tuple array[] = {{4, 7}, {2, 5}, {3, 2}};
    int n = sizeof(array) / sizeof(array[0]);
    int min_prod = minProduct(array, n);
    printf("Minimum Product is %d", min_prod);
    return 0;
}