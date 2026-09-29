#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int compare_integers(const void *a, const void *b)
{
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

bool contains_duplicate(const int *arr, size_t size)
{
    if (arr == NULL || size <= 1) {
        return false;
    }

    int *sorted = malloc(size * sizeof(int));
    if (sorted == NULL) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        sorted[i] = arr[i];
    }

    qsort(sorted, size, sizeof(int), compare_integers);

    bool found = false;
    for (size_t i = 0; i < size - 1; i++) {
        if (sorted[i] == sorted[i + 1]) {
            found = true;
            break;
        }
    }

    free(sorted);
    return found;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 3};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    if (contains_duplicate(arr, size)) {
        printf("Array contains duplicates\n");
    } else {
        printf("Array does not contain duplicates\n");
    }

    return 0;
}