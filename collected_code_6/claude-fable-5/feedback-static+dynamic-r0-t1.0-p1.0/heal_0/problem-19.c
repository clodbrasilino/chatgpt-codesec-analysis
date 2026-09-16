#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool contains_duplicate(const int *arr, size_t n)
{
    size_t i;
    size_t j;

    if (arr == NULL || n < 2U) {
        return false;
    }

    for (i = 0U; i < n - 1U; i++) {
        for (j = i + 1U; j < n; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }

    return false;
}

int main(void)
{
    int data1[] = {3, 1, 4, 1, 5};
    int data2[] = {10, 20, 30, 40};
    size_t n1 = sizeof(data1) / sizeof(data1[0]);
    size_t n2 = sizeof(data2) / sizeof(data2[0]);

    if (contains_duplicate(data1, n1)) {
        if (printf("Array 1 contains duplicates.\n") < 0) {
            return 1;
        }
    } else {
        if (printf("Array 1 does not contain duplicates.\n") < 0) {
            return 1;
        }
    }

    if (contains_duplicate(data2, n2)) {
        if (printf("Array 2 contains duplicates.\n") < 0) {
            return 1;
        }
    } else {
        if (printf("Array 2 does not contain duplicates.\n") < 0) {
            return 1;
        }
    }

    return 0;
}