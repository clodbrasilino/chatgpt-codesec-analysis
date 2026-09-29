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

static void reverse_strings(char *strings[], const size_t lengths[], size_t count)
{
    size_t index;

    if (strings == NULL || lengths == NULL) {
        return;
    }

    for (index = 0; index < count; ++index) {
        if (strings[index] != NULL) {
            reverse_string(strings[index], lengths[index]);
        }
    }
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
    char **strings;
    size_t index;
    int result = EXIT_SUCCESS;

    if (count > SIZE_MAX / sizeof(*strings)) {
        fputs("Allocation size overflow.\n", stderr);
        return EXIT_FAILURE;
    }

    strings = calloc(count, sizeof(*strings));
    if (strings == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < count; ++index) {
        size_t source_length = strlen(values[index]);
        size_t capacity;

        if (source_length != lengths[index] || source_length == SIZE_MAX) {
            fputs("Invalid string length.\n", stderr);
            result = EXIT_FAILURE;
            break;
        }

        capacity = source_length + 1U;
        strings[index] = malloc(capacity);
        if (strings[index] == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            result = EXIT_FAILURE;
            break;
        }

        if (snprintf(strings[index], capacity, "%s", values[index]) < 0) {
            fputs("String copy failed.\n", stderr);
            result = EXIT_FAILURE;
            break;
        }
    }

    if (result == EXIT_SUCCESS) {
        reverse_strings(strings, lengths, count);

        for (index = 0; index < count; ++index) {
            if (fwrite(strings[index], 1U, lengths[index], stdout) != lengths[index] ||
                fputc('\n', stdout) == EOF) {
                fputs("Output failure.\n", stderr);
                result = EXIT_FAILURE;
                break;
            }
        }
    }

    for (index = 0; index < count; ++index) {
        free(strings[index]);
    }

    free(strings);
    return result;
}