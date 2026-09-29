#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

bool all_elements_same(const int *arr, size_t n)
{
    size_t i;

    if (arr == NULL || n == 0U) {
        return false;
    }

    for (i = 1U; i < n; i++) {
        if (arr[i] != arr[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int list1[] = { 5, 5, 5, 5, 5 };
    int list2[] = { 1, 2, 1, 1, 1 };
    size_t n1 = sizeof(list1) / sizeof(list1[0]);
    size_t n2 = sizeof(list2) / sizeof(list2[0]);

    if (all_elements_same(list1, n1)) {
        if (printf("list1: all elements are same\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("list1: elements are not same\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (all_elements_same(list2, n2)) {
        if (printf("list2: all elements are same\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("list2: elements are not same\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}