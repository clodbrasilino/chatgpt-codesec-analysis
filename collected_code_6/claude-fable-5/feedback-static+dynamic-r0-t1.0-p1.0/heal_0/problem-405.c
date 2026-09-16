#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#define TUPLE_SIZE 5

typedef struct {
    int elements[TUPLE_SIZE];
    size_t size;
} Tuple;

bool tuple_contains(const Tuple *tuple, int value)
{
    if (tuple == NULL) {
        return false;
    }

    if (tuple->size > TUPLE_SIZE) {
        return false;
    }

    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i] == value) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    Tuple my_tuple = { {10, 20, 30, 40, 50}, TUPLE_SIZE };
    int search_values[] = {30, 99, 10, -5};
    size_t num_searches = sizeof(search_values) / sizeof(search_values[0]);

    for (size_t i = 0; i < num_searches; i++) {
        if (tuple_contains(&my_tuple, search_values[i])) {
            if (printf("%d exists in the tuple.\n", search_values[i]) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("%d does not exist in the tuple.\n", search_values[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}