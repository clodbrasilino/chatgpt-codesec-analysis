#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool contains(const int *arr, size_t len, int value)
{
    size_t i;
    for (i = 0; i < len; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

int *find_common_elements(const int **lists, const size_t *sizes, size_t list_count, size_t *result_count)
{
    int *result;
    size_t capacity;
    size_t count;
    size_t i;
    size_t j;
    bool in_all;

    if (lists == NULL || sizes == NULL || result_count == NULL || list_count == 0) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    capacity = sizes[0];
    if (capacity == 0) {
        *result_count = 0;
        return NULL;
    }

    result = malloc(capacity * sizeof(int));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    count = 0;
    for (i = 0; i < sizes[0]; i++) {
        if (contains(result, count, lists[0][i])) {
            continue;
        }
        in_all = true;
        for (j = 1; j < list_count; j++) {
            if (!contains(lists[j], sizes[j], lists[0][i])) {
                in_all = false;
                break;
            }
        }
        if (in_all) {
            result[count] = lists[0][i];
            count++;
        }
    }

    if (count == 0) {
        free(result);
        *result_count = 0;
        return NULL;
    }

    *result_count = count;
    return result;
}

int main(void)
{
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {3, 4, 5, 6, 7};
    int list3[] = {4, 5, 6, 7, 8};
    const int *lists[] = {list1, list2, list3};
    /* Possible weaknesses found:
     *  Variable 'sizes' can be declared as const array [constVariable]
     */
    size_t sizes[] = {5, 5, 5};
    size_t list_count = 3;
    size_t result_count = 0;
    int *common;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    common = find_common_elements(lists, sizes, list_count, &result_count);

    if (common == NULL || result_count == 0) {
        printf("No common elements found.\n");
    } else {
        printf("Common elements: ");
        for (i = 0; i < result_count; i++) {
            printf("%d ", common[i]);
        }
        printf("\n");
        free(common);
    }

    return EXIT_SUCCESS;
}