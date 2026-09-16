#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void sift_down(int *list, size_t length, size_t root)
{
    while (root < length / 2) {
        size_t child = root * 2 + 1;

        if (child + 1 < length && list[child + 1] < list[child]) {
            ++child;
        }

        if (list[root] <= list[child]) {
            break;
        }

        int temporary = list[root];
        list[root] = list[child];
        list[child] = temporary;
        root = child;
    }
}

bool heapify(int *list, size_t length)
{
    if (list == NULL && length != 0) {
        return false;
    }

    for (size_t i = length / 2; i > 0; --i) {
        sift_down(list, length, i - 1);
    }

    return true;
}

int main(int argc, char *argv[])
{
    size_t length = argc > 1 ? (size_t)(argc - 1) : 0;

    if (length > SIZE_MAX / sizeof(int)) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    int *list = NULL;

    if (length != 0) {
        list = malloc(length * sizeof(*list));
        if (list == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        char *end = NULL;
        errno = 0;
        long value = strtol(argv[i + 1], &end, 10);

        if (errno == ERANGE || end == argv[i + 1] || *end != '\0' ||
            value < INT_MIN || value > INT_MAX) {
            fprintf(stderr, "Invalid integer: %s\n", argv[i + 1]);
            free(list);
            return EXIT_FAILURE;
        }

        list[i] = (int)value;
    }

    if (!heapify(list, length)) {
        fputs("Failed to create heap.\n", stderr);
        free(list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (i != 0 && putchar(' ') == EOF) {
            free(list);
            return EXIT_FAILURE;
        }

        if (printf("%d", list[i]) < 0) {
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