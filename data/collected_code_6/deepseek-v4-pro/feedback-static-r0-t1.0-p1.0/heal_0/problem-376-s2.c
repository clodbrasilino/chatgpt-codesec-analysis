#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Tuple;

Tuple *tuple_create(size_t capacity) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (!t) return NULL;
    t->data = (int *)malloc(capacity * sizeof(int));
    if (!t->data) {
        free(t);
        return NULL;
    }
    t->size = 0;
    t->capacity = capacity;
    return t;
}

void tuple_destroy(Tuple *t) {
    if (!t) return;
    free(t->data);
    free(t);
}

int tuple_push(Tuple *t, int value) {
    if (!t) return 0;
    if (t->size >= t->capacity) {
        size_t new_cap = t->capacity * 2;
        if (new_cap == 0) new_cap = 1;
        int *new_data = (int *)realloc(t->data, new_cap * sizeof(int));
        if (!new_data) return 0;
        t->data = new_data;
        t->capacity = new_cap;
    }
    t->data[t->size++] = value;
    return 1;
}

void tuple_replace_duplicates(Tuple *t, int replacement) {
    if (!t || !t->data || t->size == 0) return;

    int *counts = (int *)calloc(t->size, sizeof(int));
    if (!counts) return;

    for (size_t i = 0; i < t->size; i++) {
        counts[i] = 0;
        for (size_t j = 0; j < t->size; j++) {
            if (t->data[j] == t->data[i]) {
                counts[i]++;
            }
        }
    }

    for (size_t i = 0; i < t->size; i++) {
        if (counts[i] > 1) {
            t->data[i] = replacement;
        }
    }

    free(counts);
}

void tuple_print(const Tuple *t) {
    if (!t) {
        printf("NULL\n");
        return;
    }
    for (size_t i = 0; i < t->size; i++) {
        if (i > 0) printf(" ");
        printf("%d", t->data[i]);
    }
    printf("\n");
}

int main(void) {
    Tuple *t = tuple_create(8);
    if (!t) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    int values[] = {1, 2, 3, 2, 4, 1, 5, 1, 6, 3};
    size_t n = sizeof(values) / sizeof(values[0]);

    for (size_t i = 0; i < n; i++) {
        if (!tuple_push(t, values[i])) {
            fprintf(stderr, "Failed to push value\n");
            tuple_destroy(t);
            return EXIT_FAILURE;
        }
    }

    printf("Original: ");
    tuple_print(t);

    tuple_replace_duplicates(t, -1);

    printf("Modified: ");
    tuple_print(t);

    tuple_destroy(t);
    return EXIT_SUCCESS;
}