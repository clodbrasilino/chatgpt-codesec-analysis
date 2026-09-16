#include <stdio.h>
#include <stdlib.h>

static int find_kth_odd_then_even(const int *array, size_t length, size_t k, int *result)
{
    size_t count = 0;

    if (array == NULL || result == NULL || k == 0 || k > length) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] % 2 != 0) {
            ++count;
            if (count == k) {
                *result = array[i];
                return 0;
            }
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] % 2 == 0) {
            ++count;
            if (count == k) {
                *result = array[i];
                return 0;
            }
        }
    }

    return -1;
}

int main(void)
{
    int array[] = {2, 7, 4, 9, 1, 6, 3, 8};
    const size_t length = sizeof(array) / sizeof(array[0]);
    size_t k = 0;
    int result = 0;

    if (printf("Enter k (1-%zu): ", length) < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%zu", &k) != 1) {
        return EXIT_FAILURE;
    }

    if (find_kth_odd_then_even(array, length, k, &result) != 0) {
        if (fprintf(stderr, "Invalid value of k.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("The %zuth element is %d.\n", k, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}