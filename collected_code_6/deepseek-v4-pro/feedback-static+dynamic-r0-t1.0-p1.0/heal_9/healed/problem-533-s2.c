#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_UNKNOWN
} DataType;

typedef struct {
    DataType type;
    void *data;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t size;
    size_t capacity;
} Tuple;

Tuple *tuple_create(void) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (!t) return NULL;
    t->elements = NULL;
    t->size = 0;
    t->capacity = 0;
    return t;
}

void tuple_destroy(Tuple *t) {
    if (!t) return;
    for (size_t i = 0; i < t->size; i++) {
        free(t->elements[i].data);
    }
    free(t->elements);
    free(t);
}

static int tuple_add_int(Tuple *t, const void *data) {
    int *new_data = (int *)malloc(sizeof(int));
    if (!new_data) return -1;
    *new_data = *(const int *)data;
    t->elements[t->size].data = new_data;
    return 0;
}

static int tuple_add_float(Tuple *t, const void *data) {
    float *new_data = (float *)malloc(sizeof(float));
    if (!new_data) return -1;
    *new_data = *(const float *)data;
    t->elements[t->size].data = new_data;
    return 0;
}

static int tuple_add_double(Tuple *t, const void *data) {
    double *new_data = (double *)malloc(sizeof(double));
    if (!new_data) return -1;
    *new_data = *(const double *)data;
    t->elements[t->size].data = new_data;
    return 0;
}

static int tuple_add_char(Tuple *t, const void *data) {
    char *new_data = (char *)malloc(sizeof(char));
    if (!new_data) return -1;
    *new_data = *(const char *)data;
    t->elements[t->size].data = new_data;
    return 0;
}

static int tuple_add_string(Tuple *t, const void *data) {
    const char *str = (const char *)data;
    size_t len = strnlen(str, 65535);
    
    if (len >= 65535) return -1;
    
    size_t alloc_size = len + 1;
    if (alloc_size > 65536) return -1;
    
    char *new_data = (char *)malloc(alloc_size);
    if (!new_data) return -1;
    
    if (len > 0) {
        memcpy(new_data, str, len);
    }
    new_data[len] = '\0';
    
    t->elements[t->size].data = new_data;
    return 0;
}

int tuple_add(Tuple *t, DataType type, const void *data) {
    if (!t || !data) return -1;
    
    if (t->size >= t->capacity) {
        size_t new_capacity = (t->capacity == 0) ? 4 : t->capacity * 2;
        if (new_capacity == 0 || new_capacity > SIZE_MAX / sizeof(TupleElement)) return -1;
        TupleElement *new_elements = (TupleElement *)realloc(t->elements, new_capacity * sizeof(TupleElement));
        if (!new_elements) return -1;
        t->elements = new_elements;
        t->capacity = new_capacity;
    }
    
    t->elements[t->size].type = type;
    
    int result = -1;
    switch (type) {
        case TYPE_INT:
            result = tuple_add_int(t, data);
            break;
        case TYPE_FLOAT:
            result = tuple_add_float(t, data);
            break;
        case TYPE_DOUBLE:
            result = tuple_add_double(t, data);
            break;
        case TYPE_CHAR:
            result = tuple_add_char(t, data);
            break;
        case TYPE_STRING:
            result = tuple_add_string(t, data);
            break;
        default:
            return -1;
    }
    
    if (result != 0) return -1;
    
    t->size++;
    return 0;
}

Tuple *tuple_remove_type(const Tuple *t, DataType type_to_remove) {
    if (!t) return NULL;
    
    Tuple *result = tuple_create();
    if (!result) return NULL;
    
    for (size_t i = 0; i < t->size; i++) {
        if (t->elements[i].type != type_to_remove) {
            if (tuple_add(result, t->elements[i].type, t->elements[i].data) != 0) {
                tuple_destroy(result);
                return NULL;
            }
        }
    }
    
    return result;
}

void tuple_print(const Tuple *t) {
    if (!t) return;
    
    printf("(");
    for (size_t i = 0; i < t->size; i++) {
        if (i > 0) printf(", ");
        
        switch (t->elements[i].type) {
            case TYPE_INT:
                printf("%d", *(int *)t->elements[i].data);
                break;
            case TYPE_FLOAT:
                printf("%f", *(float *)t->elements[i].data);
                break;
            case TYPE_DOUBLE:
                printf("%lf", *(double *)t->elements[i].data);
                break;
            case TYPE_CHAR:
                printf("'%c'", *(char *)t->elements[i].data);
                break;
            case TYPE_STRING:
                printf("\"%s\"", (char *)t->elements[i].data);
                break;
            default:
                printf("?");
                break;
        }
    }
    printf(")\n");
}

int main(void) {
    Tuple *tuple = tuple_create();
    if (!tuple) {
        fprintf(stderr, "Failed to create tuple\n");
        return 1;
    }
    
    int int_val = 42;
    float float_val = 3.14f;
    double double_val = 2.71828;
    char char_val = 'A';
    const char *str_val = "hello";
    int int_val2 = 100;
    
    tuple_add(tuple, TYPE_INT, &int_val);
    tuple_add(tuple, TYPE_FLOAT, &float_val);
    tuple_add(tuple, TYPE_DOUBLE, &double_val);
    tuple_add(tuple, TYPE_CHAR, &char_val);
    tuple_add(tuple, TYPE_STRING, str_val);
    tuple_add(tuple, TYPE_INT, &int_val2);
    
    printf("Original tuple: ");
    tuple_print(tuple);
    
    Tuple *no_ints = tuple_remove_type(tuple, TYPE_INT);
    if (no_ints) {
        printf("After removing INT: ");
        tuple_print(no_ints);
        tuple_destroy(no_ints);
    }
    
    Tuple *no_strings = tuple_remove_type(tuple, TYPE_STRING);
    if (no_strings) {
        printf("After removing STRING: ");
        tuple_print(no_strings);
        tuple_destroy(no_strings);
    }
    
    Tuple *no_doubles = tuple_remove_type(tuple, TYPE_DOUBLE);
    if (no_doubles) {
        printf("After removing DOUBLE: ");
        tuple_print(no_doubles);
        tuple_destroy(no_doubles);
    }
    
    tuple_destroy(tuple);
    
    return 0;
}