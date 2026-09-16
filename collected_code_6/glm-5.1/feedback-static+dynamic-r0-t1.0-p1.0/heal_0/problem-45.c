#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int find_array_gcd(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    int result = arr[0];
    if (result < 0) {
        result = -result;
    }
    for (int i = 1; i < n; i++) {
        int current = arr[i];
        if (current < 0) {
            current = -current;
        }
        result = gcd(result, current);
        if (result == 1) {
            break;
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    int n = argc - 1;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        long val = strtol(argv[i + 1], NULL, 10);
        if (val > 2147483647 || val < -2147483648) {
            free(arr);
            return 1;
        }
        arr[i] = (int)val;
    }
    int result = find_array_gcd(arr, n);
    printf("%d\n", result);
    free(arr);
    return 0;
}