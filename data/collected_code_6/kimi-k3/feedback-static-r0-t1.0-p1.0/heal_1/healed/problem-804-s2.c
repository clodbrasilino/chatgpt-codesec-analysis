#include <stdio.h>
#include <stdbool.h>

bool is_product_even(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            return true;
        }
    }
    return false;
}

int main(void) {
    int size;
    printf("Enter the number of elements: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("Invalid input.\n");
        return 1;
    }
    
    int arr[size];
    printf("Enter %d integers: ", size);
    for (int i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
    }
    
    if (is_product_even(arr, size)) {
        printf("The product is even.\n");
    } else {
        printf("The product is odd.\n");
    }
    
    return 0;
}