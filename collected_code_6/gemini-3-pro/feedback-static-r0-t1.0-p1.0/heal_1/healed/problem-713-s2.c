#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int value;
    bool is_valid;
} TupleElement;

typedef struct {
    TupleElement* elements;
    size_t size;
} Tuple;

bool check_all_valid(const Tuple* tuple) {
    if (tuple == NULL || tuple->elements == NULL) {
        return false;
    }

    for (size_t i = 0; i < tuple->size; i++) {
        if (!tuple->elements[i].is_valid) {
            return false;
        }
    }

    return true;
}

void print_tuple(const Tuple* tuple) {
    if (tuple == NULL || tuple->elements == NULL) {
        return;
    }
    
    printf("Values: ");
    for (size_t i = 0; i < tuple->size; i++) {
        printf("%d ", tuple->elements[i].value);
    }
    printf("\n");
}

int main(void) {
    TupleElement elements_valid[] = {
        {1, true},
        {2, true},
        {3, true}
    };
    Tuple tuple_valid = {elements_valid, sizeof(elements_valid) / sizeof(elements_valid[0])};

    TupleElement elements_invalid[] = {
        {1, true},
        {2, false},
        {3, true}
    };
    Tuple tuple_invalid = {elements_invalid, sizeof(elements_invalid) / sizeof(elements_invalid[0])};

    print_tuple(&tuple_valid);
    bool is_valid = check_all_valid(&tuple_valid);
    printf("Tuple 1 valid: %s\n\n", is_valid ? "true" : "false");

    print_tuple(&tuple_invalid);
    is_valid = check_all_valid(&tuple_invalid);
    printf("Tuple 2 valid: %s\n", is_valid ? "true" : "false");

    return 0;
}