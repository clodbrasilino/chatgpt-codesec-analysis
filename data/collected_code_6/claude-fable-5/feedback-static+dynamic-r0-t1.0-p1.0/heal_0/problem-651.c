#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool contains(const int *tuple, size_t size, int value)
{
    size_t i;

    if (tuple == NULL) {
        return false;
    }

    for (i = 0; i < size; i++) {
        if (tuple[i] == value) {
            return true;
        }
    }

    return false;
}

bool is_subset(const int *sub, size_t sub_size, const int *super, size_t super_size)
{
    size_t i;

    if (sub_size == 0) {
        return true;
    }

    if (sub == NULL || super == NULL) {
        return false;
    }

    if (sub_size > super_size) {
        return false;
    }

    for (i = 0; i < sub_size; i++) {
        if (!contains(super, super_size, sub[i])) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int tuple_a[] = {1, 2, 3, 4, 5, 6, 7};
    int tuple_b[] = {2, 4, 6};
    int tuple_c[] = {2, 4, 8};
    size_t size_a = sizeof(tuple_a) / sizeof(tuple_a[0]);
    size_t size_b = sizeof(tuple_b) / sizeof(tuple_b[0]);
    size_t size_c = sizeof(tuple_c) / sizeof(tuple_c[0]);

    if (is_subset(tuple_b, size_b, tuple_a, size_a)) {
        if (printf("tuple_b is a subset of tuple_a\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("tuple_b is not a subset of tuple_a\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (is_subset(tuple_c, size_c, tuple_a, size_a)) {
        if (printf("tuple_c is a subset of tuple_a\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("tuple_c is not a subset of tuple_a\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}