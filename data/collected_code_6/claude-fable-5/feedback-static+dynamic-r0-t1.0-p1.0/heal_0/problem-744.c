#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TUPLE_SIZE 5

typedef struct {
    const void *items[TUPLE_SIZE];
    size_t size;
} Tuple;

bool has_none_value(const Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return true;
    }

    if (tuple->size > TUPLE_SIZE) {
        return true;
    }

    for (i = 0; i < tuple->size; i++) {
        if (tuple->items[i] == NULL) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    int a = 10;
    double b = 3.14;
    const char *c = "hello";

    Tuple tuple_with_none;
    Tuple tuple_without_none;

    tuple_with_none.items[0] = &a;
    tuple_with_none.items[1] = NULL;
    tuple_with_none.items[2] = c;
    tuple_with_none.size = 3;

    tuple_without_none.items[0] = &a;
    tuple_without_none.items[1] = &b;
    tuple_without_none.items[2] = c;
    tuple_without_none.size = 3;

    if (has_none_value(&tuple_with_none)) {
        if (printf("Tuple 1 contains a none value.\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Tuple 1 does not contain a none value.\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (has_none_value(&tuple_without_none)) {
        if (printf("Tuple 2 contains a none value.\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Tuple 2 does not contain a none value.\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}