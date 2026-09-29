#include <stdio.h>
#include <stdbool.h>

bool is_product_even(int arr[], int n) {
    if (n <= 0) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            return true;
        }
    }
    return false;
}

int main(void) {
    int arr[] = {1, 3, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (is_product_even(arr, n)) {
        printf("The product of the numbers is even.\n");
    } else {
        printf("The product of the numbers is odd.\n");
    }
    return 0;
}