#include <stdio.h>
#include <stdlib.h>

unsigned int get_max(const unsigned int *arr, size_t n) {
    unsigned int max = arr[0];
    for (size_t i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void counting_sort(unsigned int *arr, size_t n, unsigned int exp, unsigned int *output) {
    size_t count[10] = {0};

    for (size_t i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (size_t i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (size_t i = n; i > 0; i--) {
        output[count[(arr[i - 1] / exp) % 10] - 1] = arr[i - 1];
        count[(arr[i - 1] / exp) % 10]--;
    }

    for (size_t i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radix_sort(unsigned int *arr, size_t n) {
    if (arr == NULL || n <= 1) {
        return;
    }

    unsigned int max = get_max(arr, n);
    unsigned int *output = (unsigned int *)malloc(n * sizeof(unsigned int));
    if (output == NULL) {
        exit(EXIT_FAILURE);
    }

    unsigned int exp = 1;
    while (max / exp > 0) {
        counting_sort(arr, n, exp, output);
        if (max / exp < 10) {
            break;
        }
        exp *= 10;
    }

    free(output);
}

void print_array(const unsigned int *arr, size_t n) {
    if (arr == NULL) {
        return;
    }
    for (size_t i = 0; i < n; i++) {
        printf("%u ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    unsigned int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    radix_sort(arr, n);
    print_array(arr, n);

    return EXIT_SUCCESS;
}