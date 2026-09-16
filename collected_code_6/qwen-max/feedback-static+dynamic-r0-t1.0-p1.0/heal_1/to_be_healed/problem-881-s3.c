#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int sumFirstEvenOdd(int *arr, int n, int *even, int *odd) {
    *even = INT_MAX;
    *odd = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (arr[i] % 2 == 0 && *even == INT_MAX) {
            *even = arr[i];
        } else if (arr[i] % 2 != 0 && *odd == INT_MAX) {
            *odd = arr[i];
        }
        if (*even != INT_MAX && *odd != INT_MAX) {
            return *even + *odd;
        }
    }
    return -1; // Indicates at least one of the first even or odd numbers was not found
}

int main() {
    int arr[] = {3, 5, 8, 1, 2, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int even, odd;
    int result = sumFirstEvenOdd(arr, n, &even, &odd);
    if (result != -1) {
        printf("Sum of the first even and odd number: %d\n", result);
    } else {
        printf("One of the first even or odd numbers was not found.\n");
    }
    return 0;
}