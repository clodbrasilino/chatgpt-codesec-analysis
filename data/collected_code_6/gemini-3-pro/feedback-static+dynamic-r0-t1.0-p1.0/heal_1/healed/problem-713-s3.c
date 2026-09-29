#include <stdio.h>
#include <stdbool.h>

typedef struct {
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

int main(void) {
    TupleElement elements0[] = { {true}, {true} };
    Tuple tuple0 = {elements0, 2};

    TupleElement elements1[] = { {true}, {false}, {true} };
    Tuple tuple1 = {elements1, 3};

    TupleElement elements2[] = { {true}, {true}, {true} };
    Tuple tuple2 = {elements2, 3};

    printf("%s\n", check_all_valid(&tuple0) ? "True" : "False");
    printf("%s\n", check_all_valid(&tuple1) ? "True" : "False");
    printf("%s\n", check_all_valid(&tuple2) ? "True" : "False");

    return 0;
}