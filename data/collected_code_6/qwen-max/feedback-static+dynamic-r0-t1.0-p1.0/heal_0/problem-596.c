#include <stdio.h>
#include <stddef.h>

size_t tuple_size(void *tuple, size_t elem_size, size_t num_elements) {
    return elem_size * num_elements;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    size_t size = tuple_size(tuple, sizeof(int), 5);
    printf("Size of the tuple: %zu bytes\n", size);
    return 0;
}