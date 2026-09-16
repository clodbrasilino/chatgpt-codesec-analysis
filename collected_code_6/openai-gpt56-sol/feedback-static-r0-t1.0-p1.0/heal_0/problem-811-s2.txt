#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

static bool tuple_lists_are_identical(
    const Tuple *list1,
    size_t length1,
    const Tuple *list2,
    size_t length2
) {
    size_t i;

    if (length1 != length2) {
        return false;
    }

    if (length1 == 0U) {
        return true;
    }

    if (list1 == NULL || list2 == NULL) {
        return false;
    }

    for (i = 0U; i < length1; ++i) {
        if (list1[i].first != list2[i].first ||
            list1[i].second != list2[i].second) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const Tuple list1[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    const Tuple list2[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    const size_t length1 = sizeof(list1) / sizeof(list1[0]);
    const size_t length2 = sizeof(list2) / sizeof(list2[0]);

    if (tuple_lists_are_identical(list1, length1, list2, length2)) {
        if (puts("The lists are identical.") == EOF) {
            return 1;
        }
    } else {
        if (puts("The lists are not identical.") == EOF) {
            return 1;
        }
    }

    return 0;
}