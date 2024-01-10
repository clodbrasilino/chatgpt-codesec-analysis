#include <stdio.h>

int minProduct(const int array[], int n) {
    int min_prod = array[0] * array[1];

    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            int product = array[i] * array[j];
            if (product < min_prod)
                min_prod = product;
        }
    }

    return min_prod;
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    int size = sizeof(array) / sizeof(array[0]);
    int result = minProduct(array, size);
    printf("Minimum product: %d\n", result);

    return 0;
}