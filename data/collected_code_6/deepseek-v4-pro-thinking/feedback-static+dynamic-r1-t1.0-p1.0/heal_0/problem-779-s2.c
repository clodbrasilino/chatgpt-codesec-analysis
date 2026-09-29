#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    int *data;
    size_t length;
} List;

static bool list_equal(const List *a, const List *b) {
    if (a == NULL || b == NULL) {
        return false;
    }
    if (a->length != b->length) {
        return false;
    }
    if (a->length == 0) {
        return true;
    }
    if (a->data == NULL || b->data == NULL) {
        return false;
    }
    if (a->data == b->data) {
        return true;
    }
    for (size_t i = 0; i < a->length; ++i) {
        if (a->data[i] != b->data[i]) {
            return false;
        }
    }
    return true;
}

size_t count_unique_lists(const List *lists, size_t count) {
    if (lists == NULL && count > 0) {
        return 0;
    }

    size_t unique = 0;

    for (size_t i = 0; i < count; ++i) {
        bool duplicate = false;

        for (size_t j = 0; j < i; ++j) {
            if (list_equal(&lists[i], &lists[j])) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) {
            ++unique;
        }
    }

    return unique;
}

int main(void) {
    int data0[] = {1, 2, 3};
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5};
    int data3[] = {4, 5, 6};
    int data4[] = {1, 2, 3};

    List lists[] = {
        {data0, 3},
        {data1, 3},
        {data2, 2},
        {data3, 3},
        {data4, 3}
    };

    size_t result = count_unique_lists(lists, sizeof(lists) / sizeof(lists[0]));
    printf("%zu\n", result);

    return 0;
}