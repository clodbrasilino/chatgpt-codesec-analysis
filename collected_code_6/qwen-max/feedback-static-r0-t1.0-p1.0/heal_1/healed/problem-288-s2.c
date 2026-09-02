#include <stdio.h>
#include <stdlib.h>

int modular_inverse(int a, int p) {
    int m0 = p;
    int y = 0, x = 1;

    if (p == 1)
        return 0;

    while (a > 1) {
        int q = a / p;
        if (p == 0 || a % p == 0) {
            return -1;
        }
        p = a % p;
        a = p + q * p;
        int t = y;
        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}

int count_self_modular_inverses(const int* arr, int n, int p) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (modular_inverse(arr[i], p) == arr[i])
            ++count;
    }
    return count;
}

int main() {
    const int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int p = 11;
    int result = count_self_modular_inverses(arr, n, p);
    printf("%d\n", result);
    return 0;
}