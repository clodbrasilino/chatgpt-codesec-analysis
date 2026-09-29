#include <stdio.h>
#include <stddef.h>

size_t remove_negatives(int *list, size_t size) {
    if (list == NULL) {
        return 0;
    }

    int *write_ptr = list;
    int *end = list + size;

    for (int *read_ptr = list; read_ptr < end; ++read_ptr) {
        if (*read_ptr >= 0) {
            if (write_ptr < end) {
                *write_ptr++ = *read_ptr;
            }
        }
    }

    return (size_t)(write_ptr - list);
}

int main(void) {
    int list[] = {5, -3, 2, -1, 7, -8, 0};
    size_t size = sizeof(list) / sizeof(list[0]);

    size_t new_size = remove_negatives(list, size);

    for (size_t i = 0; i < new_size; ++i) {
        printf("%d ", list[i]);
    }

    printf("\n");

    return 0;
}