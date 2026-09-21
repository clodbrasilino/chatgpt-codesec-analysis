#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void sift_down(int *list, size_t length, size_t root)
{
    while (root < length / 2U) {
        size_t left = root * 2U + 1U;
        size_t right = left + 1U;
        size_t smallest = left;

        if (right < length && list[right] < list[left]) {
            smallest = right;
        }

        if (list[root] <= list[smallest]) {
            return;
        }

        int temporary = list[root];
        list[root] = list[smallest];
        list[smallest] = temporary;
        root = smallest;
    }
}

bool heapify(int *list, size_t length)
{
    if (length > 0U && list == NULL) {
        return false;
    }

    for (size_t index = length / 2U; index > 0U; --index) {
        sift_down(list, length, index - 1U);
    }

    return true;
}

static bool parse_integer(const char *argument, int *result)
{
    char *end = NULL;
    long value;

    if (argument == NULL || result == NULL || *argument == '\0') {
        return false;
    }

    errno = 0;
    value = strtol(argument, &end, 10);

    if (errno == ERANGE ||
        end == argument ||
        *end != '\0' ||
        value < INT_MIN ||
        value > INT_MAX) {
        return false;
    }

    *result = (int)value;
    return true;
}

static int run(int argc, char **argv)
{
    const char *program_name = "program";

    if (argv != NULL && argc > 0 && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc < 2 || argv == NULL) {
        if (fprintf(stderr,
                    "Usage: %s integer [integer ...]\n",
                    program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if ((uintmax_t)(unsigned int)(argc - 1) >
        (uintmax_t)(SIZE_MAX / sizeof(int))) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t length = (size_t)(argc - 1);
    int *list = malloc(length * sizeof(*list));

    if (list == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < length; ++index) {
        const char *argument = argv[index + 1U];

        if (!parse_integer(argument, &list[index])) {
            if (argument != NULL) {
                fprintf(stderr, "Invalid integer: %s\n", argument);
            } else {
                fputs("Invalid integer: null argument\n", stderr);
            }

            free(list);
            return EXIT_FAILURE;
        }
    }

    if (!heapify(list, length)) {
        fputs("Failed to create heap.\n", stderr);
        free(list);
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < length; ++index) {
        if (printf(index == 0U ? "%d" : " %d", list[index]) < 0) {
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

int main(int argc, char **argv)
{
    return run(argc, argv);
}