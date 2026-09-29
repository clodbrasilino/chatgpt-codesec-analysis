#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void reverse_range(int *list, size_t begin, size_t end)
{
    while (begin < end) {
        int temporary;

        --end;
        if (begin >= end) {
            break;
        }

        temporary = list[begin];
        list[begin] = list[end];
        list[end] = temporary;
        ++begin;
    }
}

bool rotate_left(int *list, size_t length, size_t positions)
{
    if (length == 0) {
        return true;
    }

    if (list == NULL) {
        return false;
    }

    positions %= length;

    if (positions == 0) {
        return true;
    }

    reverse_range(list, 0, positions);
    reverse_range(list, positions, length);
    reverse_range(list, 0, length);

    return true;
}

int main(void)
{
    int *list = NULL;
    size_t length;
    size_t positions;
    size_t index;
    int status = EXIT_FAILURE;

    if (scanf("%zu %zu", &length, &positions) != 2) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*list)) {
        return EXIT_FAILURE;
    }

    if (length > 0) {
        list = malloc(length * sizeof(*list));
        if (list == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (index = 0; index < length; ++index) {
        if (scanf("%d", &list[index]) != 1) {
            goto cleanup;
        }
    }

    if (!rotate_left(list, length, positions)) {
        goto cleanup;
    }

    for (index = 0; index < length; ++index) {
        if (index > 0 && putchar(' ') == EOF) {
            goto cleanup;
        }

        if (printf("%d", list[index]) < 0) {
            goto cleanup;
        }
    }

    if (putchar('\n') == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(list);
    return status;
}