#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool contains(const int *arr, size_t len, int value)
{
    for (size_t i = 0; i < len; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

int *find_common_elements(const int **lists, const size_t *lengths,
                          size_t num_lists, size_t *result_len)
{
    if (lists == NULL || lengths == NULL || result_len == NULL ||
        num_lists == 0) {
        if (result_len != NULL) {
            *result_len = 0;
        }
        return NULL;
    }

    for (size_t i = 0; i < num_lists; i++) {
        if (lists[i] == NULL) {
            *result_len = 0;
            return NULL;
        }
    }

    int *result = malloc(lengths[0] * sizeof(int));
    if (result == NULL) {
        *result_len = 0;
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < lengths[0]; i++) {
        int candidate = lists[0][i];
        if (contains(result, count, candidate)) {
            continue;
        }
        bool in_all = true;
        for (size_t j = 1; j < num_lists; j++) {
            if (!contains(lists[j], lengths[j], candidate)) {
                in_all = false;
                break;
            }
        }
        if (in_all) {
            result[count] = candidate;
            count++;
        }
    }

    *result_len = count;
    return result;
}

int main(void)
{
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {3, 4, 5, 6, 7};
    int list3[] = {4, 5, 8, 9, 3};

    const int *lists[] = {list1, list2, list3};
    const size_t lengths[] = {
        sizeof(list1) / sizeof(list1[0]),
        sizeof(list2) / sizeof(list2[0]),
        sizeof(list3) / sizeof(list3[0])
    };
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    size_t result_len = 0;
    int *common = find_common_elements(lists, lengths, num_lists, &result_len);

    if (common == NULL) {
        fprintf(stderr, "Failed to compute common elements\n");
        return EXIT_FAILURE;
    }

    printf("Common elements: ");
    for (size_t i = 0; i < result_len; i++) {
        printf("%d ", common[i]);
    }
    printf("\n");

    free(common);
    return EXIT_SUCCESS;
}