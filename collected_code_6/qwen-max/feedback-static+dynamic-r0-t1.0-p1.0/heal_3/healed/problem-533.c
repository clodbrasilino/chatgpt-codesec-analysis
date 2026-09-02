#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int type; // 0 for int, 1 for float, 2 for char
    union {
        int i;
        float f;
        char c;
    } value;
} TupleElement;

typedef struct {
    TupleElement *data;
    size_t size;
    size_t capacity;
} Tuple;

Tuple* create_tuple(size_t capacity) {
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    t->data = (TupleElement*)malloc(capacity * sizeof(TupleElement));
    t->size = 0;
    t->capacity = capacity;
    return t;
}

void tuple_add(Tuple *t, int type, int i, float f, char c) {
    if (t->size == t->capacity) {
        t->capacity *= 2;
        t->data = (TupleElement*)realloc(t->data, t->capacity * sizeof(TupleElement));
    }
    t->data[t->size].type = type;
    switch (type) {
        case 0:
            t->data[t->size].value.i = i;
            break;
        case 1:
            t->data[t->size].value.f = f;
            break;
        case 2:
            t->data[t->size].value.c = c;
            break;
    }
    t->size++;
}

Tuple* remove_elements_by_type(Tuple *t, int type) {
    Tuple *result = create_tuple(t->size);
    for (size_t i = 0; i < t->size; ++i) {
        if (t->data[i].type != type) {
            switch (t->data[i].type) {
                case 0:
                    tuple_add(result, 0, t->data[i].value.i, 0, '\0');
                    break;
                case 1:
                    tuple_add(result, 1, 0, t->data[i].value.f, '\0');
                    break;
                case 2:
                    tuple_add(result, 2, 0, 0, t->data[i].value.c);
                    break;
            }
        }
    }
    return result;
}

void free_tuple(Tuple *t) {
    free(t->data);
    free(t);
}

int main() {
    Tuple *t = create_tuple(5);
    tuple_add(t, 0, 1, 0, '\0');
    tuple_add(t, 1, 0, 2.5, '\0');
    tuple_add(t, 2, 0, 0, 'a');
    tuple_add(t, 0, 3, 0, '\0');
    tuple_add(t, 1, 0, 4.5, '\0');

    Tuple *filtered = remove_elements_by_type(t, 1);

    for (size_t i = 0; i < filtered->size; ++i) {
        switch (filtered->data[i].type) {
            case 0:
                printf("%d\n", filtered->data[i].value.i);
                break;
            case 1:
                printf("%.2f\n", filtered->data[i].value.f);
                break;
            case 2:
                printf("%c\n", filtered->data[i].value.c);
                break;
        }
    }

    free_tuple(t);
    free_tuple(filtered);
    return 0;
}