#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

static int pairs_equal(const Pair *left, const Pair *right)
{
    return left->first == right->first &&
           left->second == right->second;
}

static int contains_pair(const Pair *list, size_t length, const Pair *pair)
{
    for (size_t i = 0; i < length; ++i) {
        if (pairs_equal(&list[i], pair)) {
            return 1;
        }
    }

    return 0;
}

static size_t count_same_pairs(const Pair *list1, size_t length1,
                               const Pair *list2, size_t length2,
                               const Pair *list3, size_t length3)
{
    size_t count = 0;

    for (size_t i = 0; i < length1; ++i) {
        if (contains_pair(list2, length2, &list1[i]) &&
            contains_pair(list3, length3, &list1[i])) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    const Pair list1[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    const Pair list2[] = {
        {3, 4},
        {5, 6},
        {7, 8}
    };
    const Pair list3[] = {
        {0, 1},
        {3, 4},
        {5, 6}
    };

    const size_t length1 = sizeof list1 / sizeof list1[0];
    const size_t length2 = sizeof list2 / sizeof list2[0];
    const size_t length3 = sizeof list3 / sizeof list3[0];

    const size_t count = count_same_pairs(
        list1, length1,
        list2, length2,
        list3, length3
    );

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}