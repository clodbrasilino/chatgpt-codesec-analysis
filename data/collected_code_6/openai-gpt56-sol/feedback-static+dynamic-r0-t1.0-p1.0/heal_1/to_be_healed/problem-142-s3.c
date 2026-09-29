#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

static int pairs_equal(const Pair *left, const Pair *right)
{
    return left->first == right->first && left->second == right->second;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got <no output>
  *  test case 2 failed: expected 5, got <no output>
  *  test case 0 failed: expected 3, got <no output>
  */

static size_t count_same_pairs(const Pair *list1, size_t length1,
                               const Pair *list2, size_t length2,
                               const Pair *list3, size_t length3)
{
    size_t count = 0;

    for (size_t i = 0; i < length1; ++i) {
        for (size_t j = 0; j < length2; ++j) {
            if (!pairs_equal(&list1[i], &list2[j])) {
                continue;
            }

            for (size_t k = 0; k < length3; ++k) {
                if (pairs_equal(&list1[i], &list3[k])) {
                    ++count;
                }
            }
        }
    }

    return count;
}

int main(void)
{
    const Pair list1[] = {{1, 2}, {3, 4}, {5, 6}};
    const Pair list2[] = {{3, 4}, {5, 6}, {7, 8}};
    const Pair list3[] = {{0, 1}, {3, 4}, {5, 6}};

    const size_t length1 = sizeof list1 / sizeof list1[0];
    const size_t length2 = sizeof list2 / sizeof list2[0];
    const size_t length3 = sizeof list3 / sizeof list3[0];

    const size_t count = count_same_pairs(list1, length1,
                                          list2, length2,
                                          list3, length3);

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}