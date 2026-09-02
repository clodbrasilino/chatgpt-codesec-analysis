#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void power_elements(long *arr, int size, int n) {
    for (int i = 0; i < size; i++) {
        arr[i] = (long)pow(arr[i], n);
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