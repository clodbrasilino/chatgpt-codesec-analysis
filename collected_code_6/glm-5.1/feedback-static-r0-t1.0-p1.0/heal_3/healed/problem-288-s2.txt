#include <stdio.h>
#include <stdlib.h>

int modular_inverse(int a, int p) {
    if (a <= 0 || p <= 1) {
        return 0;
    }
    int result = 1;
    int base = a % p;
    int exponent = p - 2;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % p;
        }
        exponent /= 2;
        base = (base * base) % p;
    }
    return result;
}

int count_elements_with_self_inverse(const int *arr, int n, int p) {
    if (arr == NULL || n < 0 || p <= 0) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            int inv = modular_inverse(arr[i], p);
            int val = arr[i] % p;
            if (inv == val) {
                count++;
            }
        }
    }
    return count;
}

int main(int argc, char const * const *argv) {
    if (argc < 4) {
        return 1;
    }
    int p = atoi(argv[1]);
    int n = atoi(argv[2]);
    if (n <= 0 || n + 3 > argc) {
        return 1;
    }
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[3 + i]);
    }
    int result = count_elements_with_self_inverse(arr, n, p);
    printf("%d\n", result);
    free(arr);
    return 0;
}