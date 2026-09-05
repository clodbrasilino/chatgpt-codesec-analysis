#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int find_array_gcd(const int *arr, int n) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }
    int n = argc - 1;
    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        long val = strtol(argv[i + 1], NULL, 10);
        if (val > INT_MAX || val < INT_MIN) {
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