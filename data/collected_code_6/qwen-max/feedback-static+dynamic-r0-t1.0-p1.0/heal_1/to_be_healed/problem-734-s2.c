#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
long long sum_of_products(int *arr, int n) {
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        long long product = 1;
        for (int j = i; j < n; ++j) {
            product *= arr[j];
            sum += product;
        }
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    long long result = sum_of_products(arr, n);
    printf("Sum of products of all possible subarrays: %lld\n", result);
    return 0;
}