#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int find_gcd(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    int result = arr[0] < 0 ? -arr[0] : arr[0];
    for (int i = 1; i < n; i++) {
        int val = arr[i] < 0 ? -arr[i] : arr[i];
        result = gcd(result, val);
        if (result == 1) {
            break;
        }
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
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
        char *endptr;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (*endptr != '\0' || val > 2147483647 || val < -2147483648) {
            free(arr);
            return 1;
        }
        arr[i] = (int)val;
    }
    int result = find_gcd(arr, n);
    printf("%d\n", result);
    free(arr);
    return 0;
}