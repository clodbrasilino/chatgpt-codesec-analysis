#include <stdio.h>
#include <stdlib.h>

long product_of_kth(int tuples[], int length, int k) {
    if (k < 0 || k >= length) return -1;
    long product = 1;
    for (int i = 0; i < length; i++) {
        product *= tuples[i * 3 + k];
    }
    return product;
}

int main() {
    int tuples[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int k = 1;
    int length = sizeof(tuples) / sizeof(tuples[0]) / 3;
    long result = product_of_kth(tuples, length, k);
    if (result != -1) {
        printf("The product of the %dth index in the given tuples is: %ld\n", k, result);
    } else {
        printf("Invalid index\n");
    }
    return 0;
}