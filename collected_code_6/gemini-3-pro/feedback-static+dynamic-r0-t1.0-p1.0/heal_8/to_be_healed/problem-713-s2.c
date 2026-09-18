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
 /* Possible weaknesses found:
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 2 failed: expected True, got <no output>
  */

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
    Tuple tuple_valid = {elements_valid, 3};

    TupleElement elements_invalid[] = {
        {true},
        {false},
        {true}
    };
    Tuple tuple_invalid = {elements_invalid, 3};

    Tuple tuple_empty = {NULL, 0};

    bool is_valid1 = check_all_valid(&tuple_valid);
    printf("%s\n", is_valid1 ? "True" : "False");

    bool is_valid2 = check_all_valid(&tuple_invalid);
    printf("%s\n", is_valid2 ? "True" : "False");
    
    bool is_valid3 = check_all_valid(&tuple_empty);
    printf("%s\n", is_valid3 ? "True" : "False");

    return 0;
}