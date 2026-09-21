#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse_string(char *string, size_t length)
{
    size_t left = 0;
    size_t right = length;

    if (string == NULL) {
        return;
    }

    while (left < right) {
        char temporary;

        --right;
        temporary = string[left];
        string[left] = string[right];
        string[right] = temporary;
        ++left;
    }
}

static int reverse_strings(char *const strings[],
                           const size_t lengths[],
                           size_t count)
{
    size_t index;

    if (strings == NULL || lengths == NULL) {
        return 0;
    }

    for (index = 0; index < count; ++index) {
        if (strings[index] == NULL) {
            return 0;
        }

        reverse_string(strings[index], lengths[index]);
    }

    return 1;
}

int main(void)
{
    static const char *const values[] = {
        "Hello",
        "Experienced C",
        "Safe programming",
        ""
    };
    static const size_t lengths[] = {
        sizeof("Hello") - 1U,
        sizeof("Experienced C") - 1U,
        sizeof("Safe programming") - 1U,
        sizeof("") - 1U
    };
    const size_t count = sizeof(values) / sizeof(values[0]);
    const size_t length_count = sizeof(lengths) / sizeof(lengths[0]);
    char **strings = NULL;
    size_t initialized = 0;
    size_t index;
    int result = EXIT_SUCCESS;

    if (count != length_count ||
        count > SIZE_MAX / sizeof(*strings)) {
        fputs("Invalid array size.\n", stderr);
        return EXIT_FAILURE;
    }

    strings = calloc(count, sizeof(*strings));
    if (strings == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < count; ++index) {
        const size_t source_length = lengths[index];
        size_t capacity;

        if (values[index] == NULL || source_length == SIZE_MAX) {
            fputs("Invalid string.\n", stderr);
            result = EXIT_FAILURE;
            break;
        }

        capacity = source_length + 1U;

        if (strnlen(values[index], capacity) != source_length) {
            fputs("Invalid string.\n", stderr);
            result = EXIT_FAILURE;
            break;
        }

        strings[index] = malloc(capacity);
        if (strings[index] == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            result = EXIT_FAILURE;
            break;
        }

        memcpy(strings[index], values[index], source_length);
        strings[index][source_length] = '\0';
        ++initialized;
    }

    if (result == EXIT_SUCCESS &&
        !reverse_strings(strings, lengths, count)) {
        fputs("String reversal failed.\n", stderr);
        result = EXIT_FAILURE;
    }

    if (result == EXIT_SUCCESS) {
        for (index = 0; index < count; ++index) {
            if (fwrite(strings[index], 1U, lengths[index], stdout) !=
                    lengths[index] ||
                fputc('\n', stdout) == EOF) {
                fputs("Output failure.\n", stderr);
                result = EXIT_FAILURE;
                break;
            }
        }
    }

    for (index = 0; index < initialized; ++index) {
        free(strings[index]);
    }

    free(strings);
    return result;
}