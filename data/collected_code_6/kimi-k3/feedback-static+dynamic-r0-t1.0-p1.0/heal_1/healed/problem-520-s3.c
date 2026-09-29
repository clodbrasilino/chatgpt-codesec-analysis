#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int gcd(int a, int b) {
    if (a == INT_MIN || b == INT_MIN) {
        return 0;
    }
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    int g = gcd(a, b);
    if (g == 0) {
        return 0;
    }
    long long quotient = (long long)a / g;
    long long product = quotient * b;
    if (product > INT_MAX || product < INT_MIN) {
        return 0;
    }
    return (int)product;
}

int findLCM(const int arr[], int n) {
    if (n <= 0) {
        return 0;
    }
    int result = arr[0];
    for (int i = 1; i < n; i++) {
        result = lcm(result, arr[i]);
    }
    return result;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    int *arr = (int *)malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input\n");
            free(arr);
            return 1;
        }
    }
    int result = findLCM(arr, n);
    printf("LCM of the given array elements is: %d\n", result);
    free(arr);
    return 0;
}