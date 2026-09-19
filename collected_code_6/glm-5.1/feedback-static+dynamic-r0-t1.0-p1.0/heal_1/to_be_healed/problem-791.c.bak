#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { TYPE_INT, TYPE_FLOAT, TYPE_STRING, TYPE_TUPLE } DataType;

typedef struct Record {
    DataType type;
    union {
        int int_val;
        float float_val;
        char *string_val;
        struct Record *tuple_val;
    };
    size_t tuple_size;
    int ref_count;
} Record;

Record *create_int(int val) {
    Record *r = (Record *)malloc(sizeof(Record));
    if (!r) exit(EXIT_FAILURE);
    r->type = TYPE_INT;
    r->int_val = val;
    r->tuple_size = 0;
    r->ref_count = 1;
    return r;
}

Record *create_float(float val) {
    Record *r = (Record *)malloc(sizeof(Record));
    if (!r) exit(EXIT_FAILURE);
    r->type = TYPE_FLOAT;
    r->float_val = val;
    r->tuple_size = 0;
    r->ref_count = 1;
    return r;
}

Record *create_string(const char *val) {
    Record *r = (Record *)malloc(sizeof(Record));
    if (!r) exit(EXIT_FAILURE);
    r->type = TYPE_STRING;
    r->string_val = strdup(val);
    if (!r->string_val) exit(EXIT_FAILURE);
    r->tuple_size = 0;
    r->ref_count = 1;
    return r;
}

/* Possible weaknesses found:
 *  expected 'Record **' but argument is of type 'Record *'
 */
Record *create_tuple(Record **elements, size_t size) {
    Record *r = (Record *)malloc(sizeof(Record));
    if (!r) exit(EXIT_FAILURE);
    r->type = TYPE_TUPLE;
    r->tuple_val = (Record *)malloc(sizeof(Record) * size);
    if (!r->tuple_val) exit(EXIT_FAILURE);
    memcpy(r->tuple_val, elements, sizeof(Record) * size);
    for (size_t i = 0; i < size; i++) {
        r->tuple_val[i].ref_count++;
    }
    r->tuple_size = size;
    r->ref_count = 1;
    return r;
}

void free_record(Record *r) {
    if (!r || --r->ref_count > 0) return;
    if (r->type == TYPE_STRING && r->string_val) {
        free(r->string_val);
    } else if (r->type == TYPE_TUPLE && r->tuple_val) {
        for (size_t i = 0; i < r->tuple_size; i++) {
            free_record(&r->tuple_val[i]);
        }
        free(r->tuple_val);
    }
    if (r->ref_count == 0) {
        free(r);
    }
}

Record *remove_nested_record(Record *tuple, size_t index) {
    if (!tuple || tuple->type != TYPE_TUPLE) {
        return NULL;
    }
    if (index >= tuple->tuple_size) {
        return NULL;
    }
    if (tuple->tuple_val[index].type != TYPE_TUPLE) {
        return NULL;
    }

    Record *nested = &tuple->tuple_val[index];
    size_t nested_size = nested->tuple_size;
    size_t new_size = tuple->tuple_size - 1 + nested_size;
    
    Record *new_elements = (Record *)malloc(sizeof(Record) * new_size);
    if (!new_elements) return NULL;

    size_t new_idx = 0;
    for (size_t i = 0; i < tuple->tuple_size; i++) {
        if (i == index) {
            for (size_t j = 0; j < nested_size; j++) {
                new_elements[new_idx++] = nested->tuple_val[j];
                new_elements[new_idx].ref_count = 1;
            }
        } else {
            new_elements[new_idx++] = tuple->tuple_val[i];
        }
    }

    /* Possible weaknesses found:
     *  passing argument 1 of 'create_tuple' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    Record *new_tuple = create_tuple(new_elements, new_size);
    free(new_elements);
    
    return new_tuple;
}

void print_record(Record *r) {
    if (!r) return;
    switch (r->type) {
        case TYPE_INT: printf("%d", r->int_val); break;
        case TYPE_FLOAT: printf("%f", r->float_val); break;
        case TYPE_STRING: printf("\"%s\"", r->string_val); break;
        case TYPE_TUPLE:
            printf("(");
            for (size_t i = 0; i < r->tuple_size; i++) {
                print_record(&r->tuple_val[i]);
                if (i < r->tuple_size - 1) printf(", ");
            }
            printf(")");
            break;
    }
}

int main() {
    Record *inner_elements[] = {
        create_int(2),
        create_int(3)
    };
    Record *inner_tuple = create_tuple(inner_elements, 2);
    
    Record *outer_elements[] = {
        create_int(1),
        inner_tuple,
        create_int(4)
    };
    Record *outer_tuple = create_tuple(outer_elements, 3);

    printf("Original: ");
    print_record(outer_tuple);
    printf("\n");

    Record *flattened = remove_nested_record(outer_tuple, 1);
    if (flattened) {
        printf("After removal: ");
        print_record(flattened);
        printf("\n");
        free_record(flattened);
    }

    free_record(outer_tuple);
    for (int i = 0; i < 2; i++) free_record(inner_elements[i]);
    
    return 0;
}