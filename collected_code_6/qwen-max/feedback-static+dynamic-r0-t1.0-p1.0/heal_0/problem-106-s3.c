#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t len;
} Tuple;

void addListToTuple(int *list, size_t list_len, Tuple *tuple) {
    tuple->len = tuple->len + list_len;
    tuple->data = realloc(tuple->data, tuple->len * sizeof(int));
    for (size_t i = 0; i < list_len; ++i) {
        tuple->data[tuple->len - list_len + i] = list[i];
    }
}

int main() {
    int my_list[] = {7, 8, 9};
    size_t list_len = sizeof(my_list) / sizeof(my_list[0]);

    Tuple my_tuple;
    my_tuple.data = malloc(3 * sizeof(int));
    my_tuple.len = 3;
    my_tuple.data[0] = 1;
    my_tuple.data[1] = 2;
    my_tuple.data[2] = 3;

    addListToTuple(my_list, list_len, &my_tuple);

    for (size_t i = 0; i < my_tuple.len; ++i) {
        printf("%d ", my_tuple.data[i]);
    }

    free(my_tuple.data);
    return 0;
}