#include <stdio.h>
#include <stdbool.h>

bool isRepeated(int arr[], int index) {
    for(int i = 0; i < index; i++) {
        if(arr[i] == arr[index]) {
            return true;
        }
    }
    return false;
}

int productOfNonRepeated(int arr[], int size) {
    int product = 1;
    for(int i = 0; i < size; i++) {
        if(!isRepeated(arr, i)) {
            product *= arr[i];
        }
    }
    return product;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Product of non-repeated elements: %d\n", productOfNonRepeated(arr, size));
    return 0;
}