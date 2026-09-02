#include <stdio.h>
#include <stdbool.h>

bool is_modular_inverse_equal_to_itself(int x, int p) {
    if (x == 0) return false;
    int result = 1;
    for (int i = 1; i < p; ++i) {
        result = (result * x) % p;
        if (result == 1) return true;
    }
    return false;
}

int count_self_modular_inverse_elements(const int arr[], int n, int p) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (is_modular_inverse_equal_to_itself(arr[i], p)) {
            ++count;
        }
    }
    return count;
}

int main() {
    const int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int p = 11;

    int result = count_self_modular_inverse_elements(arr, n, p);

    printf("%d\n", result);
    return 0;
}