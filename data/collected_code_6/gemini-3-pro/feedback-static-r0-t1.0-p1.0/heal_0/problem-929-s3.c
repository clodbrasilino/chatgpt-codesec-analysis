#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int *elements;
    size_t size;
};

struct CountResult {
    int element;
    size_t count;
};

struct CountArray {
    struct CountResult *results;
    size_t size;
};

struct CountArray count_repeated_items(const struct Tuple *t) {
    struct CountArray ca = {NULL, 0};
    
    if (!t || !t->elements || t->size == 0) {
        return ca;
    }

    ca.results = (struct CountResult *)calloc(t->size, sizeof(struct CountResult));
    if (!ca.results) {
        return ca;
    }

    for (size_t i = 0; i < t->size; ++i) {
        int current = t->elements[i];
        int found = 0;

        for (size_t j = 0; j < ca.size; ++j) {
            if (ca.results[j].element == current) {
                ca.results[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            ca.results[ca.size].element = current;
            ca.results[ca.size].count = 1;
            ca.size++;
        }
    }

    struct CountResult *temp = (struct CountResult *)realloc(ca.results, ca.size * sizeof(struct CountResult));
    if (temp) {
        ca.results = temp;
    }

    return ca;
}

int main(void) {
    int data[] = {1, 2, 2, 3, 1, 4, 2, 5};
    struct Tuple t;
    t.elements = data;
    t.size = sizeof(data) / sizeof(data[0]);

    struct CountArray counts = count_repeated_items(&t);

    if (counts.results) {
        for (size_t i = 0; i < counts.size; ++i) {
            if (counts.results[i].count > 1) {
                printf("Element: %d, Count: %zu\n", counts.results[i].element, counts.results[i].count);
            }
        }
        free(counts.results);
        counts.results = NULL;
    }

    return 0;
}