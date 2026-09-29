#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int is_present;
} tuple;

typedef struct {
    int *elements;
    int size;
    int capacity;
} set;

set* create_set(int initial_capacity) {
    set *s = (set*)malloc(sizeof(set));
    if (!s) return NULL;
    s->elements = (int*)calloc(initial_capacity, sizeof(int));
    if (!s->elements) {
        free(s);
        return NULL;
    }
    s->size = 0;
    s->capacity = initial_capacity;
    return s;
}

void destroy_set(set *s) {
    if (s) {
        free(s->elements);
        free(s);
    }
}

int add_element(set *s, int element) {
    for (int i = 0; i < s->size; ++i) {
        if (s->elements[i] == element) return 0;
    }
    if (s->size >= s->capacity) {
        s->capacity *= 2;
        s->elements = (int*)realloc(s->elements, s->capacity * sizeof(int));
        if (!s->elements) return -1;
    }
    s->elements[s->size++] = element;
    return 1;
}

set* convert_tuples_to_set(tuple *tuples, int count) {
    set *s = create_set(count);
    if (!s) return NULL;
    for (int i = 0; i < count; ++i) {
        if (tuples[i].is_present && add_element(s, tuples[i].value) == -1) {
            destroy_set(s);
            return NULL;
        }
    }
    return s;
}

int main() {
    tuple tuples[] = {{1, 1}, {2, 1}, {3, 0}, {4, 1}, {5, 1}};
    int count = sizeof(tuples) / sizeof(tuples[0]);
    set *s = convert_tuples_to_set(tuples, count);
    if (s) {
        for (int i = 0; i < s->size; ++i) {
            printf("%d ", s->elements[i]);
        }
        destroy_set(s);
    }
    return 0;
}