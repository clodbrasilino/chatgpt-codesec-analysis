#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void sift_down(int *values, size_t length, size_t root)
{
    while (root < length / 2U) {
        size_t child = root * 2U + 1U;

        if (child + 1U < length && values[child + 1U] < values[child]) {
            ++child;
        }

        if (values[root] <= values[child]) {
            break;
        }

        int temporary = values[root];
        values[root] = values[child];
        values[child] = temporary;
        root = child;
    }
}

static bool heapify(int *values, size_t length)
{
    if (values == NULL && length != 0U) {
        return false;
    }

    for (size_t index = length / 2U; index > 0U; --index) {
        sift_down(values, length, index - 1U);
    }

    return true;
}

int main(int argc, char *argv[const])
{
    if (argc < 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s integer [integer ...]\n", program_name);
        return EXIT_FAILURE;
    }

    size_t length = (size_t)argc - 1U;

    if (length > SIZE_MAX / sizeof(int)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    int *values = malloc(length * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < length; ++index) {
        const char *argument = argv[index + 1U];
        char *end = NULL;

        errno = 0;
        long parsed = strtol(argument, &end, 10);

        if (errno == ERANGE || end == argument || *end != '\0' ||
            parsed < INT_MIN || parsed > INT_MAX) {
            fprintf(stderr, "Invalid integer: %s\n", argument);
            free(values);
            return EXIT_FAILURE;
        }

        values[index] = (int)parsed;
    }

    if (!heapify(values, length)) {
        fputs("Unable to create heap\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < length; ++index) {
        if (printf("%s%d", index == 0U ? "" : " ", values[index]) < 0) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}