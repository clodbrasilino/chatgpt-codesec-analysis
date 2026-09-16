#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *items;
    size_t len;
} Tuple;

typedef struct {
    int value;
    size_t count;
} TupleCount;

typedef struct {
    TupleCount *entries;
    size_t len;
} CountResult;

CountResult count_tuple_elements(const Tuple *t) {
    CountResult result;
    result.len = 0;
    result.entries = NULL;

    if (t == NULL || t->items == NULL || t->len == 0) {
        return result;
    }

    result.entries = (TupleCount *)malloc(t->len * sizeof(TupleCount));
    if (result.entries == NULL) {
        fprintf(stderr, "Allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < t->len; i++) {
        int found = 0;
        for (size_t j = 0; j < result.len; j++) {
            if (result.entries[j].value == t->items[i]) {
                result.entries[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            result.entries[result.len].value = t->items[i];
            result.entries[result.len].count = 1;
            result.len++;
        }
    }

    return result;
}

int main(void) {
    int data[] = {1, 2, 3, 2, 4, 1, 5, 2};
    Tuple t;
    t.items = data;
    t.len = sizeof(data) / sizeof(data[0]);

    CountResult counts = count_tuple_elements(&t);

    for (size_t i = 0; i < counts.len; i++) {
        printf("%d: %zu\n", counts.entries[i].value, counts.entries[i].count);
    }

    free(counts.entries);
    counts.entries = NULL;

    return 0;
}