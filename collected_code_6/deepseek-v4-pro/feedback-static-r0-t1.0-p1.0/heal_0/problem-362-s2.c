#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *items;
    int count;
    int capacity;
} IntList;

typedef struct {
    int value;
    int count;
} MaxOccurrence;

void init_list(IntList *list) {
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

void free_list(IntList *list) {
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

int add_item(IntList *list, int item) {
    if (list->count == list->capacity) {
        int new_capacity = list->capacity == 0 ? 8 : list->capacity * 2;
        int *new_items = (int *)realloc(list->items, new_capacity * sizeof(int));
        if (new_items == NULL) {
            return 0;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->count++] = item;
    return 1;
}

MaxOccurrence find_max_occurrence(const int *arr, int size) {
    MaxOccurrence result;
    result.value = 0;
    result.count = 0;

    if (arr == NULL || size <= 0) {
        return result;
    }

    int *values = (int *)malloc(size * sizeof(int));
    int *counts = (int *)malloc(size * sizeof(int));
    if (values == NULL || counts == NULL) {
        free(values);
        free(counts);
        return result;
    }

    int unique_count = 0;
    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (values[j] == arr[i]) {
                counts[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            values[unique_count] = arr[i];
            counts[unique_count] = 1;
            unique_count++;
        }
    }

    int max_count = counts[0];
    int max_value = values[0];
    for (int i = 1; i < unique_count; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            max_value = values[i];
        }
    }

    free(values);
    free(counts);

    result.value = max_value;
    result.count = max_count;
    return result;
}

int main(void) {
    IntList list;
    init_list(&list);

    int input;
    printf("Enter integers (non-numeric to stop): ");
    while (scanf("%d", &input) == 1) {
        if (!add_item(&list, input)) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(&list);
            return EXIT_FAILURE;
        }
    }

    if (list.count > 0) {
        MaxOccurrence result = find_max_occurrence(list.items, list.count);
        printf("Item with maximum occurrences: %d (occurs %d times)\n", result.value, result.count);
    } else {
        printf("No valid integers entered.\n");
    }

    free_list(&list);
    return EXIT_SUCCESS;
}