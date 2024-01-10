#include <stdio.h>

int findProduct(const int arr[], int size) {
    int product = 1;

    for (int i = 0; i < size; i++) {
        int count = 0;

        for (int j = 0; j < size; j++) {
            if (arr[i] == arr[j])
                count++;
        }
        
        if (count == 1)
            product *= arr[i];
    }

    return product;
}

int main() {
    int arr[] = {5, 7, 2, 7, 3, 2, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = findProduct(arr, size);
    printf("Product of non-repeated elements: %d", result);

    return 0;
}