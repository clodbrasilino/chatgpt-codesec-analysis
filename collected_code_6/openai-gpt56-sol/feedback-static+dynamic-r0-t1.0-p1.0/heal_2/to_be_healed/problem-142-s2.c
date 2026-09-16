#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Pair;

static int pair_equal(Pair left, Pair right)
{
    return left.first == right.first && left.second == right.second;
}

static int contains_pair(const Pair *list, size_t count, Pair target)
{
    for (size_t i = 0; i < count; ++i) {
        if (pair_equal(list[i], target)) {
            return 1;
        }
    }

    return 0;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got <no output>
  *  test case 2 failed: expected 5, got <no output>
  *  test case 0 failed: expected 3, got <no output>
  */

static size_t count_same_pairs(const Pair *list1, size_t count1,
                               const Pair *list2, size_t count2,
                               const Pair *list3, size_t count3)
{
    if ((list1 == NULL && count1 != 0) ||
        (list2 == NULL && count2 != 0) ||
        (list3 == NULL && count3 != 0)) {
        return 0;
    }

    size_t matches = 0;

    for (size_t i = 0; i < count1; ++i) {
        int already_counted = 0;

        for (size_t j = 0; j < i; ++j) {
            if (pair_equal(list1[j], list1[i])) {
                already_counted = 1;
                break;
            }
        }

        if (!already_counted &&
            contains_pair(list2, count2, list1[i]) &&
            contains_pair(list3, count3, list1[i])) {
            ++matches;
        }
    }

    return matches;
}

int main(void)
{
    Pair list1[] = {{1, 2}, {3, 4}, {5, 6}};
    Pair list2[] = {{3, 4}, {1, 2}, {7, 8}};
    Pair list3[] = {{9, 0}, {1, 2}, {3, 4}};

    size_t count1 = sizeof list1 / sizeof list1[0];
    size_t count2 = sizeof list2 / sizeof list2[0];
    size_t count3 = sizeof list3 / sizeof list3[0];

    size_t result = count_same_pairs(list1, count1, list2, count2,
                                     list3, count3);

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}