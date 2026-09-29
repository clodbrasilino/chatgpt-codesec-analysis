#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

typedef struct {
    IntList *lists;
    size_t count;
} NestedList;

static bool contains(const IntList *list, int value)
{
    if (list == NULL || list->data == NULL) {
        return false;
    }
    for (size_t i = 0; i < list->size; i++) {
        if (list->data[i] == value) {
            return true;
        }
    }
    return false;
}

static IntList *find_common_elements(const NestedList *nested, const IntList *reference, size_t *result_count)
{
    if (nested == NULL || reference == NULL || result_count == NULL) {
        return NULL;
    }

    *result_count = 0;

    IntList *results = calloc(nested->count, sizeof(IntList));
    if (results == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < nested->count; i++) {
        const IntList *current = &nested->lists[i];
        results[i].data = NULL;
        results[i].size = 0;

        if (current->data == NULL || current->size == 0) {
            continue;
        }

        int *matches = malloc(current->size * sizeof(int));
        if (matches == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(results[j].data);
            }
            free(results);
            return NULL;
        }

        size_t match_count = 0;
        for (size_t j = 0; j < current->size; j++) {
            if (contains(reference, current->data[j])) {
                matches[match_count] = current->data[j];
                match_count++;
            }
        }

        if (match_count > 0) {
            int *shrunk = realloc(matches, match_count * sizeof(int));
            if (shrunk != NULL) {
                results[i].data = shrunk;
            } else {
                results[i].data = matches;
            }
            results[i].size = match_count;
        } else {
            free(matches);
        }
    }

    *result_count = nested->count;
    return results;
}

static void free_results(IntList *results, size_t count)
{
    if (results == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(results[i].data);
    }
    free(results);
}

int main(void)
{
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5, 6};
    int list3[] = {7, 8, 9, 10};

    IntList nested_arrays[3];
    nested_arrays[0].data = list1;
    nested_arrays[0].size = sizeof(list1) / sizeof(list1[0]);
    nested_arrays[1].data = list2;
    nested_arrays[1].size = sizeof(list2) / sizeof(list2[0]);
    nested_arrays[2].data = list3;
    nested_arrays[2].size = sizeof(list3) / sizeof(list3[0]);

    NestedList nested;
    nested.lists = nested_arrays;
    nested.count = 3;

    int ref_data[] = {2, 3, 5, 8, 10, 12};
    IntList reference;
    reference.data = ref_data;
    reference.size = sizeof(ref_data) / sizeof(ref_data[0]);

    size_t result_count = 0;
    IntList *results = find_common_elements(&nested, &reference, &result_count);
    if (results == NULL) {
        fprintf(stderr, "Failed to compute common elements\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_count; i++) {
        printf("Sublist %zu common elements: ", i);
        if (results[i].size == 0) {
            printf("(none)");
        } else {
            for (size_t j = 0; j < results[i].size; j++) {
                printf("%d ", results[i].data[j]);
            }
        }
        printf("\n");
    }

    free_results(results, result_count);
    return EXIT_SUCCESS;
}