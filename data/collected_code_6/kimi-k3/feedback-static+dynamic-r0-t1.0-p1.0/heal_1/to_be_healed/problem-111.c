#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

typedef struct {
    IntList *lists;
    size_t count;
} NestedList;

static int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

static int contains(const IntList *list, int value) {
    size_t i;
    for (i = 0; i < list->size; i++) {
        if (list->data[i] == value) {
            return 1;
        }
    }
    return 0;
}

static int in_result(const int *result, size_t result_size, int value) {
    size_t i;
    for (i = 0; i < result_size; i++) {
        if (result[i] == value) {
            return 1;
        }
    }
    return 0;
}

int *find_common_elements(const NestedList *nested, size_t *common_size) {
    int *result;
    int *temp;
    size_t result_size = 0;
    size_t capacity;
    size_t i, j;
    /* Possible weaknesses found:
     *  The scope of the variable 'is_common' can be reduced. [variableScope]
     */
    int is_common;

    if (nested == NULL || common_size == NULL || nested->count == 0) {
        if (common_size != NULL) {
            *common_size = 0;
        }
        return NULL;
    }

    capacity = nested->lists[0].size;
    if (capacity == 0) {
        *common_size = 0;
        return NULL;
    }

    result = malloc(capacity * sizeof(int));
    if (result == NULL) {
        *common_size = 0;
        return NULL;
    }

    for (i = 0; i < nested->lists[0].size; i++) {
        int candidate = nested->lists[0].data[i];
        is_common = 1;

        for (j = 1; j < nested->count; j++) {
            if (!contains(&nested->lists[j], candidate)) {
                is_common = 0;
                break;
            }
        }

        if (is_common && !in_result(result, result_size, candidate)) {
            result[result_size++] = candidate;
        }
    }

    if (result_size == 0) {
        free(result);
        *common_size = 0;
        return NULL;
    }

    temp = realloc(result, result_size * sizeof(int));
    if (temp != NULL) {
        result = temp;
    }

    qsort(result, result_size, sizeof(int), compare_ints);
    *common_size = result_size;
    return result;
}

static void free_nested_list(NestedList *nested) {
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;
    if (nested == NULL) {
        return;
    }
    if (nested->lists != NULL) {
        for (i = 0; i < nested->count; i++) {
            free(nested->lists[i].data);
        }
        free(nested->lists);
    }
    nested->lists = NULL;
    nested->count = 0;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'arr1' can be declared as const array [constVariable]
     */
    int arr1[] = {1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  Variable 'arr2' can be declared as const array [constVariable]
     */
    int arr2[] = {3, 4, 5, 6, 7};
    /* Possible weaknesses found:
     *  Variable 'arr3' can be declared as const array [constVariable]
     */
    int arr3[] = {2, 3, 4, 8, 9};
    /* Possible weaknesses found:
     *  Variable 'arr4' can be declared as const array [constVariable]
     */
    int arr4[] = {3, 4, 10, 11, 12};
    NestedList nested;
    int *common;
    size_t common_size;
    size_t i;
    int status = EXIT_SUCCESS;

    nested.count = 4;
    nested.lists = malloc(nested.count * sizeof(IntList));
    if (nested.lists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    nested.lists[0].data = malloc(5 * sizeof(int));
    nested.lists[1].data = malloc(5 * sizeof(int));
    nested.lists[2].data = malloc(5 * sizeof(int));
    nested.lists[3].data = malloc(5 * sizeof(int));

    if (nested.lists[0].data == NULL || nested.lists[1].data == NULL ||
        nested.lists[2].data == NULL || nested.lists[3].data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_nested_list(&nested);
        return EXIT_FAILURE;
    }

    for (i = 0; i < 5; i++) {
        nested.lists[0].data[i] = arr1[i];
        nested.lists[1].data[i] = arr2[i];
        nested.lists[2].data[i] = arr3[i];
        nested.lists[3].data[i] = arr4[i];
    }
    nested.lists[0].size = 5;
    nested.lists[1].size = 5;
    nested.lists[2].size = 5;
    nested.lists[3].size = 5;

    common = find_common_elements(&nested, &common_size);

    if (common != NULL) {
        printf("Common elements: ");
        for (i = 0; i < common_size; i++) {
            printf("%d ", common[i]);
        }
        printf("\n");
        free(common);
    } else {
        printf("No common elements found\n");
    }

    free_nested_list(&nested);
    return status;
}