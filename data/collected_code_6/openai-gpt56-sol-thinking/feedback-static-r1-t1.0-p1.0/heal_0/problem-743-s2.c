#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void reverse_range(int *list, size_t first, size_t last)
{
    while (first < last) {
        int temporary;

        --last;
        if (first >= last) {
            break;
        }

        temporary = list[first];
        list[first] = list[last];
        list[last] = temporary;
        ++first;
    }
}

static bool rotate_right(int *list, size_t length, size_t positions)
{
    if (list == NULL && length != 0U) {
        return false;
    }

    if (length < 2U) {
        return true;
    }

    positions %= length;
    if (positions == 0U) {
        return true;
    }

    reverse_range(list, 0U, length);
    reverse_range(list, 0U, positions);
    reverse_range(list, positions, length);

    return true;
}

int main(void)
{
    int *list = NULL;
    size_t length;
    size_t positions;
    size_t index;

    if (scanf("%zu %zu", &length, &positions) != 2) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*list)) {
        return EXIT_FAILURE;
    }

    if (length != 0U) {
        list = malloc(length * sizeof(*list));
        if (list == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (index = 0U; index < length; ++index) {
        if (scanf("%d", &list[index]) != 1) {
            free(list);
            return EXIT_FAILURE;
        }
    }

    if (!rotate_right(list, length, positions)) {
        free(list);
        return EXIT_FAILURE;
    }

    for (index = 0U; index < length; ++index) {
        if (printf("%s%d", index == 0U ? "" : " ", list[index]) < 0) {
            free(list);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(list);
        return EXIT_FAILURE;
    }

    free(list);
    return EXIT_SUCCESS;
}