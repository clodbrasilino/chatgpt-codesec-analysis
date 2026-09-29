#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int get_max(const int *arr, size_t n)
{
    size_t i;
    int max_val = arr[0];

    for (i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

static int counting_sort_by_digit(int *arr, size_t n, int exp)
{
    int *output;
    size_t count[10];
    size_t i;
    size_t j;

    if (arr == NULL || n == 0 || exp <= 0) {
        return -1;
    }

    if (n > SIZE_MAX / sizeof(*output)) {
        return -1;
    }

    output = malloc(n * sizeof(*output));
    if (output == NULL) {
        return -1;
    }

    memset(count, 0, sizeof(count));

    for (i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (j = 1; j < 10; j++) {
        count[j] += count[j - 1];
    }

    i = n;
    while (i > 0) {
        i--;
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    memcpy(arr, output, n * sizeof(*arr));
    free(output);
    return 0;
}

static int radix_sort(int *arr, size_t n)
{
    int max_val;
    int exp;

    if (arr == NULL || n == 0) {
        return -1;
    }

    max_val = get_max(arr, n);
    if (max_val < 0) {
        return -1;
    }

    for (exp = 1; max_val / exp > 0; exp *= 10) {
        if (counting_sort_by_digit(arr, n, exp) != 0) {
            return -1;
        }
        if (exp > max_val / 10) {
            break;
        }
    }
    return 0;
}

int main(void)
{
    int data[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
    size_t n = sizeof(data) / sizeof(data[0]);
    size_t i;

    if (radix_sort(data, n) != 0) {
        fprintf(stderr, "Sorting failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++) {
        if (printf("%d ", data[i]) < 0) {
            return EXIT_FAILURE;
        }
    }
    if (printf("\n") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}