#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

static bool binary_search_int(const int *arr, size_t n, int key)
{
    size_t low = 0;
    size_t high = n;

    while (low < high) {
        size_t mid = low + (high - low) / 2;

        if (arr[mid] == key) {
            return true;
        }
        if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return false;
}

static bool is_subset(const int *set, size_t set_len, const int *subset, size_t subset_len)
{
    int *sorted_set = NULL;
    size_t i;
    bool result = true;

    if (subset_len == 0) {
        return true;
    }
    if (set == NULL || subset == NULL || set_len == 0) {
        return false;
    }
    if (subset_len > set_len) {
        return false;
    }

    sorted_set = malloc(set_len * sizeof(*sorted_set));
    if (sorted_set == NULL) {
        return false;
    }

    for (i = 0; i < set_len; i++) {
        sorted_set[i] = set[i];
    }

    qsort(sorted_set, set_len, sizeof(*sorted_set), compare_ints);

    for (i = 0; i < subset_len; i++) {
        if (!binary_search_int(sorted_set, set_len, subset[i])) {
            result = false;
            break;
        }
    }

    free(sorted_set);
    return result;
}

int main(void)
{
    int arr1[] = { 11, 1, 13, 21, 3, 7 };
    int arr2[] = { 11, 3, 7, 1 };
    int arr3[] = { 11, 3, 7, 100 };
    size_t len1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t len2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t len3 = sizeof(arr3) / sizeof(arr3[0]);

    if (is_subset(arr1, len1, arr2, len2)) {
        if (printf("arr2 is a subset of arr1\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("arr2 is not a subset of arr1\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (is_subset(arr1, len1, arr3, len3)) {
        if (printf("arr3 is a subset of arr1\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("arr3 is not a subset of arr1\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}