#include <stdio.h>
#include <stdlib.h>

enum DataType {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR
};

struct Element {
    enum DataType type;
    union {
        int int_val;
        float float_val;
        char char_val;
    } value;
};

struct Element* remove_elements_by_type(const struct Element* tuple, size_t tuple_size, enum DataType type_to_remove, size_t* out_size) {
    if (tuple == NULL || out_size == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < tuple_size; i++) {
        if (tuple[i].type != type_to_remove) {
            count++;
        }
    }

    if (count == 0) {
        *out_size = 0;
        return NULL;
    }

    struct Element* result = (struct Element*)malloc(count * sizeof(struct Element));
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < tuple_size; i++) {
        if (tuple[i].type != type_to_remove) {
            result[j] = tuple[i];
            j++;
        }
    }

    *out_size = count;
    return result;
}

int main(void) {
    struct Element tuple[] = {
        {TYPE_INT, .value.int_val = 1},
        {TYPE_FLOAT, .value.float_val = 2.5f},
        {TYPE_CHAR, .value.char_val = 'a'},
        {TYPE_INT, .value.int_val = 3}
    };
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);

    size_t new_size = 0;
    struct Element* filtered = remove_elements_by_type(tuple, tuple_size, TYPE_INT, &new_size);

    if (filtered != NULL) {
        for (size_t i = 0; i < new_size; i++) {
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
        filtered = NULL;
    }

    return 0;
}