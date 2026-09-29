#include <stdio.h>
#include <stdlib.h>

long long productOfUniqueNumbers(int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return 0;
    }

    long long product = 1;
    int has_unique = 0;

    for (int i = 0; i < size; i++) {
        int is_unique = 1;
        for (int j = 0; j < i; j++) {
            if (arr[i] == arr[j]) {
                is_unique = 0;
                break;
            }
        }
        if (is_unique) {
            product *= arr[i];
            has_unique = 1;
        }
    }

    return has_unique ? product : 0;
}

int main(void) {
    int arr[] = {1, 2, 2, 3, 4, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    long long result = productOfUniqueNumbers(arr, size);
    printf("Product of unique numbers: %lld\n", result);

    int empty_arr[] = {0};
    long long empty_result = productOfUniqueNumbers(NULL, 0);
    printf("Product of NULL or empty array: %lld\n", empty_result);

    return 0;
}