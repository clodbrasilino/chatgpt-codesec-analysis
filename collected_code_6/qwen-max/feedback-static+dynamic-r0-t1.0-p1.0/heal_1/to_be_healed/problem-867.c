#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
bool is_sum_even(int *arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
    }
    return (sum % 2 == 0);
}

int min_addition_to_make_even(int *arr, int n) {
    if (is_sum_even(arr, n)) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    int arr[] = {1, 3, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = min_addition_to_make_even(arr, n);
    printf("Minimum number to add: %d\n", result);
    return 0;
}