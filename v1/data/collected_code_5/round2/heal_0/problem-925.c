#include <stdio.h>

long long product_Tuple(int *arr, int size) {
  
  if (!arr || size == 0) return 0;

    long long product = 1;
    int i;

    for (i = 0; i < size; i++) {
        product *= arr[i];
    }

    return product;
}

int main() {
    int Arr[] = {1, 2, 3, 4, 5};
    int Size = sizeof(Arr) / sizeof(Arr[0]);

    long long product = product_Tuple(Arr, Size);

    printf("Product of the given tuple is %lld\n", product);

    return 0;
}