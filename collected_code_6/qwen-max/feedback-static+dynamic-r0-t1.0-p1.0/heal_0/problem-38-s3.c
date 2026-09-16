#include <stdio.h>
#include <stdlib.h>

double find_division(int *arr, int n) {
    int first_even = -1, first_odd = -1;

    for (int i = 0; i < n; i++) {
        if (first_even == -1 && arr[i] % 2 == 0) {
            first_even = arr[i];
        }
        if (first_odd == -1 && arr[i] % 2 != 0) {
            first_odd = arr[i];
        }
        if (first_even != -1 && first_odd != -1) {
            break;
        }
    }

    if (first_even == -1 || first_odd == -1) {
        return 0.0;
    }

    return (double)first_even / (double)first_odd;
}

int main() {
    int arr[] = {5, 3, 2, 8, 1, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    double result = find_division(arr, n);
    printf("The division of the first even and odd number: %.2f\n", result);
    return 0;
}