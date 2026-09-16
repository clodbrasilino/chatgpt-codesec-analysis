#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int first;
    int second;
} Pair;

static int compare_pairs(const void *lhs, const void *rhs)
{
    const Pair *left = lhs;
    const Pair *right = rhs;

    if (left->first < right->first) {
        return -1;
    }
    if (left->first > right->first) {
        return 1;
    }
    if (left->second < right->second) {
        return -1;
    }
    if (left->second > right->second) {
        return 1;
    }
    return 0;
}

static size_t count_same_pairs(Pair *list1, size_t count1,
                               Pair *list2, size_t count2,
                               Pair *list3, size_t count3)
{
    qsort(list1, count1, sizeof(*list1), compare_pairs);
    qsort(list2, count2, sizeof(*list2), compare_pairs);
    qsort(list3, count3, sizeof(*list3), compare_pairs);

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    size_t matches = 0;

    while (i < count1 && j < count2 && k < count3) {
        int cmp12 = compare_pairs(&list1[i], &list2[j]);
        int cmp13 = compare_pairs(&list1[i], &list3[k]);

        if (cmp12 == 0 && cmp13 == 0) {
            Pair value = list1[i];
            ++matches;

            while (i < count1 && compare_pairs(&list1[i], &value) == 0) {
                ++i;
            }
            while (j < count2 && compare_pairs(&list2[j], &value) == 0) {
                ++j;
            }
            while (k < count3 && compare_pairs(&list3[k], &value) == 0) {
                ++k;
            }
        } else {
            Pair minimum = list1[i];

            if (compare_pairs(&list2[j], &minimum) < 0) {
                minimum = list2[j];
            }
            if (compare_pairs(&list3[k], &minimum) < 0) {
                minimum = list3[k];
            }

            while (i < count1 && compare_pairs(&list1[i], &minimum) == 0) {
                ++i;
            }
            while (j < count2 && compare_pairs(&list2[j], &minimum) == 0) {
                ++j;
            }
            while (k < count3 && compare_pairs(&list3[k], &minimum) == 0) {
                ++k;
            }
        }
    }

    return matches;
}

static int read_pairs(Pair *list, size_t count)
{
    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d %d", &list[i].first, &list[i].second) != 2) {
            return 0;
        }
    }
    return 1;
}

static Pair *allocate_pairs(size_t count)
{
    if (count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(Pair)) {
        return NULL;
    }

    return malloc(count * sizeof(Pair));
}

int main(void)
{
    size_t count1;
    size_t count2;
    size_t count3;

    if (scanf("%zu %zu %zu", &count1, &count2, &count3) != 3) {
        return EXIT_FAILURE;
    }

    Pair *list1 = allocate_pairs(count1);
    Pair *list2 = allocate_pairs(count2);
    Pair *list3 = allocate_pairs(count3);

    if ((count1 > 0 && list1 == NULL) ||
        (count2 > 0 && list2 == NULL) ||
        (count3 > 0 && list3 == NULL)) {
        free(list1);
        free(list2);
        free(list3);
        return EXIT_FAILURE;
    }

    if (!read_pairs(list1, count1) ||
        !read_pairs(list2, count2) ||
        !read_pairs(list3, count3)) {
        free(list1);
        free(list2);
        free(list3);
        return EXIT_FAILURE;
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