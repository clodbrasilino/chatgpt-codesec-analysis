#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR
} DataType;

typedef struct {
    DataType type;
    union {
        int int_val;
        float float_val;
        char char_val;
    } value;
} Element;

Element* remove_type(const Element* tuple, size_t size, DataType type_to_remove, size_t* out_size) {
    if (tuple == NULL || out_size == NULL) {
        if (out_size != NULL) {
            *out_size = 0;
        }
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (tuple[i].type != type_to_remove) {
            count++;
        }
    }

    if (count == 0) {
        *out_size = 0;
        return NULL;
    }

    Element* new_tuple = (Element*)malloc(count * sizeof(Element));
    if (new_tuple == NULL) {
        *out_size = 0;
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < size; ++i) {
        if (tuple[i].type != type_to_remove) {
            new_tuple[j++] = tuple[i];
        }
    }

    *out_size = count;
    return new_tuple;
}

int main(void) {
    Element original[] = {
        {TYPE_INT, .value.int_val = 1},
        {TYPE_FLOAT, .value.float_val = 2.5f},
        {TYPE_CHAR, .value.char_val = 'a'},
        {TYPE_INT, .value.int_val = 3},
        {TYPE_CHAR, .value.char_val = 'b'}
    };
    size_t original_size = sizeof(original) / sizeof(original[0]);
    size_t new_size = 0;

    Element* filtered = remove_type(original, original_size, TYPE_INT, &new_size);

    for (size_t i = 0; i < new_size; ++i) {
        switch (filtered[i].type) {
            case TYPE_INT:
                printf("INT: %d\n", filtered[i].value.int_val);
                break;
            case TYPE_FLOAT:
                printf("FLOAT: %f\n", filtered[i].value.float_val);
                break;
            case TYPE_CHAR:
                printf("CHAR: %c\n", filtered[i].value.char_val);
                break;
        }
    }

    free(filtered);

    return 0;
}