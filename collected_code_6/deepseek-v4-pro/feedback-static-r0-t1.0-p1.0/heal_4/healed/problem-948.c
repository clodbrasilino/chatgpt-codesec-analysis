#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef enum {
    TUPLE_INT,
    TUPLE_FLOAT,
    TUPLE_STRING
} TupleType;

typedef struct {
    TupleType type;
    union {
        int int_val;
        float float_val;
        char *str_val;
    } value;
} TupleItem;

typedef struct {
    TupleItem *items;
    size_t size;
} Tuple;

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

Tuple *tuple_create(size_t size) {
    if (size == 0) {
        return NULL;
    }
    
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->items = (TupleItem *)calloc(size, sizeof(TupleItem));
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
    
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->items[i].type == TUPLE_STRING && tuple->items[i].value.str_val != NULL) {
            free(tuple->items[i].value.str_val);
            tuple->items[i].value.str_val = NULL;
        }
    }
    
    free(tuple->items);
    free(tuple);
}

int tuple_set_int(Tuple *tuple, size_t index, int value) {
    if (tuple == NULL || index >= tuple->size) {
        return -1;
    }
    
    if (tuple->items[index].type == TUPLE_STRING && tuple->items[index].value.str_val != NULL) {
        free(tuple->items[index].value.str_val);
        tuple->items[index].value.str_val = NULL;
    }
    
    tuple->items[index].type = TUPLE_INT;
    tuple->items[index].value.int_val = value;
    return 0;
}

int tuple_set_float(Tuple *tuple, size_t index, float value) {
    if (tuple == NULL || index >= tuple->size) {
        return -1;
    }
    
    if (tuple->items[index].type == TUPLE_STRING && tuple->items[index].value.str_val != NULL) {
        free(tuple->items[index].value.str_val);
        tuple->items[index].value.str_val = NULL;
    }
    
    tuple->items[index].type = TUPLE_FLOAT;
    tuple->items[index].value.float_val = value;
    return 0;
}

int tuple_set_string(Tuple *tuple, size_t index, const char *value) {
    if (tuple == NULL || index >= tuple->size || value == NULL) {
        return -1;
    }
    
    if (tuple->items[index].type == TUPLE_STRING && tuple->items[index].value.str_val != NULL) {
        free(tuple->items[index].value.str_val);
        tuple->items[index].value.str_val = NULL;
    }
    
    size_t max_len = 4096;
    size_t len = safe_strlen(value, max_len);
    
    if (len >= max_len) {
        return -1;
    }
    
    size_t alloc_size = len + 1;
    if (alloc_size <= len) {
        return -1;
    }
    
    char *str_copy = (char *)malloc(alloc_size);
    if (str_copy == NULL) {
        return -1;
    }
    
    memcpy(str_copy, value, len);
    str_copy[len] = '\0';
    
    tuple->items[index].type = TUPLE_STRING;
    tuple->items[index].value.str_val = str_copy;
    return 0;
}

int tuple_get_item(const Tuple *tuple, size_t index, TupleItem *result) {
    if (tuple == NULL || result == NULL || index >= tuple->size) {
        return -1;
    }
    
    result->type = tuple->items[index].type;
    
    if (result->type == TUPLE_STRING) {
        if (tuple->items[index].value.str_val == NULL) {
            result->value.str_val = NULL;
            return 0;
        }
        
        size_t max_len = 4096;
        size_t len = safe_strlen(tuple->items[index].value.str_val, max_len);
        
        if (len >= max_len) {
            return -1;
        }
        
        size_t alloc_size = len + 1;
        if (alloc_size <= len) {
            return -1;
        }
        
        char *str_copy = (char *)malloc(alloc_size);
        if (str_copy == NULL) {
            return -1;
        }
        
        memcpy(str_copy, tuple->items[index].value.str_val, len);
        str_copy[len] = '\0';
        result->value.str_val = str_copy;
    } else if (result->type == TUPLE_INT) {
        result->value.int_val = tuple->items[index].value.int_val;
    } else if (result->type == TUPLE_FLOAT) {
        result->value.float_val = tuple->items[index].value.float_val;
    }
    
    return 0;
}

void tuple_print_item(const TupleItem *item) {
    if (item == NULL) {
        return;
    }
    
    switch (item->type) {
        case TUPLE_INT:
            printf("%d", item->value.int_val);
            break;
        case TUPLE_FLOAT:
            printf("%.2f", item->value.float_val);
            break;
        case TUPLE_STRING:
            if (item->value.str_val != NULL) {
                printf("%s", item->value.str_val);
            }
            break;
        default:
            break;
    }
}

int main(void) {
    Tuple *tuple = tuple_create(3);
    if (tuple == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }
    
    if (tuple_set_int(tuple, 0, 42) != 0) {
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }
    
    if (tuple_set_float(tuple, 1, 3.14f) != 0) {
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }
    
    if (tuple_set_string(tuple, 2, "Hello, World!") != 0) {
        tuple_destroy(tuple);
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < tuple->size; i++) {
        TupleItem item;
        if (tuple_get_item(tuple, i, &item) == 0) {
            printf("Item %zu: ", i);
            tuple_print_item(&item);
            printf("\n");
            
            if (item.type == TUPLE_STRING && item.value.str_val != NULL) {
                free(item.value.str_val);
            }
        }
    }
    
    TupleItem invalid_item;
    if (tuple_get_item(tuple, 10, &invalid_item) != 0) {
        printf("Successfully handled invalid index\n");
    }
    
    tuple_destroy(tuple);
    return EXIT_SUCCESS;
}