#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

void power_elements(long *arr, int size, int n) {
    for (int i = 0; i < size; i++) {
        double result = pow((double)arr[i], n);
        if (result > LONG_MAX || result < LONG_MIN) {
            arr[i] = 0;
        } else {
            arr[i] = (long)result;
        }
    }
}

int main() {
    int size;
    printf("Enter the number of elements: ");
    scanf("%d", &size);

    long *arr = (long *)malloc(size * sizeof(long));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter the elements:\n");
    for (int i = 0; i < size; i++) {
        scanf("%ld", &arr[i]);
    }

    int n;
    printf("Enter the power: ");
    scanf("%d", &n);

    power_elements(arr, size, n);

    printf("Result after powering each element by %d:\n", n);
    for (int i = 0; i < size; i++) {
        printf("%ld ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}