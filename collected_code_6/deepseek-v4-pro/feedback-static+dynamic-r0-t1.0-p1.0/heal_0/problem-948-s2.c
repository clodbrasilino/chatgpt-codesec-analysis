#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_CHAR,
    TYPE_DOUBLE
} TupleType;

typedef struct {
    TupleType type;
    union {
        int int_val;
        float float_val;
        double double_val;
        char char_val;
        char *str_val;
    } data;
} TupleItem;

typedef struct {
    TupleItem *items;
    size_t size;
    size_t capacity;
} Tuple;

static int tuple_init(Tuple *tuple, size_t initial_capacity) {
    if (tuple == NULL || initial_capacity == 0) {
        return -1;
    }
    
    tuple->items = (TupleItem *)malloc(initial_capacity * sizeof(TupleItem));
    if (tuple->items == NULL) {
        return -1;
    }
    
    tuple->size = 0;
    tuple->capacity = initial_capacity;
    return 0;
}

static int tuple_add_int(Tuple *tuple, int value) {
    if (tuple == NULL || tuple->size >= tuple->capacity) {
        return -1;
    }
    
    tuple->items[tuple->size].type = TYPE_INT;
    tuple->items[tuple->size].data.int_val = value;
    tuple->size++;
    return 0;
}

static int tuple_add_float(Tuple *tuple, float value) {
    if (tuple == NULL || tuple->size >= tuple->capacity) {
        return -1;
    }
    
    tuple->items[tuple->size].type = TYPE_FLOAT;
    tuple->items[tuple->size].data.float_val = value;
    tuple->size++;
    return 0;
}

static int tuple_add_string(Tuple *tuple, const char *value) {
    if (tuple == NULL || tuple->size >= tuple->capacity || value == NULL) {
        return -1;
    }
    
    tuple->items[tuple->size].data.str_val = strdup(value);
    if (tuple->items[tuple->size].data.str_val == NULL) {
        return -1;
    }
    
    tuple->items[tuple->size].type = TYPE_STRING;
    tuple->size++;
    return 0;
}

static int tuple_add_char(Tuple *tuple, char value) {
    if (tuple == NULL || tuple->size >= tuple->capacity) {
        return -1;
    }
    
    tuple->items[tuple->size].type = TYPE_CHAR;
    tuple->items[tuple->size].data.char_val = value;
    tuple->size++;
    return 0;
}

static int tuple_add_double(Tuple *tuple, double value) {
    if (tuple == NULL || tuple->size >= tuple->capacity) {
        return -1;
    }
    
    tuple->items[tuple->size].type = TYPE_DOUBLE;
    tuple->items[tuple->size].data.double_val = value;
    tuple->size++;
    return 0;
}

static int tuple_get_item(const Tuple *tuple, size_t index, TupleItem *result) {
    if (tuple == NULL || result == NULL || index >= tuple->size) {
        return -1;
    }
    
    *result = tuple->items[index];
    
    if (result->type == TYPE_STRING && result->data.str_val != NULL) {
        result->data.str_val = strdup(result->data.str_val);
        if (result->data.str_val == NULL) {
            return -1;
        }
    }
    
    return 0;
}

static void tuple_free(Tuple *tuple) {
    if (tuple == NULL || tuple->items == NULL) {
        return;
    }
    
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->items[i].type == TYPE_STRING && tuple->items[i].data.str_val != NULL) {
            free(tuple->items[i].data.str_val);
        }
    }
    
    free(tuple->items);
    tuple->items = NULL;
    tuple->size = 0;
    tuple->capacity = 0;
}

static void tuple_item_free(TupleItem *item) {
    if (item == NULL) {
        return;
    }
    
    if (item->type == TYPE_STRING && item->data.str_val != NULL) {
        free(item->data.str_val);
        item->data.str_val = NULL;
    }
}

int main(void) {
    Tuple tuple;
    
    if (tuple_init(&tuple, 5) != 0) {
        return 1;
    }
    
    if (tuple_add_int(&tuple, 42) != 0) {
        tuple_free(&tuple);
        return 1;
    }
    
    if (tuple_add_string(&tuple, "Hello") != 0) {
        tuple_free(&tuple);
        return 1;
    }
    
    if (tuple_add_double(&tuple, 3.14159) != 0) {
        tuple_free(&tuple);
        return 1;
    }
    
    if (tuple_add_char(&tuple, 'A') != 0) {
        tuple_free(&tuple);
        return 1;
    }
    
    TupleItem item;
    
    if (tuple_get_item(&tuple, 0, &item) == 0) {
        if (item.type == TYPE_INT) {
            printf("Item[0] = %d\n", item.data.int_val);
        }
        tuple_item_free(&item);
    }
    
    if (tuple_get_item(&tuple, 1, &item) == 0) {
        if (item.type == TYPE_STRING) {
            printf("Item[1] = %s\n", item.data.str_val);
        }
        tuple_item_free(&item);
    }
    
    if (tuple_get_item(&tuple, 2, &item) == 0) {
        if (item.type == TYPE_DOUBLE) {
            printf("Item[2] = %f\n", item.data.double_val);
        }
        tuple_item_free(&item);
    }
    
    if (tuple_get_item(&tuple, 3, &item) == 0) {
        if (item.type == TYPE_CHAR) {
            printf("Item[3] = %c\n", item.data.char_val);
        }
        tuple_item_free(&item);
    }
    
    if (tuple_get_item(&tuple, 10, &item) == 0) {
        printf("Item[10] retrieved successfully\n");
        tuple_item_free(&item);
    } else {
        printf("Failed to retrieve Item[10]\n");
    }
    
    tuple_free(&tuple);
    
    return 0;
}