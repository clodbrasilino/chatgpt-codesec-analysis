#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    TUPLE_INT,
    TUPLE_DOUBLE,
    TUPLE_STRING
} TupleType;

typedef struct {
    TupleType type;
    union {
        int int_val;
        double double_val;
        char *string_val;
    } data;
} TupleItem;

typedef struct {
    TupleItem *items;
    size_t size;
} Tuple;

Tuple *tuple_create(size_t size) {
    if (size == 0) {
        return NULL;
    }
    
    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->items = calloc(size, sizeof(TupleItem));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }
    
    tuple->size = size;
    return tuple;
}

void tuple_destroy(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    
    if (tuple->items != NULL) {
        for (size_t i = 0; i < tuple->size; i++) {
            if (tuple->items[i].type == TUPLE_STRING && 
                tuple->items[i].data.string_val != NULL) {
                free(tuple->items[i].data.string_val);
            }
        }
        free(tuple->items);
    }
    free(tuple);
}

bool tuple_set_int(Tuple *tuple, size_t index, int value) {
    if (tuple == NULL || index >= tuple->size) {
        return false;
    }
    
    if (tuple->items[index].type == TUPLE_STRING && 
        tuple->items[index].data.string_val != NULL) {
        free(tuple->items[index].data.string_val);
    }
    
    tuple->items[index].type = TUPLE_INT;
    tuple->items[index].data.int_val = value;
    return true;
}

bool tuple_set_double(Tuple *tuple, size_t index, double value) {
    if (tuple == NULL || index >= tuple->size) {
        return false;
    }
    
    if (tuple->items[index].type == TUPLE_STRING && 
        tuple->items[index].data.string_val != NULL) {
        free(tuple->items[index].data.string_val);
    }
    
    tuple->items[index].type = TUPLE_DOUBLE;
    tuple->items[index].data.double_val = value;
    return true;
}

bool tuple_set_string(Tuple *tuple, size_t index, const char *value) {
    if (tuple == NULL || index >= tuple->size || value == NULL) {
        return false;
    }
    
    char *new_string = malloc(strlen(value) + 1);
    if (new_string == NULL) {
        return false;
    }
    strcpy(new_string, value);
    
    if (tuple->items[index].type == TUPLE_STRING && 
        tuple->items[index].data.string_val != NULL) {
        free(tuple->items[index].data.string_val);
    }
    
    tuple->items[index].type = TUPLE_STRING;
    tuple->items[index].data.string_val = new_string;
    return true;
}

bool tuple_get_item(const Tuple *tuple, size_t index, TupleItem *out_item) {
    if (tuple == NULL || index >= tuple->size || out_item == NULL) {
        return false;
    }
    
    *out_item = tuple->items[index];
    return true;
}

int main(void) {
    Tuple *tuple = tuple_create(3);
    if (tuple == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }
    
    if (!tuple_set_int(tuple, 0, 42)) {
        fprintf(stderr, "Failed to set int\n");
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }
    
    if (!tuple_set_double(tuple, 1, 3.14159)) {
        fprintf(stderr, "Failed to set double\n");
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }
    
    if (!tuple_set_string(tuple, 2, "Hello, World!")) {
        fprintf(stderr, "Failed to set string\n");
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }
    
    TupleItem item;
    
    if (tuple_get_item(tuple, 0, &item)) {
        if (item.type == TUPLE_INT) {
            printf("Item 0 (int): %d\n", item.data.int_val);
        }
    }
    
    if (tuple_get_item(tuple, 1, &item)) {
        if (item.type == TUPLE_DOUBLE) {
            printf("Item 1 (double): %f\n", item.data.double_val);
        }
    }
    
    if (tuple_get_item(tuple, 2, &item)) {
        if (item.type == TUPLE_STRING) {
            printf("Item 2 (string): %s\n", item.data.string_val);
        }
    }
    
    if (!tuple_get_item(tuple, 5, &item)) {
        printf("Index 5 is out of bounds\n");
    }
    
    tuple_destroy(tuple);
    return EXIT_SUCCESS;
}