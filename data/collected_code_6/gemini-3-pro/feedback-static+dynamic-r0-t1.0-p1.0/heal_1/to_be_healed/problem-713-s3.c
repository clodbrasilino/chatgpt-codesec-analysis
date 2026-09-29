#include <stdio.h>
#include <stdbool.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'TupleElement::value' is never used. [unusedStructMember]
     */
    int value;
    bool is_valid;
} TupleElement;

typedef struct {
    TupleElement* elements;
    size_t size;
} Tuple;
 /* Possible weaknesses found:
  *  test case 1 failed: expected False, got <no output>
  *  test case 2 failed: expected True, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

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

int main(void) {
    TupleElement valid_elements[] = {
        {10, true},
        {20, true},
        {30, true}
    };
    Tuple tuple1 = {valid_elements, 3};

    TupleElement mixed_elements[] = {
        {10, true},
        {20, false},
        {30, true}
    };
    Tuple tuple2 = {mixed_elements, 3};

    bool is_tuple1_valid = check_all_valid(&tuple1);
    bool is_tuple2_valid = check_all_valid(&tuple2);

    if (is_tuple1_valid) {
        printf("Tuple 1 is valid.\n");
    } else {
        printf("Tuple 1 is invalid.\n");
    }

    if (is_tuple2_valid) {
        printf("Tuple 2 is valid.\n");
    } else {
        printf("Tuple 2 is invalid.\n");
    }

    return 0;
}