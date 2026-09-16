#include <stdio.h>
#include <stdlib.h>

int find_kth_element(const int *a, size_t m, const int *b, size_t n, size_t k, int *result)
{
    size_t i = 0;
    size_t j = 0;
    size_t count = 0;
    int current = 0;

    if (result == NULL) {
        return -1;
    }
    if (a == NULL && m > 0) {
        return -1;
    }
    if (b == NULL && n > 0) {
        return -1;
    }
    if (k == 0 || k > m + n) {
        return -1;
    }

    while (count < k) {
        if (i < m && j < n) {
            if (a[i] <= b[j]) {
                current = a[i];
                i++;
            } else {
                current = b[j];
                j++;
            }
        } else if (i < m) {
            current = a[i];
            i++;
        } else {
            current = b[j];
            j++;
        }
        count++;
    }

    *result = current;
    return 0;
}

int main(void)
{
    int arr1[] = {2, 3, 6, 7, 9};
    int arr2[] = {1, 4, 8, 10};
    size_t m = sizeof(arr1) / sizeof(arr1[0]);
    size_t n = sizeof(arr2) / sizeof(arr2[0]);
    size_t k = 5;
    int result = 0;

    if (find_kth_element(arr1, m, arr2, n, k, &result) != 0) {
        fprintf(stderr, "Error: invalid input parameters\n");
        return EXIT_FAILURE;
    }

    if (printf("The %zu-th element is %d\n", k, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}