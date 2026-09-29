#include <stdio.h>
#include <stdlib.h>

int modular_inverse(int a, int p) {
    if (p == 1)
        return 0;

    int m0 = p;
    int y = 0, x = 1;

    while (a > 1) {
        int q = a / p;
        int t = p;
        p = a % p;
        a = t;

        t = y;
        y = x - q * y;
        x = t;

        if (p == 0)
            break;
    }

    if (x < 0)
        x += m0;

    return (p == 1) ? x : 0;
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