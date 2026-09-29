#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t size;
} Tuple;

typedef struct {
    int value;
    size_t count;
} ItemCount;

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->items);
        t->items = NULL;
        t->size = 0;
    }
}

int count_repeated_items(const Tuple *t, ItemCount **result, size_t *result_size) {
    size_t i;
    size_t j;
    size_t k;
    size_t unique_count;
    ItemCount *counts;
    size_t repeated_count;

    if (t == NULL || result == NULL || result_size == NULL) {
        return -1;
    }

    *result = NULL;
    *result_size = 0;

    if (t->size == 0 || t->items == NULL) {
        return 0;
    }

    counts = (ItemCount *)malloc(t->size * sizeof(ItemCount));
    if (counts == NULL) {
        return -1;
    }

    unique_count = 0;

    for (i = 0; i < t->size; i++) {
        int found = 0;
        for (j = 0; j < unique_count; j++) {
            if (counts[j].value == t->items[i]) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            counts[unique_count].value = t->items[i];
            counts[unique_count].count = 1;
            unique_count++;
        }
    }

    repeated_count = 0;
    for (k = 0; k < unique_count; k++) {
        if (counts[k].count > 1) {
            repeated_count++;
        }
    }

    if (repeated_count == 0) {
        free(counts);
        return 0;
    }

    *result = (ItemCount *)malloc(repeated_count * sizeof(ItemCount));
    if (*result == NULL) {
        free(counts);
        return -1;
    }

    j = 0;
    for (k = 0; k < unique_count; k++) {
        if (counts[k].count > 1) {
            (*result)[j].value = counts[k].value;
            (*result)[j].count = counts[k].count;
            j++;
        }
    }

    *result_size = repeated_count;
    free(counts);
    return 0;
}

int main(void) {
    Tuple t;
    ItemCount *repeated;
    size_t repeated_size;
    size_t i;
    int status;
    const int data[] = {1, 2, 3, 2, 4, 1, 5, 1, 2};

    repeated = NULL;
    repeated_size = 0;

    t.items = (int *)malloc(9 * sizeof(int));
    if (t.items == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    t.size = 9;

    for (i = 0; i < t.size; i++) {
        t.items[i] = data[i];
    }

    status = count_repeated_items(&t, &repeated, &repeated_size);

    if (status != 0) {
        fprintf(stderr, "Error counting repeated items\n");
        free_tuple(&t);
        return EXIT_FAILURE;
    }

    if (repeated_size == 0) {
        printf("No repeated items found.\n");
    } else {
        printf("Repeated items:\n");
        for (i = 0; i < repeated_size; i++) {
            printf("Value: %d, Count: %zu\n", repeated[i].value, repeated[i].count);
        }
    }

    free(repeated);
    free_tuple(&t);

    return EXIT_SUCCESS;
}