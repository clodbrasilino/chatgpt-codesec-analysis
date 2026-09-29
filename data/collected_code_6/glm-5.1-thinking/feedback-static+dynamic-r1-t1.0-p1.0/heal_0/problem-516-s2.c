#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void radix_sort(int *arr, int n) {
    if (n <= 1) {
        return;
    }

    int *temp = malloc(n * sizeof(int));
    if (temp == NULL) {
        return;
    }

    for (int i = 0; i < n; i++) {
        arr[i] ^= 0x80000000;
    }

    for (int shift = 0; shift < 32; shift += 8) {
        int count[256] = {0};

        for (int i = 0; i < n; i++) {
            count[((unsigned int)arr[i] >> shift) & 0xFF]++;
        }

        for (int i = 1; i < 256; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            temp[--count[((unsigned int)arr[i] >> shift) & 0xFF]] = arr[i];
        }

        memcpy(arr, temp, n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        arr[i] ^= 0x80000000;
    }

    free(temp);
}

int main(void) {
    int arr[] = {170, 45, 75, -90, -802, 24, 2, 66, -5};
    int n = sizeof(arr) / sizeof(arr[0]);

    radix_sort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}