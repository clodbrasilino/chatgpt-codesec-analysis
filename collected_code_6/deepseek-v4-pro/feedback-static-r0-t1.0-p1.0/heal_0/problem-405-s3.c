#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TUPLE_SIZE 10
#define MAX_ELEMENT_SIZE 32

typedef struct {
    char elements[MAX_TUPLE_SIZE][MAX_ELEMENT_SIZE];
    int size;
} Tuple;

bool tuple_contains(const Tuple *tuple, const char *element) {
    if (tuple == NULL || element == NULL || tuple->size <= 0 || tuple->size > MAX_TUPLE_SIZE) {
        return false;
    }

    for (int i = 0; i < tuple->size; i++) {
        if (strncmp(tuple->elements[i], element, MAX_ELEMENT_SIZE - 1) == 0) {
            return true;
        }
    }
    return false;
}

int main(void) {
    Tuple my_tuple = {
        .elements = {"apple", "banana", "cherry", "date", "elderberry"},
        .size = 5
    };

    const char *search_element = "cherry";
    if (tuple_contains(&my_tuple, search_element)) {
        printf("Element \"%s\" exists in the tuple.\n", search_element);
    } else {
        printf("Element \"%s\" does not exist in the tuple.\n", search_element);
    }

    const char *missing_element = "fig";
    if (tuple_contains(&my_tuple, missing_element)) {
        printf("Element \"%s\" exists in the tuple.\n", missing_element);
    } else {
        printf("Element \"%s\" does not exist in the tuple.\n", missing_element);
    }

    return 0;
}