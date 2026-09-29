#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct mutable_string {
    char *data;
    size_t length;
};

static size_t argument_length(const char *argument)
{
    size_t length = 0U;

    while (argument[length] != '\0') {
        ++length;
    }

    return length;
}

static bool reverse_strings(struct mutable_string strings[], size_t count)
{
    size_t i;

    if (count > 0U && strings == NULL) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        size_t left;

        if (strings[i].data == NULL) {
            return false;
        }

        for (left = 0U; left < strings[i].length / 2U; ++left) {
            size_t right = strings[i].length - left - 1U;
            char temporary = strings[i].data[left];

            strings[i].data[left] = strings[i].data[right];
            strings[i].data[right] = temporary;
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    struct mutable_string *strings = NULL;
    size_t count;
    size_t i;

    if (argc < 1 || argv == NULL || argv[argc] != NULL) {
        return EXIT_FAILURE;
    }

    count = (size_t)argc - 1U;

    if (count > SIZE_MAX / sizeof(*strings)) {
        return EXIT_FAILURE;
    }

    if (count > 0U) {
        strings = malloc(count * sizeof(*strings));
        if (strings == NULL) {
            (void)fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (i = 0U; i < count; ++i) {
        if (argv[i + 1U] == NULL) {
            free(strings);
            return EXIT_FAILURE;
        }

        strings[i].data = argv[i + 1U];
        strings[i].length = argument_length(argv[i + 1U]);
    }

    if (!reverse_strings(strings, count)) {
        (void)fputs("Failed to reverse strings.\n", stderr);
        free(strings);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (fputs(strings[i].data, stdout) == EOF ||
            fputc('\n', stdout) == EOF) {
            (void)fputs("Failed to write output.\n", stderr);
            free(strings);
            return EXIT_FAILURE;
        }
    }

    free(strings);

    if (fflush(stdout) == EOF) {
        (void)fputs("Failed to flush output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}