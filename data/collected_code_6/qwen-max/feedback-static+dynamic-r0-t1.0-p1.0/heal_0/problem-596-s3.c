#include <stdio.h>
#include <stdlib.h>

size_t get_tuple_size(const void *tuple, size_t elem_size, size_t count) {
    if (tuple == NULL || count == 0) {
        return 0;
    }
    return elem_size * count;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    size_t elem_size = sizeof(tuple[0]);
    size_t count = sizeof(tuple) / elem_size;
    size_t size = get_tuple_size(tuple, elem_size, count);
    printf("Size of the tuple: %zu bytes\n", size);
    return 0;
}