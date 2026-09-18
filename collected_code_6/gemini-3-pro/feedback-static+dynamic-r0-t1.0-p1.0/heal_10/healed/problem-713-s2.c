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
        return true;
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
    Tuple tuple_valid = {elements_valid, 3};

    TupleElement elements_invalid[] = {
        {true},
        {false},
        {true}
    };
    Tuple tuple_invalid = {elements_invalid, 3};

    Tuple tuple_empty = {NULL, 0};

    printf("%s\n", check_all_valid(&tuple_valid) ? "True" : "False");
    printf("%s\n", check_all_valid(&tuple_invalid) ? "True" : "False");
    printf("%s\n", check_all_valid(&tuple_empty) ? "True" : "False");
    
    fflush(stdout);

    return 0;
}