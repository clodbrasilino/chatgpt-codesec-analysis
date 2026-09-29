#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum data_type { INT_TYPE, FLOAT_TYPE, CHAR_TYPE };

union data_value {
    int int_val;
    float float_val;
    char char_val;
};

struct tuple_element {
    enum data_type type;
    union data_value value;
};

struct tuple {
    struct tuple_element *elements;
    size_t size;
    size_t capacity;
};

struct tuple create_tuple(size_t capacity) {
    struct tuple t;
    t.capacity = capacity > 0 ? capacity : 1;
    t.size = 0;
    t.elements = (struct tuple_element *)malloc(t.capacity * sizeof(struct tuple_element));
    if (t.elements == NULL) {
        t.capacity = 0;
        t.size = 0;
    }
    return t;
}

int append_tuple(struct tuple *t, enum data_type type, union data_value val) {
    if (t == NULL || t->elements == NULL) {
        return -1;
    }
    if (t->size == t->capacity) {
        size_t new_capacity = t->capacity * 2;
        struct tuple_element *new_elements = (struct tuple_element *)realloc(t->elements, new_capacity * sizeof(struct tuple_element));
        if (new_elements == NULL) {
            return -1;
        }
        t->elements = new_elements;
        t->capacity = new_capacity;
    }
    t->elements[t->size].type = type;
    t->elements[t->size].value = val;
    t->size++;
    return 0;
}

struct tuple remove_by_type(struct tuple *t, enum data_type type_to_remove) {
    struct tuple result = create_tuple(t->size);
    if (result.elements == NULL) {
        return result;
    }
    for (size_t i = 0; i < t->size; i++) {
        if (t->elements[i].type != type_to_remove) {
            if (append_tuple(&result, t->elements[i].type, t->elements[i].value) != 0) {
                free(result.elements);
                result.elements = NULL;
                result.size = 0;
                result.capacity = 0;
                return result;
            }
        }
    }
    return result;
}

void print_tuple(struct tuple *t) {
    printf("(");
    for (size_t i = 0; i < t->size; i++) {
        switch (t->elements[i].type) {
            case INT_TYPE:
                printf("%d", t->elements[i].value.int_val);
                break;
            case FLOAT_TYPE:
                printf("%f", t->elements[i].value.float_val);
                break;
            case CHAR_TYPE:
                printf("'%c'", t->elements[i].value.char_val);
                break;
        }
        if (i < t->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

void free_tuple(struct tuple *t) {
    if (t != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->size = 0;
        t->capacity = 0;
    }
}

int main(void) {
    struct tuple t = create_tuple(4);
    union data_value v1, v2, v3, v4, v5;
    
    v1.int_val = 10;
    v2.float_val = 3.14f;
    v3.char_val = 'A';
    v4.int_val = 20;
    v5.float_val = 2.71f;

    append_tuple(&t, INT_TYPE, v1);
    append_tuple(&t, FLOAT_TYPE, v2);
    append_tuple(&t, CHAR_TYPE, v3);
    append_tuple(&t, INT_TYPE, v4);
    append_tuple(&t, FLOAT_TYPE, v5);

    printf("Original: ");
    print_tuple(&t);

    struct tuple filtered = remove_by_type(&t, INT_TYPE);

    printf("After removing INT_TYPE: ");
    print_tuple(&filtered);

    free_tuple(&t);
    free_tuple(&filtered);

    return 0;
}