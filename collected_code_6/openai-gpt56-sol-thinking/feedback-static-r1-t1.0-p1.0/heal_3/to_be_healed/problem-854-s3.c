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
    if (length > 0U && values == NULL) {
        return false;
    }

    for (size_t index = length / 2U; index > 0U; --index) {
        sift_down(values, length, index - 1U);
    }

    return true;
}

static bool parse_integer(const char *text, int *result)
{
    if (text == NULL || result == NULL) {
        return false;
    }

    char *end = NULL;

    errno = 0;
    long parsed = strtol(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return false;
    }

    *result = (int)parsed;
    return true;
}

int main(int argc, char **argv)
{
    const char *program_name = "program";

    if (argv != NULL && argc > 0 && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc < 2 || argv == NULL) {
        fprintf(stderr, "Usage: %s integer [integer ...]\n", program_name);
        return EXIT_FAILURE;
    }

    size_t length = (size_t)(argc - 1);

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

        if (!parse_integer(argument, &values[index])) {
            if (argument != NULL) {
                fprintf(stderr, "Invalid integer: %s\n", argument);
            } else {
                fputs("Invalid integer: null argument\n", stderr);
            }

            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!heapify(values, length)) {
        fputs("Unable to create heap\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < length; ++index) {
        /* Possible weaknesses found:
         * Flawfinder printf: If format strings can be influenced by an attacker, they can be exploited (CWE-134). Use a constant for the format specification. (risk 4, format)
         */
        if (printf(index == 0U ? "%d" : " %d", values[index]) < 0) {
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