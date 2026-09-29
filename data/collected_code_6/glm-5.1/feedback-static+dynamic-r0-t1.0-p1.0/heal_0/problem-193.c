#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    int *elements;
    size_t size;
    size_t capacity;
} Tuple;

Tuple tuple_create(size_t capacity) {
    Tuple t;
    t.capacity = capacity < 1 ? 1 : capacity;
    t.size = 0;
    t.elements = (int *)malloc(t.capacity * sizeof(int));
    if (t.elements == NULL) {
        t.capacity = 0;
        t.size = 0;
    }
    return t;
}

void tuple_destroy(Tuple *t) {
    if (t != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->size = 0;
        t->capacity = 0;
    }
}

int tuple_append(Tuple *t, int value) {
    if (t == NULL || t->elements == NULL) {
        return -1;
    }
    if (t->size == t->capacity) {
        size_t new_capacity = t->capacity * 2;
        int *new_elements = (int *)realloc(t->elements, new_capacity * sizeof(int));
        if (new_elements == NULL) {
            return -1;
        }
        t->elements = new_elements;
        t->capacity = new_capacity;
    }
    t->elements[t->size] = value;
    t->size++;
    return 0;
}

Tuple remove_duplicates(const Tuple *t) {
    Tuple result = tuple_create(t == NULL ? 1 : t->size);
    if (result.elements == NULL) {
        return result;
    }
    if (t == NULL || t->elements == NULL) {
        return result;
    }
    for (size_t i = 0; i < t->size; ++i) {
        int is_duplicate = 0;
        for (size_t j = 0; j < result.size; ++j) {
            if (t->elements[i] == result.elements[j]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            if (tuple_append(&result, t->elements[i]) != 0) {
                tuple_destroy(&result);
                return tuple_create(0);
            }
        }
    }
    return result;
}

void tuple_print(const Tuple *t) {
    if (t == NULL || t->elements == NULL) {
        printf("()");
        return;
    }
    printf("(");
    for (size_t i = 0; i < t->size; ++i) {
        printf("%d", t->elements[i]);
        if (i < t->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    Tuple t1 = tuple_create(8);
    if (t1.elements == NULL) {
        return 1;
    }
    tuple_append(&t1, 1);
    tuple_append(&t1, 2);
    tuple_append(&t1, 2);
    tuple_append(&t1, 3);
    tuple_append(&t1, 4);
    tuple_append(&t1, 4);
    tuple_append(&t1, 5);

    printf("Original: ");
    tuple_print(&t1);

    Tuple t2 = remove_duplicates(&t1);
    
    printf("After removal: ");
    tuple_print(&t2);

    tuple_destroy(&t1);
    tuple_destroy(&t2);

    Tuple t3 = remove_duplicates(NULL);
    tuple_print(&t3);
    tuple_destroy(&t3);

    return 0;
}