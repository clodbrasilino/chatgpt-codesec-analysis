#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    Pair *data;
    size_t length;
} PairList;

static int compare_pairs(const void *left, const void *right)
{
    const Pair *a = left;
    const Pair *b = right;

    if (a->first != b->first) {
        return (a->first > b->first) - (a->first < b->first);
    }

    return (a->second > b->second) - (a->second < b->second);
}

static int read_list(PairList *list)
{
    if (scanf("%zu", &list->length) != 1) {
        return 0;
    }

    list->data = NULL;

    if (list->length == 0) {
        return 1;
    }

    if (list->length > SIZE_MAX / sizeof *list->data) {
        return 0;
    }

    list->data = malloc(list->length * sizeof *list->data);
    if (list->data == NULL) {
        return 0;
    }

    for (size_t i = 0; i < list->length; ++i) {
        if (scanf("%d %d",
                  &list->data[i].first,
                  &list->data[i].second) != 2) {
            return 0;
        }
    }

    return 1;
}

static size_t next_distinct(const Pair *data, size_t length, size_t index)
{
    Pair current = data[index];

    do {
        ++index;
    } while (index < length &&
             data[index].first == current.first &&
             data[index].second == current.second);

    return index;
}

static size_t count_common_pairs(PairList lists[3])
{
    for (size_t n = 0; n < 3; ++n) {
        if (lists[n].length > 1) {
            qsort(lists[n].data, lists[n].length,
                  sizeof *lists[n].data, compare_pairs);
        }
    }

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    size_t count = 0;

    while (i < lists[0].length &&
           j < lists[1].length &&
           k < lists[2].length) {
        Pair *a = &lists[0].data[i];
        Pair *b = &lists[1].data[j];
        Pair *c = &lists[2].data[k];

        int ab = compare_pairs(a, b);
        int ac = compare_pairs(a, c);

        if (ab == 0 && ac == 0) {
            ++count;
            i = next_distinct(lists[0].data, lists[0].length, i);
            j = next_distinct(lists[1].data, lists[1].length, j);
            k = next_distinct(lists[2].data, lists[2].length, k);
            continue;
        }

        Pair *maximum = a;

        if (compare_pairs(b, maximum) > 0) {
            maximum = b;
        }
        if (compare_pairs(c, maximum) > 0) {
            maximum = c;
        }

        if (compare_pairs(a, maximum) < 0) {
            i = next_distinct(lists[0].data, lists[0].length, i);
        }
        if (compare_pairs(b, maximum) < 0) {
            j = next_distinct(lists[1].data, lists[1].length, j);
        }
        if (compare_pairs(c, maximum) < 0) {
            k = next_distinct(lists[2].data, lists[2].length, k);
        }
    }

    return count;
}

int main(void)
{
    PairList lists[3] = {{NULL, 0}, {NULL, 0}, {NULL, 0}};
    int status = EXIT_FAILURE;

    for (size_t i = 0; i < 3; ++i) {
        if (!read_list(&lists[i])) {
            goto cleanup;
        }
    }

    printf("%zu\n", count_common_pairs(lists));
    status = EXIT_SUCCESS;

cleanup:
    for (size_t i = 0; i < 3; ++i) {
        free(lists[i].data);
    }

    return status;
}