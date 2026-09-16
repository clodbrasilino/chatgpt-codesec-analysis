#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t length;
} Sublist;

static int compare_sublists(const void *lhs, const void *rhs)
{
    const Sublist *a = lhs;
    const Sublist *b = rhs;

    if (a->elements[1] < b->elements[1]) {
        return -1;
    }
    if (a->elements[1] > b->elements[1]) {
        return 1;
    }
    return 0;
}

static int sort_by_second_element(Sublist *list, size_t count)
{
    size_t i;

    if (list == NULL && count != 0) {
        return EINVAL;
    }

    for (i = 0; i < count; ++i) {
        if (list[i].elements == NULL || list[i].length < 2) {
            return EINVAL;
        }
    }

    qsort(list, count, sizeof(*list), compare_sublists);
    return 0;
}

int main(void)
{
    int values[][3] = {
        {1, 9, 3},
        {4, 2, 6},
        {7, 5, 8}
    };
    Sublist list[] = {
        {values[0], 3},
        {values[1], 3},
        {values[2], 3}
    };
    const size_t count = sizeof(list) / sizeof(list[0]);
    size_t i;
    size_t j;
    int result;

    result = sort_by_second_element(list, count);
    if (result != 0) {
        fprintf(stderr, "Sorting failed: invalid sublist\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        for (j = 0; j < list[i].length; ++j) {
            if (printf("%s%d", j == 0 ? "" : " ", list[i].elements[j]) < 0) {
                return EXIT_FAILURE;
            }
        }
        if (putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}