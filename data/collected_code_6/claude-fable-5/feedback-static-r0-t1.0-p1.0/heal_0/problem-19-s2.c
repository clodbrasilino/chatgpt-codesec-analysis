#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

bool contains_duplicate(const int *arr, size_t size)
{
    int *copy = NULL;
    size_t i;
    bool found = false;

    if (arr == NULL || size < 2U) {
        return false;
    }

    if (size > SIZE_MAX / sizeof(int)) {
        return false;
    }

    copy = malloc(size * sizeof(int));
    if (copy == NULL) {
        return false;
    }

    for (i = 0U; i < size; i++) {
        copy[i] = arr[i];
    }

    qsort(copy, size, sizeof(int), compare_ints);

    for (i = 1U; i < size; i++) {
        if (copy[i] == copy[i - 1U]) {
            found = true;
            break;
        }
    }

    free(copy);
    return found;
}

int main(void)
{
    int data1[] = {1, 2, 3, 4, 5};
    int data2[] = {1, 2, 3, 2, 5};
    size_t size1 = sizeof(data1) / sizeof(data1[0]);
    size_t size2 = sizeof(data2) / sizeof(data2[0]);

    if (contains_duplicate(data1, size1)) {
        if (printf("Array 1 contains duplicates\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Array 1 does not contain duplicates\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (contains_duplicate(data2, size2)) {
        if (printf("Array 2 contains duplicates\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Array 2 does not contain duplicates\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}