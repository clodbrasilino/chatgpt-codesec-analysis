#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int value;
    int count;
} ItemCount;

int find_item(ItemCount *items, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (items[i].value == value) {
            return i;
        }
    }
    return -1;
}

int count_repeated(int *tuple, int size, ItemCount **result, int *result_size) {
    if (tuple == NULL || size <= 0 || result == NULL || result_size == NULL) {
        return 0;
    }

    ItemCount *items = (ItemCount *)malloc(size * sizeof(ItemCount));
    if (items == NULL) {
        return 0;
    }

    int count = 0;
    for (int i = 0; i < size; i++) {
        int index = find_item(items, count, tuple[i]);
        if (index == -1) {
            items[count].value = tuple[i];
            items[count].count = 1;
            count++;
        } else {
            items[index].count++;
        }
    }

    ItemCount *repeated = (ItemCount *)malloc(count * sizeof(ItemCount));
    if (repeated == NULL) {
        free(items);
        return 0;
    }

    int repeated_count = 0;
    for (int i = 0; i < count; i++) {
        if (items[i].count > 1) {
            repeated[repeated_count] = items[i];
            repeated_count++;
        }
    }

    free(items);

    if (repeated_count == 0) {
        free(repeated);
        *result = NULL;
        *result_size = 0;
        return 0;
    }

    ItemCount *final_result = (ItemCount *)realloc(repeated, repeated_count * sizeof(ItemCount));
    if (final_result == NULL) {
        free(repeated);
        return 0;
    }

    *result = final_result;
    *result_size = repeated_count;
    return 1;
}

int main(void) {
    int tuple[] = {1, 2, 3, 2, 4, 1, 5, 1, 6, 3, 3};
    int tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    ItemCount *result = NULL;
    int result_size = 0;

    if (count_repeated(tuple, tuple_size, &result, &result_size)) {
        printf("Repeated items:\n");
        for (int i = 0; i < result_size; i++) {
            printf("Value: %d, Count: %d\n", result[i].value, result[i].count);
        }
        free(result);
    } else {
        printf("No repeated items or error occurred.\n");
    }

    int empty_tuple[] = {1, 2, 3, 4, 5};
    int empty_size = sizeof(empty_tuple) / sizeof(empty_tuple[0]);

    if (count_repeated(empty_tuple, empty_size, &result, &result_size)) {
        printf("Repeated items:\n");
        for (int i = 0; i < result_size; i++) {
            printf("Value: %d, Count: %d\n", result[i].value, result[i].count);
        }
        free(result);
    } else {
        printf("No repeated items or error occurred.\n");
    }

    return 0;
}