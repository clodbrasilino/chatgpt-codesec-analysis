#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Set;

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple *data;
    size_t size;
} Tuples;

void set_init(Set *set, size_t initial_capacity) {
    set->size = 0;
    set->capacity = initial_capacity;
    set->data = (int *) malloc(initial_capacity * sizeof(int));
}

void set_add(Set *set, int value) {
    if (set->size == set->capacity) {
        set->capacity *= 2;
        set->data = (int *) realloc(set->data, set->capacity * sizeof(int));
    }
    set->data[set->size++] = value;
}

Tuples convert_to_tuples(const Set *set) {
    Tuples result;
    result.size = 0;
    result.data = NULL;
    if (set->size > 1) {
        result.size = (set->size - 1) * set->size / 2;
        result.data = (Tuple *) malloc(result.size * sizeof(Tuple));
        int idx = 0;
        for (size_t i = 0; i < set->size; ++i) {
            for (size_t j = i + 1; j < set->size; ++j) {
                result.data[idx].a = set->data[i];
                result.data[idx].b = set->data[j];
                ++idx;
            }
        }
    } else {
        result.data = (Tuple *) malloc(0);
    }
    return result;
}

void print_tuples(const Tuples *tuples) {
    for (size_t i = 0; i < tuples->size; ++i) {
        printf("(%d, %d)\n", tuples->data[i].a, tuples->data[i].b);
    }
}

int main() {
    Set s;
    set_init(&s, 5);
    set_add(&s, 1);
    set_add(&s, 2);
    set_add(&s, 3);
    set_add(&s, 4);

    Tuples t = convert_to_tuples(&s);
    print_tuples(&t);

    free(s.data);
    free(t.data);
    return 0;
}