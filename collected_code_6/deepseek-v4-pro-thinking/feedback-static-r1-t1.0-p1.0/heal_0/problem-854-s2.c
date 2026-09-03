#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void sift_down(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }
    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        sift_down(arr, n, smallest);
    }
}

void heapify(int arr[], int n) {
    int i;
    for (i = n / 2 - 1; i >= 0; i--) {
        sift_down(arr, n, i);
    }
}

int main(int argc, char **argv) {
    int n;
    int *arr;
    int i;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s num1 num2 ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    n = argc - 1;
    arr = malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++) {
        char *endptr;
        long val;

        errno = 0;
        val = strtol(argv[i + 1], &endptr, 10);
        if (errno != 0 || endptr == argv[i + 1] || *endptr != '\0' ||
            val < INT_MIN || val > INT_MAX) {
            fprintf(stderr, "Invalid integer: %s\n", argv[i + 1]);
            free(arr);
            return EXIT_FAILURE;
        }
        arr[i] = (int)val;
    }

    heapify(arr, n);

    for (i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");

    free(arr);
    return EXIT_SUCCESS;
}