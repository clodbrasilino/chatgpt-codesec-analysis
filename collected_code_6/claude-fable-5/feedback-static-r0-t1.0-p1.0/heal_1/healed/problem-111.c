#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool contains(const int *arr, size_t len, int value)
{
    size_t i;

    if (arr == NULL) {
        return false;
    }

    for (i = 0; i < len; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

int find_common_elements(const int **lists, const size_t *lengths,
                         size_t num_lists, int **result, size_t *result_len)
{
    size_t i;
    size_t j;
    size_t count;
    int *common;

    if (lists == NULL || lengths == NULL || result == NULL ||
        result_len == NULL || num_lists == 0) {
        return -1;
    }

    for (i = 0; i < num_lists; i++) {
        if (lists[i] == NULL) {
            return -1;
        }
    }

    common = malloc(lengths[0] * sizeof(int));
    if (common == NULL) {
        return -1;
    }

    count = 0;
    for (i = 0; i < lengths[0]; i++) {
        int candidate = lists[0][i];
        bool in_all = true;

        if (contains(common, count, candidate)) {
            continue;
        }

        for (j = 1; j < num_lists; j++) {
            if (!contains(lists[j], lengths[j], candidate)) {
                in_all = false;
                break;
            }
        }

        if (in_all) {
            common[count] = candidate;
            count++;
        }
    }

    *result = common;
    *result_len = count;
    return 0;
}

int main(void)
{
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 3, 5, 7, 9};
    int list3[] = {0, 2, 3, 5, 8};
    int list4[] = {2, 3, 5, 6, 10};

    const int *lists[] = {list1, list2, list3, list4};
    const size_t lengths[] = {5, 5, 5, 5};
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    int *result = NULL;
    size_t result_len = 0;

    if (find_common_elements(lists, lengths, num_lists,
                             &result, &result_len) != 0) {
        fprintf(stderr, "Failed to find common elements\n");
        return EXIT_FAILURE;
    }

    if (result_len == 0) {
        printf("No common elements found\n");
    } else {
        printf("Common elements:");
        for (size_t i = 0; i < result_len; i++) {
            printf(" %d", result[i]);
        }
        printf("\n");
    }

    free(result);
    return EXIT_SUCCESS;
}