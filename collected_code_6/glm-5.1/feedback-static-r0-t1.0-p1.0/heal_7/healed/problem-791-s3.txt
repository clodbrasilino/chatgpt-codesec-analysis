#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int type;
    union {
        int int_val;
        char str_val[32];
    } data;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t count;
    size_t capacity;
} Tuple;

int tuple_init(Tuple *t, size_t capacity) {
    t->elements = (TupleElement *)malloc(capacity * sizeof(TupleElement));
    if (!t->elements) return -1;
    t->count = 0;
    t->capacity = capacity;
    return 0;
}

int tuple_append(Tuple *t, TupleElement e) {
    if (!t) return -1;
    if (t->count == t->capacity) {
        if (t->capacity == 0) t->capacity = 1;
        size_t new_capacity = t->capacity * 2;
        TupleElement *new_elements = (TupleElement *)realloc(t->elements, new_capacity * sizeof(TupleElement));
        if (!new_elements) return -1;
        t->elements = new_elements;
        t->capacity = new_capacity;
    }
    t->elements[t->count++] = e;
    return 0;
}

int tuple_append_str(Tuple *t, int type, const char *str) {
    if (!t) return -1;
    if (!str) return -1;
    if (t->count == t->capacity) {
        if (t->capacity == 0) t->capacity = 1;
        size_t new_capacity = t->capacity * 2;
        TupleElement *new_elements = (TupleElement *)realloc(t->elements, new_capacity * sizeof(TupleElement));
        if (!new_elements) return -1;
        t->elements = new_elements;
        t->capacity = new_capacity;
    }
    t->elements[t->count].type = type;
    snprintf(t->elements[t->count].data.str_val, sizeof(t->elements[t->count].data.str_val), "%s", str);
    t->count++;
    return 0;
}

void tuple_free(Tuple *t) {
    if (!t) return;
    free(t->elements);
    t->elements = NULL;
    t->count = 0;
    t->capacity = 0;
}

int remove_nested_records(Tuple *t) {
    if (!t || !t->elements) return -1;
    
    size_t write_idx = 0;
    for (size_t read_idx = 0; read_idx < t->count; ++read_idx) {
        if (t->elements[read_idx].type != 1) {
            if (write_idx != read_idx) {
                t->elements[write_idx] = t->elements[read_idx];
            }
            write_idx++;
        }
    }
    
    t->count = write_idx;
    return 0;
}

int main() {
    Tuple my_tuple;
    if (tuple_init(&my_tuple, 4) != 0) {
        return 1;
    }

    TupleElement e1 = {.type = 0, .data.int_val = 10};
    TupleElement e3 = {.type = 0, .data.int_val = 30};
    TupleElement e5 = {.type = 0, .data.int_val = 50};

    if (tuple_append(&my_tuple, e1) != 0 ||
        tuple_append_str(&my_tuple, 1, "test_string_1") != 0 ||
        tuple_append(&my_tuple, e3) != 0 ||
        tuple_append_str(&my_tuple, 1, "test_string_2") != 0 ||
        tuple_append(&my_tuple, e5) != 0) {
        tuple_free(&my_tuple);
        return 1;
    }

    for (size_t i = 0; i < my_tuple.count; ++i) {
        if (my_tuple.elements[i].type == 0) {
            printf("%d ", my_tuple.elements[i].data.int_val);
        } else if (my_tuple.elements[i].type == 1) {
            printf("%s ", my_tuple.elements[i].data.str_val);
        }
    }
    printf("\n");

    if (remove_nested_records(&my_tuple) != 0) {
        tuple_free(&my_tuple);
        return 1;
    }

    for (size_t i = 0; i < my_tuple.count; ++i) {
        if (my_tuple.elements[i].type == 0) {
            printf("%d ", my_tuple.elements[i].data.int_val);
        } else if (my_tuple.elements[i].type == 1) {
            printf("%s ", my_tuple.elements[i].data.str_val);
        }
    }
    printf("\n");

    tuple_free(&my_tuple);
    return 0;
}