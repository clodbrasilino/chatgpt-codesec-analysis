#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

static int pairs_equal(Pair a, Pair b)
{
    return a.first == b.first && a.second == b.second;
}

static size_t count_common_pairs(const Pair *list1, size_t count1,
                                 const Pair *list2, size_t count2,
                                 const Pair *list3, size_t count3)
{
    size_t common_count = 0;

    if ((list1 == NULL && count1 != 0U) ||
        (list2 == NULL && count2 != 0U) ||
        (list3 == NULL && count3 != 0U)) {
        return 0U;
    }

    for (size_t i = 0; i < count1; ++i) {
        int found_in_list2 = 0;
        int found_in_list3 = 0;
        int already_counted = 0;

        for (size_t j = 0; j < i; ++j) {
            if (pairs_equal(list1[i], list1[j])) {
                already_counted = 1;
                break;
            }
        }

        if (already_counted != 0) {
            continue;
        }

        for (size_t j = 0; j < count2; ++j) {
            if (pairs_equal(list1[i], list2[j])) {
                found_in_list2 = 1;
                break;
            }
        }

        if (found_in_list2 == 0) {
            continue;
        }

        for (size_t j = 0; j < count3; ++j) {
            if (pairs_equal(list1[i], list3[j])) {
                found_in_list3 = 1;
                break;
            }
        }

        if (found_in_list3 != 0) {
            ++common_count;
        }
    }

    return common_count;
}

int main(void)
{
    const Pair list1[] = {{1, 2}, {3, 4}, {5, 6}, {1, 2}};
    const Pair list2[] = {{5, 6}, {1, 2}, {7, 8}};
    const Pair list3[] = {{9, 10}, {1, 2}, {5, 6}};

    const size_t count1 = sizeof list1 / sizeof list1[0];
    const size_t count2 = sizeof list2 / sizeof list2[0];
    const size_t count3 = sizeof list3 / sizeof list3[0];

    const size_t result = count_common_pairs(list1, count1,
                                             list2, count2,
                                             list3, count3);

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}