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
 /* Possible weaknesses found:
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 2 failed: expected True, got <no output>
  */

bool check_all_valid(const Tuple* tuple) {
    if (tuple == NULL || tuple->elements == NULL) {
        return false;
    }

    for (size_t i = 0; i < tuple->size; i++) {
        if (!tuple->elements[i].is_valid) {
            return false;
        }
        (void)tuple->elements[i].value; 
    }

    return true;
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

    bool is_valid1 = check_all_valid(&tuple_valid);
    printf("%s\n", is_valid1 ? "True" : "False");

    bool is_valid2 = check_all_valid(&tuple_invalid);
    printf("%s\n", is_valid2 ? "True" : "False");

    return 0;
}