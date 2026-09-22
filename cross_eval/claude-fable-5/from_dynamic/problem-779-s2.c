#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool lists_equal(const int *a, size_t len_a, const int *b, size_t len_b)
{
    size_t i;

    if (a == NULL || b == NULL) {
        return false;
    }

    if (len_a != len_b) {
        return false;
    }

    for (i = 0; i < len_a; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

static size_t count_unique_lists(const int **lists, const size_t *lengths, size_t count)
{
    size_t unique = 0;
    size_t i;
    size_t j;
    bool seen;

    if (lists == NULL || lengths == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (lists[i] == NULL) {
            continue;
        }
        seen = false;
        for (j = 0; j < i; j++) {
            if (lists[j] == NULL) {
                continue;
            }
            if (lists_equal(lists[i], lengths[i], lists[j], lengths[j])) {
                seen = true;
                break;
            }
        }
        if (!seen) {
            unique++;
        }
    }

    return unique;
}

int main(void)
{
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5};
    int list3[] = {1, 2, 3};
    int list4[] = {6, 7, 8, 9};
    int list5[] = {4, 5};

    const int *lists[5];
    size_t lengths[5];
    size_t result;

    lists[0] = list1;
    lists[1] = list2;
    lists[2] = list3;
    lists[3] = list4;
    lists[4] = list5;

    lengths[0] = sizeof(list1) / sizeof(list1[0]);
    lengths[1] = sizeof(list2) / sizeof(list2[0]);
    lengths[2] = sizeof(list3) / sizeof(list3[0]);
    lengths[3] = sizeof(list4) / sizeof(list4[0]);
    lengths[4] = sizeof(list5) / sizeof(list5[0]);

    result = count_unique_lists(lists, lengths, 5U);

    if (printf("Number of unique lists: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}