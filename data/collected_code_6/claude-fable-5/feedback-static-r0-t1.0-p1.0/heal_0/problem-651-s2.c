#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool contains(const int *arr, size_t len, int value)
{
    size_t i;

    if (arr == NULL) {
        return false;
    }

    for (i = 0; i < len; i++) {
        if (arr[i] == value) {
            return true;
        }
    }

    return false;
}

bool is_subset(const int *subset, size_t subset_len, const int *superset, size_t superset_len)
{
    size_t i;

    if (subset_len == 0) {
        return true;
    }

    if (subset == NULL || superset == NULL) {
        return false;
    }

    if (subset_len > superset_len) {
        return false;
    }

    for (i = 0; i < subset_len; i++) {
        if (!contains(superset, superset_len, subset[i])) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int tuple_a[] = {10, 4, 5, 6, 7};
    int tuple_b[] = {5, 10};
    int tuple_c[] = {5, 99};
    size_t len_a = sizeof(tuple_a) / sizeof(tuple_a[0]);
    size_t len_b = sizeof(tuple_b) / sizeof(tuple_b[0]);
    size_t len_c = sizeof(tuple_c) / sizeof(tuple_c[0]);
    bool result;

    result = is_subset(tuple_b, len_b, tuple_a, len_a);
    if (printf("tuple_b is %sa subset of tuple_a\n", result ? "" : "not ") < 0) {
        return 1;
    }

    result = is_subset(tuple_c, len_c, tuple_a, len_a);
    if (printf("tuple_c is %sa subset of tuple_a\n", result ? "" : "not ") < 0) {
        return 1;
    }

    return 0;
}