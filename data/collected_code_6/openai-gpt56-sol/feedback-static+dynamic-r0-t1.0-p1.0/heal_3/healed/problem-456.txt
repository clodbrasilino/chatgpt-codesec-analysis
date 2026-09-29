#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse_string(char *string, size_t length)
{
    size_t left = 0U;
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

static int reverse_strings(char *const strings[],
                           const size_t lengths[],
                           size_t count)
{
    if (count != 0U && (strings == NULL || lengths == NULL)) {
        return -1;
    }

    for (size_t index = 0U; index < count; ++index) {
        if (strings[index] == NULL) {
            return -1;
        }

        reverse_string(strings[index], lengths[index]);
    }

    return 0;
}

int main(void)
{
    static const char *const source_strings[] = {
        "Hello",
        "World",
        "Secure C"
    };
    static const size_t lengths[] = {
        sizeof("Hello") - 1U,
        sizeof("World") - 1U,
        sizeof("Secure C") - 1U
    };
    enum {
        STRING_COUNT = sizeof(source_strings) / sizeof(source_strings[0])
    };
    char **strings = calloc(STRING_COUNT, sizeof(*strings));
    int status = EXIT_FAILURE;

    if (strings == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < STRING_COUNT; ++index) {
        size_t allocation_size;

        if (lengths[index] == SIZE_MAX) {
            goto cleanup;
        }

        allocation_size = lengths[index] + 1U;
        strings[index] = malloc(allocation_size);
        if (strings[index] == NULL) {
            goto cleanup;
        }

        memcpy(strings[index], source_strings[index], lengths[index]);
        strings[index][lengths[index]] = '\0';
    }

    if (reverse_strings(strings, lengths, STRING_COUNT) != 0) {
        goto cleanup;
    }

    for (size_t index = 0U; index < STRING_COUNT; ++index) {
        if (puts(strings[index]) == EOF) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    for (size_t index = 0U; index < STRING_COUNT; ++index) {
        free(strings[index]);
    }

    free(strings);
    return status;
}