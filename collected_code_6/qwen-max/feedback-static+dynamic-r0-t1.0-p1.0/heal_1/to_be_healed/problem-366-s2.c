#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int findLargestProduct(int *arr, int n) {
    if (n < 2) return INT_MIN;
    int maxProduct = INT_MIN;
    for (int i = 0; i < n - 1; ++i) {
        int product = arr[i] * arr[i + 1];
        if (product > maxProduct) {
            maxProduct = product;
        }
    }
    return maxProduct;
}

int main() {
    int arr[] = {3, 6, -2, -5, 7, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findLargestProduct(arr, n);
    if (result != INT_MIN) {
        printf("The largest product of adjacent elements is: %d\n", result);
    } else {
        printf("List contains less than two elements.\n");
    }
    return 0;
}