#include <stdio.h>
#include <stdlib.h>

long long product_of_first_even_odd(int *arr, int size, int *status) {
    if (arr == NULL || size <= 0) {
        *status = -1;
        return 0;
    }

    int *even = NULL;
    int *odd = NULL;

    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            even = &arr[i];
            break;
        }
    }

    for (int i = 0; i < size; i++) {
        if (abs(arr[i]) % 2 == 1) {
            odd = &arr[i];
            break;
        }
    }

    if (even == NULL || odd == NULL) {
        *status = -1;
        return 0;
    }

    *status = 0;
    return (long long)(*even) * (long long)(*odd);
}

int main(void) {
    int arr[] = {3, 5, 2, 8, 11, 14};
    int size = sizeof(arr) / sizeof(arr[0]);
    int status = 0;

    long long result = product_of_first_even_odd(arr, size, &status);

    if (status == 0) {
        printf("%lld\n", result);
    } else {
        printf("No product found\n");
    }

    return 0;
}