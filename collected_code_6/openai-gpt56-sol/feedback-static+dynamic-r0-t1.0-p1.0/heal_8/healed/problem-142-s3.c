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

    if (a->first != b->first) {
        return (a->first > b->first) - (a->first < b->first);
    }

    return (a->second > b->second) - (a->second < b->second);
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
    if (length1 > 1) {
        qsort(list1, length1, sizeof *list1, compare_pairs);
    }
    if (length2 > 1) {
        qsort(list2, length2, sizeof *list2, compare_pairs);
    }
    if (length3 > 1) {
        qsort(list3, length3, sizeof *list3, compare_pairs);
    }

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    size_t count = 0;

    while (i < length1 && j < length2 && k < length3) {
        int comparison12 = compare_pairs(&list1[i], &list2[j]);
        int comparison13 = compare_pairs(&list1[i], &list3[k]);

        if (comparison12 == 0 && comparison13 == 0) {
            ++count;
            skip_duplicates(list1, length1, &i);
            skip_duplicates(list2, length2, &j);
            skip_duplicates(list3, length3, &k);
        } else if (comparison12 <= 0 && comparison13 <= 0) {
            skip_duplicates(list1, length1, &i);
        } else {
            int comparison23 = compare_pairs(&list2[j], &list3[k]);

            if (comparison12 >= 0 && comparison23 <= 0) {
                skip_duplicates(list2, length2, &j);
            } else {
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

    size_t count = count_same_pairs(list1, length1,
                                    list2, length2,
                                    list3, length3);

    if (printf("%zu\n", count) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(list1);
    free(list2);
    free(list3);
    return status;
}