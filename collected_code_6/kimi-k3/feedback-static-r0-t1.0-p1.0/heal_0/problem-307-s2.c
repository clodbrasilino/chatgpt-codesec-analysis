#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

char *tuple_get_colon(const Tuple *tuple, size_t index) {
    if (tuple == NULL || tuple->elements == NULL || index >= tuple->count) {
        return NULL;
    }
    return tuple->elements[index];
}

int main(void) {
    char *data[] = {"apple", "banana", "cherry", "date"};
    Tuple tuple = {data, 4};
    size_t index = 2;
    char *result = tuple_get_colon(&tuple, index);
    if (result != NULL) {
        printf("Element at index %zu: %s\n", index, result);
    } else {
        printf("Invalid index or tuple\n");
    }
    return 0;
}