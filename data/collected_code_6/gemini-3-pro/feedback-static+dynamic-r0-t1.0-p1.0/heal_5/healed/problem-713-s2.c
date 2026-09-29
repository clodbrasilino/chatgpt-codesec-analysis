#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    bool is_valid;
} TupleElement;

typedef struct {
    TupleElement* elements;
    size_t size;
} Tuple;

bool check_all_valid(const Tuple* tuple) {
    if (tuple == NULL) {
        return false;
    }

    for (size_t i = 0; i < tuple->size; i++) {
        if (!tuple->elements[i].is_valid) {
            return false;
        }
    }

    return true;
}

int main(void) {
    TupleElement elements_valid[] = {
        {true},
        {true},
        {true}
    };
    Tuple tuple_valid = {elements_valid, sizeof(elements_valid) / sizeof(elements_valid[0])};

    TupleElement elements_invalid[] = {
        {true},
        {false},
        {true}
    };
    Tuple tuple_invalid = {elements_invalid, sizeof(elements_invalid) / sizeof(elements_invalid[0])};

    Tuple tuple_empty = {NULL, 0};

    bool is_valid1 = check_all_valid(&tuple_valid);
    printf("%s\n", is_valid1 ? "True" : "False");

    bool is_valid2 = check_all_valid(&tuple_invalid);
    printf("%s\n", is_valid2 ? "True" : "False");
    
    bool is_valid3 = check_all_valid(&tuple_empty);
    printf("%s\n", is_valid3 ? "True" : "False");

    return 0;
}