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
        if (contains_pair(list2, length2, &list1[i]) &&
            contains_pair(list3, length3, &list1[i]) &&
            !contains_pair(list1, i, &list1[i])) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    size_t length1;
    size_t length2;
    size_t length3;

    if (scanf("%zu %zu %zu", &length1, &length2, &length3) != 3) {
        return EXIT_FAILURE;
    }

    Pair *list1 = length1 > 0 ? malloc(length1 * sizeof *list1) : NULL;
    Pair *list2 = length2 > 0 ? malloc(length2 * sizeof *list2) : NULL;
    Pair *list3 = length3 > 0 ? malloc(length3 * sizeof *list3) : NULL;

    if ((length1 > 0 && list1 == NULL) ||
        (length2 > 0 && list2 == NULL) ||
        (length3 > 0 && list3 == NULL)) {
        free(list1);
        free(list2);
        free(list3);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length1; ++i) {
        if (scanf("%d %d", &list1[i].first, &list1[i].second) != 2) {
            free(list1);
            free(list2);
            free(list3);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length2; ++i) {
        if (scanf("%d %d", &list2[i].first, &list2[i].second) != 2) {
            free(list1);
            free(list2);
            free(list3);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length3; ++i) {
        if (scanf("%d %d", &list3[i].first, &list3[i].second) != 2) {
            free(list1);
            free(list2);
            free(list3);
            return EXIT_FAILURE;
        }
    }

    size_t count = count_same_pairs(list1, length1,
                                    list2, length2,
                                    list3, length3);

    int result = printf("%zu\n", count);

    free(list1);
    free(list2);
    free(list3);

    return result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}