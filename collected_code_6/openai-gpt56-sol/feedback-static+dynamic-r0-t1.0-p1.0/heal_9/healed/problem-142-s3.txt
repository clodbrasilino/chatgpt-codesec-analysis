#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

static int compare_pairs(const void *left, const void *right)
{
    const Pair *a = left;
    const Pair *b = right;

    if (a->first < b->first) {
        return -1;
    }
    if (a->first > b->first) {
        return 1;
    }
    if (a->second < b->second) {
        return -1;
    }
    if (a->second > b->second) {
        return 1;
    }
    return 0;
}

static int allocate_pairs(Pair **list, size_t length)
{
    *list = NULL;

    if (length == 0) {
        return 1;
    }

    if (length > SIZE_MAX / sizeof **list) {
        return 0;
    }

    *list = malloc(length * sizeof **list);
    return *list != NULL;
}

static int read_pairs(Pair *list, size_t length)
{
    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d %d", &list[i].first, &list[i].second) != 2) {
            return 0;
        }
    }

    return 1;
}

static int pairs_equal(const Pair *a, const Pair *b)
{
    return a->first == b->first && a->second == b->second;
}

static void skip_duplicates(const Pair *list, size_t length, size_t *index)
{
    Pair value = list[*index];

    do {
        ++*index;
    } while (*index < length && pairs_equal(&list[*index], &value));
}

static size_t count_same_pairs(Pair *list1, size_t length1,
                               Pair *list2, size_t length2,
                               Pair *list3, size_t length3)
{
    qsort(list1, length1, sizeof *list1, compare_pairs);
    qsort(list2, length2, sizeof *list2, compare_pairs);
    qsort(list3, length3, sizeof *list3, compare_pairs);

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    size_t count = 0;

    while (i < length1 && j < length2 && k < length3) {
        const Pair *maximum = &list1[i];

        if (compare_pairs(&list2[j], maximum) > 0) {
            maximum = &list2[j];
        }
        if (compare_pairs(&list3[k], maximum) > 0) {
            maximum = &list3[k];
        }

        int cmp1 = compare_pairs(&list1[i], maximum);
        int cmp2 = compare_pairs(&list2[j], maximum);
        int cmp3 = compare_pairs(&list3[k], maximum);

        if (cmp1 == 0 && cmp2 == 0 && cmp3 == 0) {
            ++count;
            skip_duplicates(list1, length1, &i);
            skip_duplicates(list2, length2, &j);
            skip_duplicates(list3, length3, &k);
        } else {
            if (cmp1 < 0) {
                skip_duplicates(list1, length1, &i);
            }
            if (cmp2 < 0) {
                skip_duplicates(list2, length2, &j);
            }
            if (cmp3 < 0) {
                skip_duplicates(list3, length3, &k);
            }
        }
    }

    return count;
}

int main(void)
{
    size_t length1;
    size_t length2;
    size_t length3;
    Pair *list1 = NULL;
    Pair *list2 = NULL;
    Pair *list3 = NULL;
    int status = EXIT_FAILURE;

    if (scanf("%zu %zu %zu", &length1, &length2, &length3) != 3) {
        goto cleanup;
    }

    if (!allocate_pairs(&list1, length1) ||
        !allocate_pairs(&list2, length2) ||
        !allocate_pairs(&list3, length3)) {
        goto cleanup;
    }

    if (!read_pairs(list1, length1) ||
        !read_pairs(list2, length2) ||
        !read_pairs(list3, length3)) {
        goto cleanup;
    }

    printf("%zu\n", count_same_pairs(list1, length1,
                                     list2, length2,
                                     list3, length3));
    status = EXIT_SUCCESS;

cleanup:
    free(list1);
    free(list2);
    free(list3);
    return status;
}