#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int contains(const int *list, size_t length, int value)
{
    size_t low = 0;
    size_t high = length;

    while (low < high) {
        size_t middle = low + (high - low) / 2;

        if (list[middle] == value) {
            return 1;
        }

        if (list[middle] < value) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }

    return 0;
}

static int find_common_elements(
    const int *const lists[],
    const size_t lengths[],
    size_t list_count,
    int **result,
    size_t *result_length)
{
    int **copies = NULL;
    int *common = NULL;
    size_t shortest = 0;
    size_t common_count = 0;
    size_t i;
    size_t j;

    if (lists == NULL || lengths == NULL || result == NULL ||
        result_length == NULL || list_count == 0) {
        return -1;
    }

    *result = NULL;
    *result_length = 0;

    for (i = 0; i < list_count; ++i) {
        if (lengths[i] == 0) {
            return 0;
        }

        if (lists[i] == NULL || lengths[i] > SIZE_MAX / sizeof(int)) {
            return -1;
        }

        if (lengths[i] < lengths[shortest]) {
            shortest = i;
        }
    }

    if (list_count > SIZE_MAX / sizeof(*copies)) {
        return -1;
    }

    copies = calloc(list_count, sizeof(*copies));
    if (copies == NULL) {
        return -1;
    }

    for (i = 0; i < list_count; ++i) {
        copies[i] = malloc(lengths[i] * sizeof(*copies[i]));
        if (copies[i] == NULL) {
            goto failure;
        }

        for (j = 0; j < lengths[i]; ++j) {
            copies[i][j] = lists[i][j];
        }

        qsort(copies[i], lengths[i], sizeof(*copies[i]), compare_ints);
    }

    common = malloc(lengths[shortest] * sizeof(*common));
    if (common == NULL) {
        goto failure;
    }

    for (i = 0; i < lengths[shortest]; ++i) {
        int value = copies[shortest][i];
        int present_everywhere = 1;

        if (i > 0 && value == copies[shortest][i - 1]) {
            continue;
        }

        for (j = 0; j < list_count; ++j) {
            if (j != shortest &&
                !contains(copies[j], lengths[j], value)) {
                present_everywhere = 0;
                break;
            }
        }

        if (present_everywhere) {
            common[common_count++] = value;
        }
    }

    for (i = 0; i < list_count; ++i) {
        free(copies[i]);
    }
    free(copies);

    if (common_count == 0) {
        free(common);
        return 0;
    }

    *result = common;
    *result_length = common_count;
    return 0;

failure:
    for (i = 0; i < list_count; ++i) {
        free(copies[i]);
    }
    free(copies);
    free(common);
    return -1;
}

int main(void)
{
    const int list1[] = {1, 2, 3, 4, 5};
    const int list2[] = {2, 3, 5, 7};
    const int list3[] = {0, 2, 3, 5, 8};
    const int list4[] = {2, 3, 4, 5, 9};
    const int *lists[] = {list1, list2, list3, list4};
    const size_t lengths[] = {
        sizeof(list1) / sizeof(list1[0]),
        sizeof(list2) / sizeof(list2[0]),
        sizeof(list3) / sizeof(list3[0]),
        sizeof(list4) / sizeof(list4[0])
    };
    int *common = NULL;
    size_t common_length = 0;
    size_t i;

    if (find_common_elements(
            lists,
            lengths,
            sizeof(lists) / sizeof(lists[0]),
            &common,
            &common_length) != 0) {
        fputs("Failed to find common elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < common_length; ++i) {
        if (printf("%d%s", common[i],
                   i + 1 == common_length ? "\n" : " ") < 0) {
            free(common);
            return EXIT_FAILURE;
        }
    }

    if (common_length == 0 && putchar('\n') == EOF) {
        free(common);
        return EXIT_FAILURE;
    }

    free(common);
    return EXIT_SUCCESS;
}