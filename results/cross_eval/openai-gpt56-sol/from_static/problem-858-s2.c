#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    struct List *next;
} List;

int square_list_count(const List *list, size_t *result)
{
    size_t count = 0;

    if (result == NULL) {
        return -1;
    }

    while (list != NULL) {
        if (count == SIZE_MAX) {
            return -1;
        }

        ++count;
        list = list->next;
    }

    if (count != 0 && count > SIZE_MAX / count) {
        return -1;
    }

    *result = count * count;
    return 0;
}

int main(void)
{
    List third = {NULL};
    List second = {&third};
    List first = {&second};
    size_t result;

    if (square_list_count(&first, &result) != 0) {
        fputs("Unable to compute the squared count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}