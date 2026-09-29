#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse_string(char *string, size_t length)
{
    size_t left = 0;
    size_t right = length;

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

static int duplicate_string(const char *source, size_t length, char **destination)
{
    char *copy;

    if (source == NULL || destination == NULL || length == SIZE_MAX) {
        return 0;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return 0;
    }

    if (snprintf(copy, length + 1U, "%.*s", (int)length, source) < 0 ||
        strlen(copy) != length) {
        free(copy);
        return 0;
    }

    *destination = copy;
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
    char **strings;
    size_t index;
    int result = EXIT_SUCCESS;

    if (count != sizeof(lengths) / sizeof(lengths[0]) ||
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
        if (lengths[index] > (size_t)INT32_MAX ||
            !duplicate_string(values[index], lengths[index], &strings[index])) {
            fputs("String allocation or copy failed.\n", stderr);
            result = EXIT_FAILURE;
            break;
        }
    }

    if (result == EXIT_SUCCESS) {
        reverse_strings(strings, lengths, count);

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

    for (index = 0; index < count; ++index) {
        free(strings[index]);
    }

    free(strings);
    return result;
}