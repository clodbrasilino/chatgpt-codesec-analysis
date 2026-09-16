#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static bool contains_sorted(const int *values, size_t count, int target)
{
    size_t left = 0;
    size_t right = count;

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (values[middle] == target) {
            return true;
        }

        if (values[middle] < target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return false;
}

static int *find_common_elements(const int *const lists[],
                                 const size_t lengths[],
                                 size_t list_count,
                                 size_t *result_count)
{
    int *result = NULL;
    int **copies = NULL;
    size_t smallest = 0;
    size_t output_count = 0;

    if (result_count == NULL) {
        return NULL;
    }

    *result_count = 0;

    if (lists == NULL || lengths == NULL || list_count == 0) {
        return NULL;
    }

    for (size_t i = 0; i < list_count; ++i) {
        if (lengths[i] == 0) {
            return NULL;
        }

        if (lists[i] == NULL || lengths[i] > SIZE_MAX / sizeof(int)) {
            return NULL;
        }

        if (lengths[i] < lengths[smallest]) {
            smallest = i;
        }
    }

    if (list_count > SIZE_MAX / sizeof(*copies)) {
        return NULL;
    }

    copies = calloc(list_count, sizeof(*copies));
    if (copies == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < list_count; ++i) {
        copies[i] = malloc(lengths[i] * sizeof(*copies[i]));
        if (copies[i] == NULL) {
            goto cleanup;
        }

        for (size_t j = 0; j < lengths[i]; ++j) {
            copies[i][j] = lists[i][j];
        }

        qsort(copies[i], lengths[i], sizeof(*copies[i]), compare_ints);
    }

    result = malloc(lengths[smallest] * sizeof(*result));
    if (result == NULL) {
        goto cleanup;
    }

    for (size_t i = 0; i < lengths[smallest]; ++i) {
        int candidate = copies[smallest][i];
        bool common = true;

        if (i > 0 && candidate == copies[smallest][i - 1]) {
            continue;
        }

        for (size_t j = 0; j < list_count; ++j) {
            if (j != smallest &&
                !contains_sorted(copies[j], lengths[j], candidate)) {
                common = false;
                break;
            }
        }

        if (common) {
            result[output_count++] = candidate;
        }
    }

    *result_count = output_count;

cleanup:
    if (copies != NULL) {
        for (size_t i = 0; i < list_count; ++i) {
            free(copies[i]);
        }
        free(copies);
    }

    if (*result_count == 0) {
        free(result);
        result = NULL;
    }

    return result;
}

int main(void)
{
    const int list1[] = {1, 2, 2, 3, 4, 5};
    const int list2[] = {2, 3, 5, 7};
    const int list3[] = {0, 2, 3, 5, 8};
    const int list4[] = {2, 3, 5, 9};

    const int *lists[] = {list1, list2, list3, list4};
    const size_t lengths[] = {
        sizeof(list1) / sizeof(list1[0]),
        sizeof(list2) / sizeof(list2[0]),
        sizeof(list3) / sizeof(list3[0]),
        sizeof(list4) / sizeof(list4[0])
    };

    size_t common_count = 0;
    int *common = find_common_elements(
        lists,
        lengths,
        sizeof(lists) / sizeof(lists[0]),
        &common_count
    );

    if (common == NULL && common_count == 0) {
        puts("No common elements found.");
        return EXIT_SUCCESS;
    }

    for (size_t i = 0; i < common_count; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", common[i]) < 0) {
            free(common);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(common);
        return EXIT_FAILURE;
    }

    free(common);
    return EXIT_SUCCESS;
}