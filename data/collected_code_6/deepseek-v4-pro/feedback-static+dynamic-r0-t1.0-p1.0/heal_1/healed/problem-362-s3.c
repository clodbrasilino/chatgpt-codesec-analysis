#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} List;

int find_max_occurrence_item(List *list, int *max_item) {
    if (list == NULL || list->data == NULL || list->size <= 0 || max_item == NULL) {
        return -1;
    }

    int *unique_items = (int *)malloc(list->size * sizeof(int));
    int *counts = (int *)calloc(list->size, sizeof(int));
    if (unique_items == NULL || counts == NULL) {
        free(unique_items);
        free(counts);
        return -1;
    }

    int unique_count = 0;
    int i, j;

    for (i = 0; i < list->size; i++) {
        int found = 0;
        for (j = 0; j < unique_count; j++) {
            if (unique_items[j] == list->data[i]) {
                counts[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            unique_items[unique_count] = list->data[i];
            counts[unique_count] = 1;
            unique_count++;
        }
    }

    int max_count = 0;
    int max_index = 0;
    for (i = 0; i < unique_count; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            max_index = i;
        }
    }

    *max_item = unique_items[max_index];

    free(unique_items);
    free(counts);
    return max_count;
}

int main(void) {
    int arr[] = {3, 5, 2, 3, 3, 2, 4, 5, 5, 5, 2};
    List list;
    list.data = arr;
    list.size = sizeof(arr) / sizeof(arr[0]);

    int max_item;
    int result = find_max_occurrence_item(&list, &max_item);

    if (result == -1) {
        printf("Error occurred\n");
        return 1;
    }

    printf("Item with maximum occurrences: %d\n", max_item);
    printf("Number of occurrences: %d\n", result);

    return 0;
}