#include <stdio.h>
#include <stddef.h>

size_t remove_negatives(int *list, size_t size) {
    if (list == NULL || size == 0) {
        return 0;
    }

    int *end = list + size;
    int *write = list;
    int *read = list;

    while (read < end) {
        if (*read >= 0) {
            *write = *read;
            ++write;
        }
        ++read;
    }

    return (size_t)(write - list);
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