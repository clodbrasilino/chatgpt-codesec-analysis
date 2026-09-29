#include <stdint.h>
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
        if (!contains_pair(list1, i, &list1[i]) &&
            contains_pair(list2, length2, &list1[i]) &&
            contains_pair(list3, length3, &list1[i])) {
            ++count;
        }
    }

    return count;
}

static int allocate_pairs(Pair **list, size_t length)
{
    if (length == 0) {
        *list = NULL;
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

int main(void)
{
    size_t length1;
    size_t length2;
    size_t length3;
    Pair *list1 = NULL;
    Pair *list2 = NULL;
    Pair *list3 = NULL;

    if (scanf("%zu %zu %zu", &length1, &length2, &length3) != 3) {
        return EXIT_FAILURE;
    }

    if (!allocate_pairs(&list1, length1) ||
        !allocate_pairs(&list2, length2) ||
        !allocate_pairs(&list3, length3)) {
        free(list1);
        free(list2);
        free(list3);
        return EXIT_FAILURE;
    }

    if (!read_pairs(list1, length1) ||
        !read_pairs(list2, length2) ||
        !read_pairs(list3, length3)) {
        free(list1);
        free(list2);
        free(list3);
        return EXIT_FAILURE;
    }

    size_t count = count_same_pairs(list1, length1,
                                    list2, length2,
                                    list3, length3);

    int status = printf("%zu\n", count);

    free(list1);
    free(list2);
    free(list3);

    return status < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}