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
    size_t count1;
    size_t count2;
    size_t count3;

    if (scanf("%zu %zu %zu", &count1, &count2, &count3) != 3) {
        return EXIT_FAILURE;
    }

    if (count1 > SIZE_MAX / sizeof(Pair) ||
        count2 > SIZE_MAX / sizeof(Pair) ||
        count3 > SIZE_MAX / sizeof(Pair)) {
        return EXIT_FAILURE;
    }

    Pair *list1 = count1 != 0 ? malloc(count1 * sizeof(*list1)) : NULL;
    Pair *list2 = count2 != 0 ? malloc(count2 * sizeof(*list2)) : NULL;
    Pair *list3 = count3 != 0 ? malloc(count3 * sizeof(*list3)) : NULL;

    if ((count1 != 0 && list1 == NULL) ||
        (count2 != 0 && list2 == NULL) ||
        (count3 != 0 && list3 == NULL)) {
        free(list1);
        free(list2);
        free(list3);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count1; ++i) {
        if (scanf("%d %d", &list1[i].first, &list1[i].second) != 2) {
            free(list1);
            free(list2);
            free(list3);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count2; ++i) {
        if (scanf("%d %d", &list2[i].first, &list2[i].second) != 2) {
            free(list1);
            free(list2);
            free(list3);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count3; ++i) {
        if (scanf("%d %d", &list3[i].first, &list3[i].second) != 2) {
            free(list1);
            free(list2);
            free(list3);
            return EXIT_FAILURE;
        }
    }

    size_t result = count_same_pairs(list1, count1, list2, count2,
                                     list3, count3);

    free(list1);
    free(list2);
    free(list3);

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}