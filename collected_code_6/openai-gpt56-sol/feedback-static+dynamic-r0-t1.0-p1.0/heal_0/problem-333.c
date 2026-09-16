#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

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
    if (list == NULL && count != 0U) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if (list[i].elements == NULL || list[i].length < 2U) {
            return -1;
        }
    }

    qsort(list, count, sizeof(*list), compare_sublists);
    return 0;
}

int main(void)
{
    int values[][3] = {
        {1, 7, 3},
        {2, 4, 8},
        {5, 9, 6},
        {0, 2, 1}
    };
    const size_t count = sizeof(values) / sizeof(values[0]);
    Sublist list[count];

    for (size_t i = 0; i < count; ++i) {
        list[i].elements = values[i];
        list[i].length = sizeof(values[i]) / sizeof(values[i][0]);
    }

    if (sort_by_second_element(list, count) != 0) {
        fputs("Unable to sort the list.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < list[i].length; ++j) {
            if (printf("%d%s", list[i].elements[j],
                       j + 1U == list[i].length ? "\n" : " ") < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}