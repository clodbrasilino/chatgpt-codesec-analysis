#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void sift_down(int *list, size_t length, size_t root)
{
    while (root < length / 2U) {
        const size_t left = root * 2U + 1U;
        const size_t right = left + 1U;
        size_t smallest = left;

        if (right < length && list[right] < list[left]) {
            smallest = right;
        }

        if (list[root] <= list[smallest]) {
            break;
        }

        const int temporary = list[root];
        list[root] = list[smallest];
        list[smallest] = temporary;
        root = smallest;
    }
}

static bool heapify(int *list, size_t length)
{
    if (list == NULL && length != 0U) {
        return false;
    }

    for (size_t index = length / 2U; index > 0U; --index) {
        sift_down(list, length, index - 1U);
    }

    return true;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        const char *program_name = "heapify";

        if (argc > 0 && argv[0] != NULL) {
            program_name = argv[0];
        }

        fprintf(stderr, "Usage: %s integer [integer ...]\n", program_name);
        return EXIT_FAILURE;
    }

    const size_t length = (size_t)argc - 1U;

    if (length > SIZE_MAX / sizeof(int)) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    int *list = malloc(length * sizeof(*list));

    if (list == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < length; ++index) {
        const char *argument = argv[index + 1U];

        if (argument == NULL) {
            fputs("Invalid null argument.\n", stderr);
            free(list);
            return EXIT_FAILURE;
        }

        char *end = NULL;
        errno = 0;

        const long value = strtol(argument, &end, 10);

        if (errno == ERANGE ||
            end == argument ||
            *end != '\0' ||
            value < INT_MIN ||
            value > INT_MAX) {
            fprintf(stderr, "Invalid integer: %s\n", argument);
            free(list);
            return EXIT_FAILURE;
        }

        list[index] = (int)value;
    }

    if (!heapify(list, length)) {
        fputs("Failed to create heap.\n", stderr);
        free(list);
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < length; ++index) {
        if (index != 0U && putchar(' ') == EOF) {
            free(list);
            return EXIT_FAILURE;
        }

        if (printf("%d", list[index]) < 0) {
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